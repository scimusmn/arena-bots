/*
 *  baseBlock.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/9/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "baseBlock.h"
#include "blockDraw.h"

extern ofColor white, black, blue, yellow, gray;

extern int TITLE_HEIGHT;

baseBlock::baseBlock():block(){
  bDrawtest=true;
  w=530, h=90;
  orig.width=w;
  orig.height=h;
  interior.height=bottomBar=0;
  interior.y=0;
  interior.x=0;
	arialHeader.loadFont("DinC.ttf");
	arialHeader.setSize(21);
  title="";
  type=BLK_BASE;
	bGrabbed=0;
	w=max(w,double(arialHeader.stringWidth(title)+20));
	ddOpen=false;
	titlePos.x=10;
	color=ofColor(yellow);
	filename="null";
	placeHolder=false;
  
  ttlSize.y=TITLE_HEIGHT;
  ttlSize.x=w;
  
  //uploadBut.setup( 128,128,"images/upload2.png");
  testBut.setup("Test program", 20);
  uploadBut.setup("Upload program",20);
  
  pad=15;
  
  butArea.x=max(uploadBut.w,testBut.w)+pad*2;
  butArea.y=pad+uploadBut.h+pad+testBut.h+pad;
}

void baseBlock::setDrawTest(bool btest){
  bDrawtest=btest;
}

void baseBlock::draw(int _x, int _y)
{
  x=_x, y=_y;
  
  ofSetColor(color*.9);
  if(bDrawtest) drawBaseBlock(x, y, w, h,butArea.x,butArea.y);
  else drawBaseBlock(x, y, w, h,0,h);
  
  ofSetColor(black);
  ofNoFill();
  ofSetLineWidth(2);
  if(bDrawtest) drawBaseBlock(x, y, w, h,butArea.x,butArea.y);
  else drawBaseBlock(x, y, w, h,0,h);
  ofSetLineWidth(1);
  ofFill();
  
  //-------- Draw the blocks below
  int hOn=0;
	for (unsigned int i=0; i<blocksOn.size(); i++) {
		blocksOn[i].draw(x,y+h+hOn);
    hOn+=blocksOn[i].h;
	}
	//-------- draw the blocks inside
	for (unsigned int i=0; i<blocksIn.size(); i++) {
		blocksIn[i].draw();
	}
  
  if(bDrawtest){
    testBut.draw(x+w-butArea.x+(butArea.x-testBut.w)/2, y+pad);
    uploadBut.draw(x+w-butArea.x+(butArea.x-uploadBut.w)/2,testBut.y+testBut.h+pad);
  }
  else uploadBut.draw(x+w-butArea.x+(butArea.x-uploadBut.w)/2,y+(h-uploadBut.h)/2);
  
  
  drawOpenDD();
}

bool baseBlock::clickDown(int _x, int _y)
{
  uploadBut.clickDown(_x, _y);
}

bool baseBlock::newClickUp( int _x, int _y)
{
  uploadBut.clickUp();
}

void baseBlock::setup(bGroup * grp)
{
  group=grp;
}


baseBlock & baseBlock::operator=(baseBlock & t)
{
  x=t.x;
	y=t.y;
	w=t.w;
	h=t.h;
  relPos=t.relPos;
  
  orig=t.orig;
  interior=t.interior;
  titlePos=t.titlePos;
  ttlSize=t.ttlSize;
  
	arialHeader=t.arialHeader;
	type=t.type;
	bGrabbed=t.bGrabbed;
	title =t.title;
	filename=t.filename;
	numBlocks=t.numBlocks;
	
	ddGroup=t.ddGroup;
	blocksOn=t.blocksOn;
	blocksIn=t.blocksIn;
	ddOpen=t.ddOpen;
	placeHolder=t.placeHolder;
	color=t.color;
  insertSpace=t.insertSpace;
  
  return *this;
}