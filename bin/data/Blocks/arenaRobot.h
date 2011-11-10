/*
 *  arenaRobot.h
 *  robotBlocks
 *
 *  Created by Exhibits on 7/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _ARENA_ROBOT
#define _ARENA_ROBOT

#include <WProgram.h>
#include "AFMotor.h"
#include "roboSteps.h"
#include "roboSense.h"

class robut : public roboMotors, public roboSense {
  bool justChk;
public:
  robut():roboMotors(2,1),roboSense(){
    justChk=false;
  }
  void setup(){
    Serial.begin(9600);
    roboMotors::setup();
    roboSense::setup();
    Serial.println("Hello!");
    //Wire.requestFrom(0x50 >> 1,1);
  }
  void start(){
    roboMotors::start();
  }
  void end(){
    running=false;
    roboMotors::end();
  }
  /*void followLine(){
    while(!readLinePosition()){
      Wire.requestFrom(0x50 >> 1,1);
      leftMotor.step(1, BACKWARD, SINGLE); 
      rightMotor.step(1, BACKWARD, SINGLE); 
    }
    if(dirScore<0) leftStep(-dirScore*2,SINGLE);
    else if(dirScore>0) rightStep(dirScore*2,SINGLE);
  }*/   
  
} robot;

#endif