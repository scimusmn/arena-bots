/*
 *  testApp_auxDrawing.cpp
 *  robotBlocks
 *
 *  Created by Exhibits on 6/23/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "testApp.h"

extern ofColor black,white,yellow,blue,orange, gray;


/*****************************************************************
 * drawBase_and_Demo(int yPos) :: member of testApp
 *
 *  Description:: function to draw the button to begin the demonstration and the base block 
 *     onto the screen.
 *
 *  Input_________
 *
 *    int yPos :  the y position at which we begin drawing
 *
 *  Output________
 *
 *    NONE :  draws the base and the demo button onto the screen
 *
 */

void testApp::drawBase_and_Demo(int yPos)
{
  
  blocks.drawBase((ofGetWidth()-300)/2, yPos);
  upBut.draw(blocks.base.x+blocks.base.w+10,blocks.base.y+blocks.base.h-50);
  
  
  //-------- Draw the text onto the base block
  ofSetColor(0);
  string baseLabel="1. Connect instruction blocks\n   here";
  ofRectangle one(blocks.base.x+25, blocks.base.y+10+label.stringHeight("Co")+4,label.stringWidth(baseLabel)-5,2);
  label.drawString(baseLabel, blocks.base.x+20, blocks.base.y+10);
  label.setMode(OF_FONT_RIGHT);
  baseLabel="2. Upload instructions";
  ofRectangle two(blocks.base.x+blocks.base.w+upBut.w, blocks.base.y+10+label.stringHeight("Kj")+4,label.stringWidth(baseLabel)-5,2);
  label.drawString(baseLabel, blocks.base.x+blocks.base.w+upBut.w, blocks.base.y+10);
  label.setMode(OF_FONT_LEFT);
  
  //------- Underline the text on the block
  ofSetColor(0);
  ofSetLineWidth(1);
  ofLine(one.x+one.width, one.y, one.x, one.y);
  ofLine(one.x, one.y, one.x, one.y+40);
  ofLine(two.x-two.width, two.y, two.x, two.y);
  ofLine(two.x-2*two.width/3, two.y, two.x-2*two.width/3, upBut.y+upBut.h/4);
  ofLine(upBut.x, upBut.y+upBut.h/4, two.x-2*two.width/3, upBut.y+upBut.h/4);
}

