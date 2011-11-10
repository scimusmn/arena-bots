#define IS_ROBOT 0x06
#define ROBOT_NUMBER 0x0C

  #include "AFMotor.h"
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

}

void loop(){
  Serial.print(IS_ROBOT,BYTE);
  Serial.print(ROBOT_NUMBER,BYTE);
  Serial.print(206,BYTE);
  Serial.print("\n");
  
  if(running&&!thru){
    while(robot.isRunning()){ 	robot.forward(2 );
}

  }
  
  thru=true;
}
