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
  bAvailable=false;
  MODE=0;
	waitForData=2;
	data[0]=data[1]=data[2]=0;
}

bool serialCheck::isAvailable()
{
  return bAvailable;
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
            ofTimer delay;
            delay.set(.5);
            delay.run();
            cout << "waiting to setup serial port "+serial.deviceNameByNumber(i)+"\n";
            while(delay.running());
            serial.setup("/dev/"+serial.deviceNameByNumber(i), 9600);
            if(getDeviceNumber()){
              bAvailable=true;
            }
            serial.close();
          }
        }
  #elif defined( TARGET_WIN32 )
        for (int i=0; i<serial.numDevices(); i++) {
          serial.setup(serial.deviceNameByNumber(i), 9600);
          if(getDeviceNumber()){
            bAvailable=true;
          }
          serial.close();
        }
  #endif
      
      }
      else if(numDevices>serial.numDevices()&&bAvailable){
        nCurrentDevice=-1;
        numDevices=serial.numDevices();
        bAvailable=false;
        for (int i=0; i<serial.numDevices(); i++)
          cout << serial.deviceNameByNumber(i) << endl;
      }
      else if(numDevices>serial.numDevices()&&!bAvailable){
        nCurrentDevice=-1;
        numDevices=serial.numDevices();
        bAvailable=false;
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
            nCurrentDevice=data[1];
            cout <<"Robot number is " << int(nCurrentDevice)<<endl;
            ret=true;
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
  return nCurrentDevice;
}
