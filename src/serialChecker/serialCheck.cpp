/*
 *  serialCheck.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/2/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "serialCheck.h"

#define IS_ROBOT 0x06
#define ROBOT_NUMBER 0x0C
#define REQUEST_IDENT 0x04

int CURRENT_ROBOT_NUMBER=0;

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_ SerialDev //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_

serialDevice::serialDevice(string prtNm)
{
  portName=prtNm;
  
#if defined( TARGET_OSX )
  if(prtNm.substr(0,7) != "tty.usb" ) type=NOT_USB_SERIAL;
  else if( prtNm.substr(0,8) != "tty.usbm" ) type=ARD_UNO;
  else if( prtNm.substr(0,8) != "tty.usbs" ) type=ARD_DUEM;
#elif defined( TARGET_WIN32 )
  
#endif
}

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_ SerialChk //_-_-_-_-_//_-_-_-_-_//_-_-_-_-_

serialCheck::serialCheck()
{
  serial.setVerbose(false);
  //ofSetLogLevel(OF_LOG_NOTICE);
  numDevices=0;
  checkTimer.set(1);
  checkTimer.run();
  bAvailable=bJustFound=bJustLost=false;
  MODE=0;
	waitForData=2;
	data[0]=data[1]=data[2]=0;
  
  report.loadFont("fonts/DinC.ttf");
  report.setMode(OF_FONT_CENTER);
  report.setSize(70);
  
  //start();
}

serialCheck::~serialCheck(){
  stop();
  devices.clear();
}

bool serialCheck::isAvailable()
{
  bool ret=0;
  if(lock()){
    ret=bAvailable;
    unlock();
  }
  return ret;
}

void serialCheck::drawWaitScreen()
{
  if(!isAvailable()){
    ofSetColor(0, 0, 0,196);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    string printOut="Connect the robot to begin";
    if(bIdent) printOut="Identifying: Do not unplug";
    ofSetColor(255, 255, 255);
    report.drawString(printOut, ofGetWidth()/2, ofGetHeight()/2);
  }
}

void serialCheck::checkAvailability()
{
  if(checkTimer.expired()){
    serial.enumerateDevices();
    if(serial.numDevices()!=numDevices){
      if(numDevices<serial.numDevices()&&!bAvailable){
        numDevices=serial.numDevices();
        cout << "Checking for robots:\n";
  #if defined( TARGET_OSX )
        for (int i=0; i<serial.numDevices(); i++) {
          if(serial.deviceNameByNumber(i).substr(0,7) == "tty.usb" ){
            bIdent=true;
            ofTimer delay;
            delay.set(.5);
            delay.run();
            cout << "waiting to setup serial port "+serial.deviceNameByNumber(i)+"\n";
            while(delay.running());
            serial.setup("/dev/"+serial.deviceNameByNumber(i), 9600);
            if(getDeviceNumber()){
              bAvailable=true;
              bJustFound=true;
            }
            bIdent=false;
            serial.close();
          }
        }
  #elif defined( TARGET_WIN32 )
        for (int i=0; i<serial.numDevices(); i++) {
          serial.setup(serial.deviceNameByNumber(i), 9600);
          if(getDeviceNumber()){
            lock();
            bAvailable=true;
            bJustFound=true;
            unlock();
          }
          serial.close();
        }
  #endif
      
      }
      else if(numDevices>serial.numDevices()&&bAvailable){
        nCurrentDevice=-1;
        numDevices=serial.numDevices();
        bAvailable=false;
        bJustLost=true;
        for (int i=0; i<serial.numDevices(); i++)
          cout << serial.deviceNameByNumber(i) << endl;
      }
      else if(numDevices>serial.numDevices()&&!bAvailable){
        nCurrentDevice=-1;
        numDevices=serial.numDevices();
        bAvailable=false;
        bJustLost=true;
        for (int i=0; i<serial.numDevices(); i++)
          cout << serial.deviceNameByNumber(i) << endl;
      }
    }
    checkTimer.reset();
  }
}

bool serialCheck::getDeviceNumber()
{
  bool ret=false;
  ofTimer timeout;
  timeout.set(.5);
  timeout.run();
  serial.flush();
  cout << "waiting for data from serial\n";
  while(timeout.running());
  serial.writeByte('a');
  timeout.set(.5);
  while (!timeout.expired()&&!ret) {
    if(!serial.available()) serial.writeByte('a');
    else if(serial.available()){
      byteRead=serial.readByte();
      cout << int(byteRead) << "here" << endl;
      if(byteRead==IS_ROBOT) cout << "serial device is a robot\n";
      switch (MODE) {
        case IS_ROBOT:
          data[2-waitForData--]=byteRead;
          break;
        case 0:
          if (byteRead==IS_ROBOT) {
            MODE=byteRead;
            waitForData=2;
          }
          break;
        default:
          break;
      }
      if(waitForData==0) {
        switch (data[0]) {
          case ROBOT_NUMBER:{
            lock();
            CURRENT_ROBOT_NUMBER=nCurrentDevice=data[1];
            cout <<"Robot number is " << int(nCurrentDevice)<<endl;
            unlock();
            if(nCurrentDevice>=100&&nCurrentDevice<=110) ret=true;
          }
            break;
            
          default:
            break;
        }
        MODE=0;
        data[0]=data[1]=data[2]=0;
      }
    }
  }
  return ret;
}

void serialCheck::addDevice(string prtNm)
{
  devices.push_back(serialDevice(prtNm));
}

void serialCheck::deviceRemoved()
{
  
}

int serialCheck::deviceNumber()
{
  int ret=0;
  if(!isThreadRunning()||lock()){
    ret=CURRENT_ROBOT_NUMBER;
    if(isThreadRunning()) unlock();
  }
  return ret;
}

void serialCheck::threadCheckAvailability()
{
  if (checkTimer.expired()) {
    start();
  }
}

bool serialCheck::justFoundDevice()
{
  bool ret=bJustFound;
  bJustFound=false;
  return ret;
}

bool serialCheck::justLostDevice()
{
  bool ret=bJustLost;
  bJustLost=false;
  return ret;
}

void serialCheck::threadedFunction(){
  
  //while( isThreadRunning() != 0 ){
    //if( lock() ){
    checkAvailability();
    stop();
    //  unlock();
    //}
  //}
}
