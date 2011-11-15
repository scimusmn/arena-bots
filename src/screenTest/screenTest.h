/*
 *  screenTest.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "turtle/turtle.h"
#include "turtleAction/turtleAction.h"

class block;

enum ofBlockActions {
  OF_BLOCK_NULL_ACT,OF_BLOCK_MOVE, OF_BLOCK_TURN, OF_BLOCK_WHILE, OF_BLOCK_IF,OF_BLOCK_REPEAT
};

class robotTest {
protected:
  vector<turtleAction> actions;
  bool bTesting;
  bool bRunning;
  ofTurtle turtle;
  block * base;
public:
  void setup();
  
  void parseActions(block * t);
  
  void startTesting(block * t);
  
  void stopTesting();
  
  bool isTesting();
  
  void startTurtle();
  
  bool idleTurtle();
  
  void pauseTurtle();
  
  void resetTurtle();
  
  bool turtleIsRunning();
  
  void drawCurrentBlock();
  
  void draw(int x, int y, int w, int h);
};