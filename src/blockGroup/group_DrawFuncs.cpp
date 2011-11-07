/*
 *  groupDrawFuncs.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/1/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "blockGroup.h"

//---------------Group Draw Functions ------------------

/*****************************************************************
 * indicate(dropBlock & db) 
 *
 *  Description::
 *
 *
 *  Input_________
 *
 *    dropBlock & db :
 *
 *  Output________
 *
 *    NONE :
 *
 */


void indicate(dropBlock & db)
{
  ofSetColor(255, 255, 255);
  if(db.index){
    block & t=(*db.inThis)[db.index-1];
    ofRect(t.x+5, t.y+t.h, t.w-10, 10);
  }
  else {
    block & t=*(db.belowThis);
    if(db.whichVector==OF_BLOCK_IN)
      ofRect(t.x+t.interior.x+5, t.y+t.interior.y, t.w-t.interior.x-10, 10);
    else
      ofRect(t.x+5, t.y+t.h, t.w-10, 10);
  }
}

void bGroup::drawIndicators(block & held, block & k)
{
  dropBlock db=underWhich(k, held);
  if(db.found()){
    indicate(db);
  }
  if(!db.found()){
    db=underWhich(held, k);
    if(db.found()&&db.index==db.inThis->size()){
      indicate(db);
    }
  }
}

void bGroup::drawBase(int _x, int _y)
{
	//base.drawSelected();
  y=_y;
	base.draw(_x,_y);
}

void bGroup::draw(){
	//-------- if the blocks are not grabbed, and the dds are not open, draw the blocks
	for (unsigned int i=0; i<size(); i++) {
		if (!blocks[i].bGrabbed&&!blocks[i].ddOpen) {
			blocks[i].draw();
		}
	}
}

void bGroup::drawForeground(){
	//******** if a block is currently being held, draw it on different layers, depending on Circumstances
	//-------- draw all the shadows
	for (unsigned int i=0; i<blocks.size(); i++) {
		if (blocks[i].bGrabbed) {
			blocks[i].drawShadow();
		}
	}
	//-------- draw all the grabbed blocks
	for (unsigned int i=0; i<blocks.size(); i++) {
		if (blocks[i].bGrabbed) {
			blocks[i].draw();
		}
	}
	
	//-------- draw ungrabbed statement blocks
	for (unsigned int i=0; i<blocks.size(); i++) {
		if (blocks[i].type==BLK_VAL&&!blocks[i].bGrabbed) {
			blocks[i].draw();
		}
	}
	//-------- draw grabbed statement blocks
	for (unsigned int i=0; i<blocks.size(); i++) {
		if (blocks[i].type==BLK_VAL&&blocks[i].bGrabbed) {
			blocks[i].draw();
		}
	}
	
	//-------- Not deprecated, displays blocks when dd clicked.
	for (unsigned int i=0; i<blocks.size(); i++) {
		if (blocks[i].ddOpen) {
			blocks[i].draw();
		}
	}
  
  if(held.bGrabbed){
    held.drawShadow();
    held.draw();
  }
  
  if(inHand&&held.bGrabbed){
    drawIndicators(held, base);
    for (unsigned int i=0; i<size(); i++) {
      drawIndicators(held,blocks[i]);
    }
  }
  
  
}