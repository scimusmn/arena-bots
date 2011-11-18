/*
 *  screenTest.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "screenTest.h"
#include "../baseBlock/baseBlock.h"

extern ofColor black, white, blue, red, orange, yellow, gray;

ofTimer actionTimer;

block * currentBlock=0;

void robotTest::setup(baseBlock * t)
{
  turtle.setup("maps/map_3.jpg");
  bTesting=false;
  bRunning=false;
  bFinished=false;
  
  display.loadFont("fonts/DinC.ttf");
  display.setSize(70);
  display.setMode(OF_FONT_CENTER);
  
  endBut.setup("Edit program", 25);
  resetBut.setup("Reset virtual robot", 25);
  
  controlBar.height=endBut.h*2;
  controlBar.width=ofGetWidth();
  base=t;
}

void robotTest::parseActions(baseBlock * t)
{
  actions.clear();
  for (unsigned int i=0; i<t->blocksOn.size(); i++) {
    actions.push_back(turtleAction(&t->blocksOn[i],&turtle));
  }
}


void robotTest::startTesting(baseBlock * t)
{
  parseActions(t);
  resetTurtle();
  resetBut.setTitle("Reset virtual robot");
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
    if(!ret) pauseTurtle(),bFinished=true;;
    if(turtle.checkPoints()) pauseTurtle();
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
  turtle.reset();
  bFinished=false;
  for (unsigned int i=0; i<actions.size(); i++) {
    actions[i].reset();
  }
}

bool robotTest::turtleIsRunning()
{
  return bRunning;
}

bool robotTest::turtleCrashed()
{
  return turtle.crashed();
}

bool robotTest::finishedActions(){
  return bFinished;
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
  ofRectangle & cBar=controlBar;
  int mapPad=25;
  
  mapArea=ofRectangle(x,y,w,h);
  
  ofSetColor(gray);
  ofRect(mapArea.x,mapArea.y,mapArea.width,mapArea.height);
  ofSetColor(black);
  drawHatching(mapArea.x,mapArea.y,mapArea.width,mapArea.height, 50,50);
  
  ofSetColor(yellow);
  ofRect(mapArea.x+mapArea.width, mapArea.y, 2, mapArea.height);
  
  drawMap(mapArea.x+mapPad,mapArea.y+mapPad,mapArea.width-mapPad*2,mapArea.height-mapPad*2);
}

void robotTest::drawMap(int x, int y, int w, int h)
{
  ofPushMatrix();
  ofTranslate(x,y, 0);
  ofScale(double(w)/(double)turtle.map.width, double(h)/double(turtle.map.height), 1);
  ofSetColor(255, 255, 255);
  turtle.map.draw(0, 0);
  
  turtle.draw(0, 0);
  ofPopMatrix();
}

void robotTest::drawForeground()
{
  if(turtle.crashed()){
    ofSetColor(black.opacity(.75));
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofSetColor(white);
    display.drawString("You screwed up.", ofGetWidth()/2, ofGetHeight()/2);
    endBut.setTextSize(50);
    resetBut.setTextSize(50);
    endBut.draw((ofGetWidth()/2-endBut.w)/2, 3*ofGetHeight()/4);
    resetBut.draw((3*ofGetWidth()/2-resetBut.w)/2, 3*ofGetHeight()/4);
  }
}

void robotTest::drawControlBar(int x, int y)
{
  ofRectangle & cBar=controlBar;
  cBar.width=mapArea.width;
  cBar.x=x,cBar.y=y;
  ofSetColor(black);
  ofRect(cBar);
  
  ofSetColor(gray);
  //drawHatching(cBar.x, cBar.y, cBar.width, cBar.height, 85,80);
  drawBorder(cBar);
  
  ofSetColor(yellow);
  ofRect(cBar.x+cBar.width/2, cBar.y, 2, cBar.height);
  
  endBut.setTextSize(19);
  resetBut.setTextSize(19);
  if(!turtleIsRunning()&&!turtleCrashed()&&(ofGetElapsedTimeMillis()/500)%2) trimmedRect(resetBut.x-5, resetBut.y-5, resetBut.w+10, resetBut.h+10, .33);
  endBut.draw(cBar.x+(cBar.width/2-endBut.w)/2, cBar.y+(cBar.height-endBut.h)/2);
  resetBut.draw(cBar.x+(3*cBar.width/2-resetBut.w)/2, cBar.y+(cBar.height-resetBut.h)/2);
}

bool robotTest::mouseLockout()
{
  return isTesting();
}


bool robotTest::clickDown(int _x, int _y)
{
  if (isTesting()) {
    if(endBut.clickDown(_x, _y))
      pauseTurtle(),resetTurtle(),stopTesting(),base->setDrawTest(true);
    if(resetBut.clickDown(_x, _y)){
      if(turtleCrashed()||turtleIsRunning()||finishedActions()){
        resetTurtle();
        resetBut.setTitle("Start virtual robot");
      }
      else {
        startTurtle();
        resetBut.setTitle("Reset virtual robot");
      }
    }
  }
  else{
    if(base->testBut.clickDown(_x,_y)){
      startTesting(base);
      startTurtle();
      base->setDrawTest(false);
    }
  }
}


bool robotTest::clickUp()
{
  endBut.clickUp();
  resetBut.clickUp();
  base->testBut.clickUp();
}

