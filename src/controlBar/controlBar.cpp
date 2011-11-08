/*
 *  controlBar.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "controlBar.h"
#include "../sideBar/sideBar.h"

extern ofColor black, white, gray,blue,yellow,orange, red;

string ROOT_NAME2="";
string ROOT_DIR2="";

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_button Hldr//_-_-_-_-_//_-_-_-_-_

buttonHolder::buttonHolder()
{
  area.width=0;
  area.height=0;
}

void buttonHolder::addObj(ofInterObj & obj)
{
  objs.push_back(&obj);
  area.width+=obj.w;
}

void buttonHolder::internalSpace(int spc)
{
  space=spc;
  area.width+=space*(objs.size()-1);
}

double buttonHolder::maxHeight()
{
  double ret=0;
  for (unsigned int i=0; i<objs.size(); i++) {
    ret=max(ret,objs[i]->h);
  }
  return ret;
}

void buttonHolder::padding(int pd)
{
  pad=pd;
  area.width+=pad;
}

void buttonHolder::draw(int _x, int _y)
{
  drawShadowsAroundRect(area,10);
  area.x=x=_x;
  area.y=y=_y;
  int xPos=pad/2;
  for (unsigned int i=0; i<objs.size(); i++) {
    objs[i]->draw(x+xPos-((objs.size()==1)?objs[i]->w/2:0),y+(area.height-objs[i]->h)/2);
    xPos+=objs[i]->w+space;
  }
}



//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_control Bar//_-_-_-_-_//_-_-_-_-_

void controlBar::setup(bGroup * bG, sbGroup * sbG)
{
  blocks=bG;
  sideBar=sbG;
  
  sets.load(config("config.cfg"));
  loadBlocks(sets[0]);
  
  clearBut.setup("Clear blocks", "fonts/Arial.ttf", 20);
  redoBut.setup(64, 64, "images/redo.png");
	undoBut.setup(64, 64, "images/undo.png");
  demo.setup("View demo", "fonts/Arial.ttf", 20);
  skipBut.setup(300, 100, "images/skipBut.png");
  
  anim.setup(blocks, sideBar);
  
  cout << "how\n";
  //sets.load(config("config.cfg"));
  
  
  //_-_-_-_-_//_-_-_-_-_ spacing setup //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
  demoHldr.addObj(demo);
  
  for (unsigned int i=0; i<sets.size(); i++) setsHldr.addObj(sets(i));
  setsHldr.internalSpace(20);
  
  
  undoHldr.addObj(undoBut);
  undoHldr.addObj(redoBut);
  undoHldr.internalSpace(20);
  
  clearHldr.addObj(clearBut);
  
  double maxH=max(demoHldr.maxHeight(),max(setsHldr.maxHeight(),undoHldr.maxHeight()));
  buttonBar=ofRectangle(x,y,ofGetWidth(),maxH*1.5);
  
  demoHldr.area.height=setsHldr.area.height=undoHldr.area.height=clearHldr.area.height=buttonBar.height;
  
  int pad=(buttonBar.width-(demoHldr.area.width+setsHldr.area.width+undoHldr.area.width+clearHldr.area.width))/4;
  demoHldr.padding(pad);
  setsHldr.padding(pad);
  undoHldr.padding(pad);
  clearHldr.padding(pad);
}

void controlBar::loadBlocks(blockGroup & bg){
	
  if(bg.nLoaded>=3){
    
    //--------- load the new blocks with the blockGroup data
    ROOT_NAME2=bg.title;
    sideBar->clear();
    sideBar->setup(bg.blockXML,blocks);
    
    anim.changeAnimXML(bg.animXML);
  }
}

void controlBar::draw(int x, int y)
{
  buttonBar.x=x;
  buttonBar.y=y;
  
  
  ofSetColor(gray);
  ofRect(buttonBar);
  //_-_-_-_-_//_-_-_-_-_ move to class def and setup 
  
  /*double buttonMaxH=((sets.size())?sets(0).h:0);
  buttonMaxH=max(demo.h,max(clearBut.h,buttonMaxH));
  ofRectangle buttonBar(x,y,ofGetWidth(),buttonMaxH);
  
  double butWidth=0;
  for (unsigned int i=0; i<sets.size(); i++) {
    butWidth+=sets(i).w+((i<sets.size()-1)?20:0);
  }
  butWidth+=demo.w;
  butWidth+=undoBut.w+20+redoBut.w;
  butWidth+=clearBut.w;
  
  double posAug=(buttonBar.w-butWidth)/4;*/
  
  //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
  //_-_-_-_-_//_-_-_-_-_ demo space//_-_-_-_-_//_-_-_-_-_
  
  demoHldr.draw(buttonBar.x,buttonBar.y);
  setsHldr.draw(demoHldr.x+demoHldr.area.width,buttonBar.y);
  undoHldr.draw(setsHldr.x+setsHldr.area.width,buttonBar.y);
  clearHldr.draw(undoHldr.x+undoHldr.area.width,buttonBar.y);
}

void controlBar::update()
{
  redoBut.setAvailable(blocks->redoAvailable());
	undoBut.setAvailable(blocks->undoAvailable());
  demo.setAvailable(anim.isPlaying());
  
  serChk.checkAvailability();
}

bool controlBar::clickDown(int x, int y)
{
  if(sets.clickDown(x,y)&&!anim.isPlaying()){
    if(sets.getSelected())
      loadBlocks((*sets.getSelected()));
  }
  
  if (clearBut.clickDown(x, y)) {
    blocks->clear();
  }
  
  if(demo.clickDown(x, y)){
    anim.play();
  }
  
  //--------- if we press the undo button, roll back the state of the blockGroup
  if (undoBut.clickDown(x, y)) {
    blocks->undoState();
  }
  
  //--------- if we press the redo button, push the state forward
  if (redoBut.clickDown(x, y)) {
    blocks->redoState();
  }
}

bool controlBar::clickUp()
{
  
}
