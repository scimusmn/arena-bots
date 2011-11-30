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

extern int CURRENT_ROBOT_NUMBER;

string ROOT_NAME="";
string ROOT_DIR="";

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_button Hldr//_-_-_-_-_//_-_-_-_-_

buttonHolder::buttonHolder()
{
  area.width=0;
  area.height=0;
}

buttonHolder::buttonHolder(int numObj, ...)
{
  area.height=0;
  va_list vl;
	va_start(vl,numObj);
  
  for (int i=0; i<numObj; i++) {
    addObj(*va_arg(vl,ofInterObj *));
  }
  
  va_end(vl);
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
  drawBorder(area);
  area.x=x=_x;
  area.y=y=_y;
  int xPos=pad/2;
  for (unsigned int i=0; i<objs.size(); i++) {
    objs[i]->draw(x+xPos-((objs.size()==1)?objs[i]->w/2:0),y+(area.height-objs[i]->h)/2);
    xPos+=objs[i]->w+space;
  }
}

buttonHolder & barOfButtons::operator[](int i){
  return *static_cast<buttonHolder *>(objs[i]);
}

void barOfButtons::addSection()
{
  objs.push_back(new buttonHolder());
}

void barOfButtons::addSection(int numObjs, ...)
{
  va_list vl;
	va_start(vl,numObjs);
  
  objs.push_back(new buttonHolder(numObjs, vl));
  va_end(vl);
}

buttonHolder & barOfButtons::lastSection()
{
  return (*this)[objs.size()-1];
}

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_control Bar//_-_-_-_-_//_-_-_-_-_

void controlBar::barSpacing()
{
  //_-_-_-_-_//_-_-_-_-_ spacing setup //_-_-_-_-_//_-_-_-_-_
  for(int i=0; i<4;i++)
    bHldr.push_back(buttonHolder());
  
  bHldr[0].addObj(demo);
  
  for (unsigned int i=0; i<sets.size(); i++) bHldr[1].addObj(sets(i));
  bHldr[1].internalSpace(20);
  
  bHldr[2].addObj(undoBut);
  bHldr[2].addObj(redoBut);
  bHldr[2].internalSpace(20);
  
  bHldr[3].addObj(clearBut);
  
  double maxH=0;
  int pad=ofGetWidth();
  
  for (unsigned int i=0; i<bHldr.size(); i++) {
    maxH=max(maxH,bHldr[i].maxHeight());
    pad-=bHldr[i].area.width;
  }
  buttonBar=ofRectangle(x,y,ofGetWidth(),maxH*1.2);
  
  for (unsigned int i=0; i<bHldr.size(); i++) {
    bHldr[i].area.height=bHldr[i].h=buttonBar.height;
    bHldr[i].padding(pad/bHldr.size());
  }
  
  h=subBar.height+buttonBar.height;
  w=ofGetWidth();
}

void controlBar::setup(bGroup * bG, sbGroup * sbG)
{
  blocks=bG;
  sideBar=sbG;
  
  clearBut.setup("Clear blocks", 19);
  redoBut.setup(64, 64, "images/redo.png");
	undoBut.setup(64, 64, "images/undo.png");
  demo.setup("View Demo", 19);
  skipBut.setup(300, 100, "images/skipBut.png");
  
  anim.setup(blocks, sideBar);
  
  subtitle.loadFont("fonts/DinC.ttf");
  subtitle.setSize(22);
  subtitle.setMode(OF_FONT_TOP);
  
  subBar.height=subtitle.stringHeight("Kjhg")*1.5;
  subBar.width=ofGetWidth();
  
  ROOT_DIR=config("config.cfg");
  
  sets.load(ROOT_DIR);
  loadBlocks(sets[0]);
  
  sets[0].choice.setAvailable(false);
  
  upload.setup(blocks);
  
  testbed.setup(&blocks->base);
  
  barSpacing();
  
  loadBlocks(sets[0]);
  setAvailableButtons();
}

void controlBar::loadBlocks(blockGroup & bg){
	
  if(bg.nLoaded>=3){
    
    //--------- load the new blocks with the blockGroup data
    ROOT_NAME=bg.title;
    sideBar->clear();
    sideBar->setup(bg.blockXML,blocks);
    
    anim.changeAnimXML(bg.animXML);
  }
}

