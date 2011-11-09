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

baseBlock::baseBlock():block(){
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
  
  ttlSize.y=h/2;
  ttlSize.x=w;
  
  uploadBut.setup( 128,128,"images/upload2.png");
}

void baseBlock::draw(int _x, int _y)
{
  x=_x, y=_y;
  
  ofSetColor(color*.9);
  drawBaseBlock(x, y, w, h);
  
  //-------- Draw the blocks below
	for (unsigned int i=0; i<blocksOn.size(); i++) {
		blocksOn[i].draw();
	}
	//-------- draw the blocks inside
	for (unsigned int i=0; i<blocksIn.size(); i++) {
		blocksIn[i].draw();
	}
  
  uploadBut.draw(x+w+10,y+h-50);
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
  action=t.action;
  
  return *this;
}