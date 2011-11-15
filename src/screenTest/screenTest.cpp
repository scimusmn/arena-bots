/*
 *  screenTest.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "screenTest.h"
#include "blocks.h"

extern ofColor black, white, blue, red, orange, yellow, gray;

ofTimer actionTimer;

block * currentBlock=0;

void robotTest::setup()
{
  turtle.setup("maps/map_2.jpg");
  bTesting=false;
  bRunning=false;
}

void robotTest::parseActions(block * t)
{
  actions.clear();
  for (unsigned int i=0; i<t->blocksOn.size(); i++) {
    actions.push_back(turtleAction(&t->blocksOn[i],&turtle));
  }
}


void robotTest::startTesting(block * t)
{
  parseActions(t);
  base=t;
  bTesting=true;
}

void robotTest::stopTesting()
{
  bTesting=false;
  actions.clear();
}

bool robotTest::isTesting()
{
  return bTesting;
}

void robotTest::startTurtle()
{
  bRunning=true;
  actionTimer.set(.01);
  actionTimer.run();
}

bool robotTest::idleTurtle()
{
  bool ret=0;
  if(actionTimer.expired()){
    for (unsigned int i=0; i<actions.size()&&!ret; i++) {
      ret=actions[i].execute();
    }
    if(!ret) pauseTurtle();
  }
  return ret;
}

void robotTest::pauseTurtle()
{
  bRunning=false;
  actionTimer.pause();
  currentBlock=0;
}

void robotTest::resetTurtle()
{
  for (unsigned int i=0; i<actions.size(); i++) {
    actions[i].reset();
  }
}

bool robotTest::turtleIsRunning()
{
  return bRunning;
}

void robotTest::drawCurrentBlock()
{
  if(currentBlock){
    currentBlock->drawSelected();
    //currentBlock->draw();
  }
}

void robotTest::draw(int x, int y, int w, int h)
{
  ofSetColor(0x33, 0x33, 0x33);
  ofRect(0, 0, ofGetWidth(), ofGetHeight());
  
  ofSetColor(black);
  drawHatching(0, 0, ofGetWidth(), ofGetHeight(), 15,1);
  
  ofPushMatrix();
  ofTranslate(x,y, 0);
  ofScale(double(w)/(double)turtle.map.width, double(h)/double(turtle.map.height), 1);
  ofSetColor(255, 255, 255);
  turtle.map.draw(0, 0);
  
  turtle.draw(0, 0);
  ofPopMatrix();
}
