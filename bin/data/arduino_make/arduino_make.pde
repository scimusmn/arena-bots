#include <stdlib.h>

  #include "AFMotor.h"
#include "arenaRobot.h"

bool thru=false;

void setup(){
	robot.setup();

}

void loop(){
  
  if(!thru){
    robot.forward(2 );

  }
    robot.end();

  thru=true;
}
