/*
 *  newSizeAndPositionFunctions.cpp
 *  robotBlocks
 *
 *  Created by Exhibits on 7/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */


#include "blocks.h"

int block::newHeightOn()
{
  int ret=0;
  for (unsigned int i=0; i<blocksOn.size(); i++) {
    blocksOn[i].newUpdateHeight();
    ret+=blocksOn[i].h;
  }
  return ret;
}

int block::newHeightIn()
{
  int ret=0;
  for (unsigned int i=0; i<blocksIn.size(); i++) {
    blocksIn[i].newUpdateHeight();
  }
  
}

int block::newUpdateHeight()
{
  int ret=0;
  int topHeight=interior.y;
  int botHeight=orig.height-(interior.y+interior.height);
  if(type==BLK_BRACKET){
    for (unsigned int i=0; i<blocksIn.size(); i++) {
      ret+=blocksIn[i].newUpdateHeight()-5;
    }
    ret+=5;
  }
  if(ret<interior.height) ret=interior.height; 
  h=ret+topHeight+botHeight;
  for (unsigned int i=0; i<blocksOn.size(); i++) {
    blocksOn[i].newUpdateHeight();
  }
  return h+insertSpace;
}

void alignBlocks(vector<block> & t)
{
  for (unsigned i=1; i<t.size(); i++) {
    t[i].move(t[i-1].x,t[i-1].y+t[i-1].h+t[i-1].insertSpace-5);
    t[i].newUpdatePositions();
  }
}

void block::newUpdatePositions()
{
  if(blocksIn.size()){
    blocksIn[0].move(x+interior.x,y+interior.y+insertSpace);
    blocksIn[0].newUpdatePositions();
  }
  alignBlocks(blocksIn);
  if(blocksOn.size()){
    blocksOn[0].move(x,y+h+insertSpace-5);
    blocksOn[0].newUpdatePositions();
  }
  alignBlocks(blocksOn);
}

//********************* position boolean functions ********************

bool block::inside(block & drop)
{
  bool ret=0;
  if(type==BLK_BRACKET){
    int inLine=y+interior.y/2;
    int bottomSpace=orig.height-(interior.y+interior.height);
    int inH=interior.y/2+h-(interior.y+bottomSpace);
    if(drop.inBounds(x+interior.x, inLine, w-interior.x, inH))
      ret=true;
  }
  return ret;
}

bool block::beneath(block & chk, int blw)
{
  if(blw<0) blw=ttlSize.y/2;
  bool ret=0;
  int bottomSpace=orig.height-(interior.y+interior.height);
  int midLine=y+ttlSize.y/2;
  
  if(type==BLK_BRACKET) midLine=y+h-bottomSpace;
  int checkHeight=h+y-midLine+blw;
  
  if(chk.inBounds(x, midLine, w, checkHeight)) ret=true;  
  return ret;
}

bool block::inBounds(int xX, int yX, int wX, int hX)
{
  bool ret=0;
  int pH=h;
  if(type==BLK_BRACKET) pH=interior.y;
  if(((x>=xX && x<xX+wX)||(x+w>=xX && x+w<xX+wX)||(x<=xX && x+w >= xX + wX))&&((y>=yX && y<yX+hX)||(y+pH>=yX && y+pH<yX+hX))) ret=true;
  return ret;
}
