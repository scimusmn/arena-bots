/*
 *  turtleAction.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "turtleAction.h"
#include "blocks.h"

#include "../turtle/turtle.h"

#include "../evaluateExpression/evaluate.h"

extern int pixPerInch;


turtleAction::turtleAction(block * prnt, ofTurtle * bdy)
{
  parentBlock=prnt;
  turtle=bdy;
  parse(parentBlock->origTag.getNode("action", 0).getValue());
  for (unsigned int i=0; parentBlock->blocksIn.size(); i++) {
    inside.push_back(turtleAction(&parentBlock->blocksIn[i], turtle));
  }
}

int turtleAction::direction()
{
  return nGoal/abs(nGoal);
}

bool turtleAction::assess()
{
  bool ret=false;
  switch (guard) {
    case ACT_NORMAL:
      if(abs(nCurrent)<abs(nGoal)){
        ret=true;
      }
      break;
    case LFT_SNS:
      if(turtle->leftIsClear(nGoal)) ret=true;
      break;
    case FRNT_SNS:
      if(turtle->leftIsClear(nGoal)) ret=true;
      break;
    case ACT_FOREVER:
      ret=true;
      break;
    default:
      break;
  }
  return ret;
}

void turtleAction::reset()
{
  bExecuted=false;
  nCurrent=0;
}

bool turtleAction::executeGuardedAction()
{
  bool ret=0;
  for (unsigned int i=0; i<inside.size()&&!ret; i++) {
    ret=inside[i].execute();
  }
  return ret;
}

bool turtleAction::resetGuardedActions()
{
  bool ret=0;
  for (unsigned int i=0; i<inside.size(); i++) {
    inside[i].reset();
  }
  return ret;
}

bool turtleAction::execute()
{
  bool ret=true;
  if(!bExecuted){
  switch (type) {
    case OF_BLOCK_MOVE:
      if(assess()){
        turtle->move(direction());
        nCurrent+=direction();
      }
      else bExecuted=true;
      //actionTime.set(0.01);
      break;
    case OF_BLOCK_TURN:
      if(assess()){
        turtle->turn(direction());
        nCurrent+=direction();
      }
      else bExecuted=true;
      //actionTime.set(0.01);
      break;
    case OF_BLOCK_WHILE:
      if(assess()){
        if(!(ret=executeGuardedAction())){
          resetGuardedActions();
        }
      }
      else bExecuted=true;
      break;
      
      
    case OF_BLOCK_IF:
      if(assess()||bData){
        bData=true;
        if(!(ret=executeGuardedAction()))
          bExecuted=true,bData=false;
      }
      else bExecuted=true;
      break;
      
      
    case OF_BLOCK_REPEAT:
      /*if(!dataStr.compare("$forever")){
        if(interpretDataStr(bA.dataStr)){
          if(!idleSequence(&nxt))
            resetActions(nxt,true);
          ret=true;
        }
        else resetActions(nxt);
      }
      else{
        if(bA.data[0]>bA.data[1]){
          if(!idleSequence(&nxt)){
            bA.data[1]++;
            resetActions(nxt,true);
          }
        }
        else bA.bExecuted=true,resetActions(nxt,true);
      }*/
      if(assess()){
        if(!(ret=executeGuardedAction())){
          nCurrent++;
          resetGuardedActions();
        }
      }
      else bExecuted=true,resetGuardedActions();
      break;
    default:
      ret=false;
      break;
  }
}

void turtleAction::parse(string str)
{
  registerAction(str);
  parseAction();
  handleWord();
}

void turtleAction::registerAction(string str)
{
  vector<string> splt=ofSplitString(str, ":");
  if(splt.size()>1){
    if(splt[0]=="move") type=TURTLE_MOVE;
    else if(splt[0]=="turn") type=TURTLE_TURN;
    else if(splt[0]=="while") type=TURTLE_WHILE;
    else if(splt[0]=="if") type=TURTLE_IF;
    else if(splt[0]=="repeat") type=TURTLE_REPEAT;
    dataStr=splt[1];
  }
}

void turtleAction::handleWord()
{
  if(type==TURTLE_IF||type==TURTLE_WHILE||type==TURTLE_REPEAT){
    vector<string> spl=ofSplitString(dataStr, "$[]()");
    for (unsigned int i=0; i<spl.size(); i++) {
      if(spl[i]=="!") bNegate=true;
      else if(spl[i]=="front"){
        guard=FRNT_SNS;
        nGoal=ofToFloat(spl[i+1])*pixPerInch;
      }
      else if(spl[i]=="leftPath"){
        guard=LFT_SNS;
        nGoal=ofToFloat(spl[i+1])*pixPerInch;
      }
      else if(spl[i]=="forever") guard=ACT_FOREVER;
    }
  }
}

double turtleAction::evalVar(string str)
{
  double ret=0;
  vector<string> spl=ofSplitString(str, "$[]()");
  for (unsigned int i=0; i<spl.size(); i++) {
    if(spl[i]=="dd") ret=parentBlock->ddGroup[ofToInt(spl[i+1])].getValue();
    else if(spl[i]=="ppi") ret=pixPerInch;
  }
  return ret;
}

double turtleAction::parseNumber(string str)
{
  vector<evalData> eval=evaluateNumbers(dataStr);
  string t;
  for (unsigned int i=0; i<eval.size(); i++) {
    if(!eval[i].isNumber){
      eval[i].number=evalVar(eval[i].varName);
      eval[i].varName=ofToString(eval[i].number,0);
      eval[i].isNumber=true;
    }
    t+=eval[i].varName+eval[i].nextOperator;
  }
  eval=evaluateNumbers(t);
  return eval[0].number;
}

void turtleAction::parseAction()
{
  if(!bParsed){
    switch (type) {
      case OF_BLOCK_MOVE:
        data[0]=parseNumber(dataStr);
        break;
      case OF_BLOCK_TURN:
        data[0]=parseNumber(dataStr);
        break;
        /*case OF_BLOCK_WHILE:
         action.data[0]=parseNumber(action.dataStr);
         break;
         case OF_BLOCK_IF:
         action.data[0]=parseNumber(action.dataStr);
         break;*/
      case OF_BLOCK_REPEAT:
        if(dataStr!="$forever")
          data[0]=parseNumber(dataStr);
        break;
      default:
        break;
    }
    bParsed=true;
  }
}