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


void controlBar::setup(bGroup * bG, sbGroup * sbG)
{
  blocks=bG;
  sideBar=sbG;
  clearBut.setup(64,64,"images/deleteBlocks2.png");
  redoBut.setup(64, 64, "images/redo.png");
	undoBut.setup(64, 64, "images/undo.png");
  demo.setup("View demo", "fonts/Arial.ttf", 20);
  
  anim.setup(blocks, sideBar);
}

void controlBar::draw(int x, int y, int w, int h)
{
  
}

void controlBar::update()
{
  redoBut.setAvailable(blocks.redoAvailable());
	undoBut.setAvailable(blocks.undoAvailable());
}

bool controlBar::clickDown(int x, int y)
{
  if (clearBut.clickDown(x, y)) {
    blocks->clear();
  }
  
  if(demo.clickDown(x, y)){
    blocks->clear();
    animStep=0;
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
