/*
 *  turtleAction.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofExtended.h"

class block;
class ofTurtle;

enum actionType {
  TURTLE_NULL,TURTLE_MOVE, TURTLE_TURN, TURTLE_WHILE, TURTLE_IF,TURTLE_REPEAT
};

enum action_word {
  ACT_NORMAL, LFT_SNS, RT_SNS, FRNT_SNS, ACT_FOREVER
};

/*struct method {
  actionType type;
  action_word guard;
  double goal, current;
  bool data
  bool negate;
  bool bDone;
  method(){
    type=TURTLE_NULL;
    guard=ACT_NORMAL;
    negate=data=false;
  }
  void set(string t);
  void set(double goal);
  bool state();
  void reset();
  bool executed();
};*/

class turtleAction {
  vector<turtleAction> inside;
  actionType type;
  action_word guard;
  ofTurtle * turtle;
  block * parentBlock;
  double nGoal,nCurrent;
  bool bData;
  double data[2];
  bool bNegate;
  string dataStr;
  bool bExecuted;
  bool bParsed;
  turtleAction(block * prnt, ofTurtle * bdy);
  
  bool execute();
  
  bool executeGuardedAction();
  void resetGuardedActions();
  
  bool assess();
  
  void parse(string str);
  void reset();
  
  //---- register, then parse
  void registerAction(string str);
  void parseAction();
  void handleWord();
  
  int direction();
  
  double evalVar(string str);
  double parseNumber(string str);
};
