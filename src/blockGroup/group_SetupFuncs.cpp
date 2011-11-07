/*
 *  blockGroup.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/1/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "blockGroup.h"

extern int pixPerInch;

/****************************************************************
 *********************BlockGroup*********************************/

bGroup::bGroup(double _x, double _y,double wid,double hgt):ofInterObj(_x,_y,wid,hgt){
	//blocks.reserve(100);
	x=_x,y=_y,w=wid,h=hgt;
	used[""]=false;
}

/*****************************************************************
 * bGroup():ofInterObj() :: constructor for bGroup, a subclass of ofInterObj()
 *
 *  Description::
 *
 *
 *  Input_________
 *
 *    NONE :
 *
 *  Output________
 *
 *    New instance of bGroup :
 *
 */

bGroup::bGroup():ofInterObj(){
	bGrabbed=inHand=ddopen=0;
}

bGroup::~bGroup(){
	blocks.clear();
}

//------------------------ Utilities -------------------

void bGroup::setup(double _x, double _y,double wid,double hgt){
	//blocks.reserve(100);
  bSequencePlay=bTesting=false;
	bGrabbed=inHand=ddopen=false;
	cSetup(_x,_y,wid,hgt);
	used[""]=false;
  base.setup(530, 90);
	base.blocksOn.reserve(100);
	states.recordState(storageState(blocks,base));
  held.setup(0,0);
  
  mapp.loadImage("maps/map_2.jpg");
  turtle.setup(2.5*(mapp.width/12.),mapp.width-1.5*(mapp.width/12.), 25*4.25,4.5*25);
  actionTime.set(0.01);
  pixPerInch=mapp.width/48;
  currentTest=0;
}

int bGroup::size(){
	return blocks.size();
}

void bGroup::clear(){
	base.blocksOn.clear();
	blocks.clear();
}

block bGroup::operator[](int i){
	return blocks[i];
}

void bGroup::recordState()
{
	states.recordState(storageState(blocks,base));
}

void bGroup::undoState()
{
	if(states.undoAvailable()){
    storageState * t;
    if((t=states.undoState())){
      blocks=t->blocks;
      base=t->base;
    }
  }
}

void bGroup::redoState()
{
	if(states.redoAvailable()){
    storageState * t;
    if((t=states.redoState())){
      blocks=t->blocks;
      base=t->base;
    }
  }
}

bool bGroup::undoAvailable()
{
	return states.undoAvailable();
}

bool bGroup::redoAvailable()
{
	return states.redoAvailable();
}


//----------------------- Add block Functions -------------------

void bGroup::addFromSB(block t,int _x,int _y){
	if(t.over(_x,_y)||t.onBlockOn(_x, _y)&&!inHand){
		int numBlocks=size();
		if(numBlocks<99){
			used[t.title]=false;
      held=t;
      held.bGrabbed=bGrabbed=inHand=true;
			dispx = held.x-_x;
			dispy = held.y-_y;
		}
		else {
			printf("Remove some blocks, doncha know.");
		}
	}
}

void bGroup::update()
{
  if(!bTesting){
    for (unsigned int i=0; i<blocks.size(); i++) {
      blocks[i].newUpdateHeight();
      blocks[i].newUpdatePositions();
    }
  }
  base.newUpdateHeight();
  base.newUpdatePositions();
	
  if(bTesting){
    bSequencePlay=idleSequence(&base);
  }
}