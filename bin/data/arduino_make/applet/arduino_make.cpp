#include "WProgram.h"
void setup();
void loop();
#define IS_ROBOT 0x06
#define ROBOT_NUMBER 0x0C

  #include "AFMotor.h"
#include "arenaRobot.h"
  #include <AFMotor.h>
#include "arenaRobot.h"
  

  #include <AFMotor.h>
#include "arenaRobot.h"
  

  

  

  



bool thru=false;
bool running=false;

void changeRun(){
  robot.toggleRun();
  running=robot.isRunning();
  if(!running) robot.end();
  thru=false;
}

void setup(){
  attachInterrupt(0, changeRun, RISING);
  Serial.begin(9600);
	robot.setup();
	robot.setup();
	
	robot.setup();
	
	
	
	

}

void loop(){
  Serial.print(IS_ROBOT,BYTE);
  Serial.print(ROBOT_NUMBER,BYTE);
  Serial.print(102,BYTE);
  Serial.print("\n");
  
  if(running&&!thru){
    robot.forward(8 );
robot.rightTurn(90 );
robot.forward(8 );
robot.leftTurn(90 );
robot.forward(12 );
robot.leftTurn(90 );
robot.forward(12 );
robot.rightTurn(90 );

  }
    robot.end();
  
  
  

  thru=true;
}