void controlBar::draw(int _x, int _y)
{
  buttonBar.x=x=_x;
  buttonBar.y=y=_y;
  subBar.x=x;
  subBar.y=y+buttonBar.height;
  
  
  //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
  //_-_-_-_-_//_-_-_-_-_//buttonbar//_-_-_-_-_//_-_-_-_-_
  
  ofSetColor(black);
  ofRect(buttonBar);
  
  ofSetColor(gray);
  drawHatching(buttonBar.x, buttonBar.y, buttonBar.width, buttonBar.height, 85,80);
  
  bHldr[0].draw(buttonBar.x,buttonBar.y);
  for (unsigned int i=1; i<bHldr.size(); i++) {
    bHldr[i].draw(bHldr[i-1].area.x+bHldr[i-1].area.width,buttonBar.y);
  }
  
  //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
  //_-_-_-_-_//_-_-_-_-_//subTitle //_-_-_-_-_//_-_-_-_-_
  
  ofSetColor(gray);
  ofRect(subBar);
  drawBorder(subBar);
  
  ofSetColor(yellow);
  ofRect(subBar.x, subBar.y, subBar.width, 1);
  
  if(sets.getSelected()){
    ofButton & t=sets.getSelected()->choice;
    int wid=t.w/16+1;
    ofSetColor(yellow);
    ofRect(t.x-wid, y, t.w+wid*2, buttonBar.height);
    wid=t.w/16;
    ofSetColor(gray);
    ofRect(t.x-wid, y, t.w+wid*2, buttonBar.height+10);
    t.draw(t.x,t.y);
    
    ofSetColor(yellow);
    subtitle.setSize(22);
    subtitle.setMode(OF_FONT_LEFT);
    subtitle.drawString(sets.getSelected()->subtitle, 50, subBar.y+(subBar.height-subtitle.stringHeight(sets.getSelected()->subtitle))/2);
  }
  
  if(testbed.isTesting()){
    ofRectangle & cBar=testbed.controlBar;
    
    ofSetColor(0x33, 0x33, 0x33);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(black);
    drawHatching(0, 0, ofGetWidth(), ofGetHeight(), 15,1);
    
    testbed.draw(0,cBar.y+cBar.height,ofGetHeight()-(cBar.y+cBar.height),ofGetHeight()-(cBar.y+cBar.height));
    blocks->base.draw(ofGetHeight(), y);
    testbed.drawCurrentBlock();
    
    testbed.drawControlBar(x, y);
  }
}

void controlBar::drawForeground(){
  
  if(anim.isPlaying()){
    ofSetColor(0, 0, 0,128);
    ofRect(skipBut.x-10, skipBut.y-10, skipBut.w+20, skipBut.h+20);
    skipBut.draw((ofGetWidth()-skipBut.w)/2, ofGetHeight()*3./4);
  }
  
  if(changed.running()){
    ofSetColor(0, 0, 0,192);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    subtitle.setSize(70);
    subtitle.setMode(OF_FONT_CENTER);
    ofSetColor(white);
    subtitle.drawString("Program changes not uploaded", ofGetWidth()/2, ofGetHeight()/3);
    subtitle.drawString("Reconnect robot to upload.", ofGetWidth()/2, ofGetHeight()*2/3.);
  }
  else if(serChk.drawForeground());
  else if(upload.drawForeground());
  else testbed.drawForeground();
  
  anim.drawCursor();
}

void controlBar::update()
{
  serChk.threadCheckAvailability();
  anim.update();
  
  if(serChk.justLostDevice()){
    cout << "lost it\n";
    if(blocks->changedSinceSave()) changed.set(3),changed.run();
    blocks->saveXML("programs/"+serChk.deviceNumber()+".xml");
    blocks->clear();
    if (testbed.isTesting()) {
      testbed.stopTesting();
      testbed.resetTurtle();
    }
  }
  if(serChk.justFoundDevice()){
    ofxDirList dir;
    int nDir=0;
    nDir = dir.listDir("programs");
    //you can now iterate through the files as you like
    for(int i = 0; i < nDir; i++){
      if(serChk.deviceNumber()+".xml"==ofGetFilename(dir.getPath(i)))
        blocks->loadFile(dir.getPath(i));
    }
  }
  
  if(testbed.turtleIsRunning()){
    testbed.idleTurtle();
  }
}

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_ mouse func//_-_-_-_-_//_-_-_-_-_

bool controlBar::clickDown(int _x, int _y, int button)
{
  if(!testbed.mouseLockout()){
    if(sets.clickDown(_x,_y)&&!anim.isPlaying()){
      if(sets.getSelected())
        loadBlocks((*sets.getSelected()));
    }
    
    if (clearBut.clickDown(_x, _y)) {
      blocks->clear();
    }
    
    if(demo.clickDown(_x, _y)){
      anim.play();
    }
    
    //--------- if we press the undo button, roll back the state of the blockGroup
    if (undoBut.clickDown(_x, _y)) {
      blocks->undoState();
    }
    
    //--------- if we press the redo button, push the state forward
    if (redoBut.clickDown(_x, _y)) {
      blocks->redoState();
    }
    
    //--------- if we press the skip button while the anim is running, stop anim
    if(anim.isPlaying()&&skipBut.clickDown(_x, _y)){
      anim.stop();
    }
  }
  
  testbed.clickDown(_x, _y);

  if(upload.clickDown(_x, _y)){
    blocks->saveXML("programs/"+serChk.deviceNumber()+".xml");
    testbed.resetTurtle();
    testbed.stopTesting();
  }
}

bool controlBar::clickUp()
{
  sets.clickUp();
  clearBut.clickUp();
  demo.clickUp();
  undoBut.clickUp();
  redoBut.clickUp();
  skipBut.clickUp();
  testbed.clickUp();
}

bool controlBar::mouseLockout(int button)
{
  return (!anim.isPlaying()||(anim.isPlaying()&&button==VMOUSE_BUTTON));
}

void controlBar::setAvailableButtons()
{
  redoBut.setAvailable(blocks->redoAvailable());
	undoBut.setAvailable(blocks->undoAvailable());
  demo.setAvailable(!anim.isPlaying());
}
