  #include "AFMotor.h"
#include "arenaRobot.h"
  


bool thru=false;

void setup(){
	robot.setup();
	

}

void loop(){
  
  if(!thru){
    robot.forward(6 );
robot.forward(0 );

  }
    robot.end();
  

  thru=true;
}
