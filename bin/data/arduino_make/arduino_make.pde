#define IS_ROBOT 0x06
#define ROBOT_NUMBER 0x0C
#define REQUEST_IDENT 0xff

  #include "AFMotor.h"
#include "arenaRobot.h"
  #include "AFMotor.h"
#include "arenaRobot.h"
  #include "AFMotor.h"
#include "arenaRobot.h"
  #include <AFMotor.h>
#include "arenaRobot.h"
  #include <AFMotor.h>
#include "arenaRobot.h"


bool thru=false;
bool running=false;
bool bInit=false;

bool change=false;

void changeRun(){
  robot.toggleRun();
  running=robot.isRunning();
  if(!running) robot.end();
  thru=false;
}

void setup(){
  attachInterrupt(0, changeRun, RISING);
	robot.setup();
	robot.setup();
	robot.setup();
	robot.setup();
	robot.setup();

}

void loop(){
  
  delay(500);
  if(running&&!thru){
    while(robot.isRunning()){ 	robot.doubleStep(2,BACKWARD,SINGLE);
	if(robot.frontSensor(500)){
	  		if(!robot.leftSensor(300)){
		  			robot.leftTurn(180 );
		  }
		robot.rightTurn(90 );
	  }
}

  }
  
  thru=true;
}
