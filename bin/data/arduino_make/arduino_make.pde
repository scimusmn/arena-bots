#define IS_ROBOT 0x06
#define ROBOT_NUMBER 0x0C
#define REQUEST_IDENT 0xff

  #include "AFMotor.h"
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
  Serial.begin(9600);
	robot.setup();

}

void loop(){
  if(Serial.available()&&Serial.read()==REQUEST_IDENT){
    Serial.print(IS_ROBOT,BYTE);
    Serial.print(ROBOT_NUMBER,BYTE);
    Serial.print(101,BYTE);
    Serial.print("\n");
  }
  
  delay(500);
  if(running&&!thru){
    robot.forward(4 );

  }
    robot.end();

  thru=true;
}
