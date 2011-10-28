#ifndef _ARENA_SENSE
#define _ARENA_SENSE

#include <WProgram.h>
//#include "Wire.h"

class roboSense {
protected:
  int frntSnsr;
  int leftSnsr;
  //int rghtSnsr;
  signed int dirScore;
  bool lastRd[5];
  bool set[7];
  byte pData;
public:
  roboSense(){
    frntSnsr=0;
    //frntRSnsr=1;
    leftSnsr=1;
    //rghtSnsr=3;
    dirScore=0;
    set[5]=set[6]=false;
    for (int i=0; i<5; i++) {
      set[i]=lastRd[i]=false;
    }
    set[3]=true;
  }
  void setup(){
    //Wire.begin();
    //readLinePosition();
  }
  void start(){
  }
  void end(){ 
  }
  bool frontSensor(int num=800){
    return analogRead(frntSnsr)>num;
  }
  /*bool frontRightSensor(int num=800){
    return analogRead(frntRSnsr)>num;
  }*/
  bool leftSensor(int num=800){
    return analogRead(leftSnsr)>num;
  }
  /*bool rightSensor(int num=800){
    return analogRead(rghtSnsr)>num;
  }*/
  void manageSet(bool newSet,bool & out, bool & num, bool & in){
    if(!out){
      if(newSet) num=in=true;
    }
    else{
      if(newSet) out=false,num=in=true;
    }
  }
  void centerRobot(){
    for(int i=0; i<7; i++)
      set[i]=false;
    set[3]=true;
  }
  /*bool readLinePosition(){
    bool ret=false;
    byte data = Wire.receive();
    dirScore=0;
    Serial.println(data,DEC);
    for(signed int i=0;i<5;i++){
      if(lastRd[i]!=bitRead(data,i)){
        if(data>96){
          ret=true;
          if(i<2) manageSet(bitRead(data,i),set[i],set[i+1],set[i+2]);
          if(i>2) manageSet(bitRead(data,i),set[i+2],set[i+1],set[i]);
          if(i==2&&bitRead(data,i)) centerRobot();
        }
      }
      Serial.print(set[i+1]);
      Serial.print(" ");
      lastRd[i]=bitRead(data,i);
    }
    for(int i=0; i<7; i++) dirScore+=set[i]*(i-3);
    Serial.print("\n");
    return ret;
  }*/
};

#endif