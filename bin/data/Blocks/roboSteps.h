/*
 *  roboSteps.h
 *  robotBlocks
 *
 *  Created by Exhibits on 7/11/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#ifndef _ARENA_MOT
#define _ARENA_MOT

#include <WProgram.h>
#include "AFMotor.h"

enum robotDirection {
  R_LEFT, R_RIGHT
};

class roboMotors {
protected:
  float robutDiameter;
  float rCirc,wCirc;
  float wheelDiameter;
  float inchesPerStep;
  int stepsPerRot;
  int speed;
  AF_Stepper leftMotor;
  AF_Stepper rightMotor;
public:
  roboMotors(int left, int right){
    stepsPerRot=200;
    leftMotor.init(stepsPerRot,left);
    rightMotor.init(stepsPerRot,right);
    robutDiameter=4.28;
    wheelDiameter=2.375;
    rCirc=robutDiameter*M_PI;
    wCirc=wheelDiameter*M_PI;
    inchesPerStep=wCirc/((float)stepsPerRot);
  }
  void setup(){
    leftMotor.setSpeed(100);
    rightMotor.setSpeed(100);
    start();
  }
  void start(){
    leftMotor.release();
    rightMotor.release();
  }
  void end(){
    leftMotor.release();
    rightMotor.release();
  }
  void doubleStep(int steps, int direction, int style) {
    while (steps--) {
      leftMotor.step(1, direction, style); 
      rightMotor.step(1, direction, style); 
    }
  }
  void forward(float inches) {
    int steps=inches/inchesPerStep;
    doubleStep(steps,BACKWARD,DOUBLE);
  }
  void backward(float inches) {
    int steps=inches/inchesPerStep;
    doubleStep(steps,FORWARD,DOUBLE);
  }
  void leftStep(int steps, int style) {
    while (steps--) {
      leftMotor.step(1, FORWARD, style); 
      rightMotor.step(1, BACKWARD, style); 
    }
  }
  void leftTurn(float degrees) {
    int steps=(rCirc*(degrees/360))/inchesPerStep;
    leftStep(steps,DOUBLE);
  }
  void rightStep(int steps, int style) {
    while (steps--) {
      leftMotor.step(1, BACKWARD, style); 
      rightMotor.step(1, FORWARD, style); 
    }
  }
  void rightTurn(float degrees) {
    int steps=(rCirc*(degrees/360))/inchesPerStep;
    rightStep(steps,DOUBLE);
  }
  void rollingTurn(int steps, int augment){
    float leftSteps=steps-augment, rightSteps=steps+augment;
    float percSteps=(leftSteps/rightSteps);
    if(percSteps>=1) steps=rightSteps;
    else steps=leftSteps;
    while (steps--) {
      if(leftSteps--)
        leftMotor.step(1, BACKWARD,DOUBLE);
      else leftMotor.release();
      if(rightSteps--) 
        rightMotor.step(1, BACKWARD,DOUBLE); 
      else rightMotor.release();
    }
  }
};

#endif