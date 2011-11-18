/*
 *  uploadModule.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/10/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "uploadModule.h"

void uploadModule::setup(bGroup * blks)
{
  blocks=blks;
  label.loadFont("fonts/DinC.ttf");
  label.setSize(70);
  label.setMode(OF_FONT_CENTER);
}

void uploadModule::upload()
{
  //--------- Generate the file which we will compile and upload to the arduino
  blocks->writeFile("arduino_make/arduino_make.pde");
  
  //--------- once we've generated the file, compile and upload with one of teh following scripts
#if defined( TARGET_OSX ) || defined( TARGET_LINUX )
  command.run(ofToDataPath("arduino_make/upload.sh"));
#else
  command.run(ofToDataPath("\"data\\arduino_make\\build.bat\""));
#endif
  
  //--------- unpress the upload button
  blocks->base.uploadBut.clickUp();
}

void uploadModule::drawUploadWait()
{
  if (command.isRunning()) {
    ofSetColor(0, 0, 0,128);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
		ofSetColor(255, 255, 255);
		spinner.draw((ofGetWidth())/2,ofGetHeight()/2, 300);
		label.drawString("Uploading: do not unplug", ofGetWidth()/2, ofGetHeight()/4);
	}
}

void uploadModule::stopUpload(){
  command.stop();
}

bool uploadModule::isUploading()
{
  return command.isRunning();
}

bool uploadModule::clickDown(int _x, int _y)
{
  bool ret=0;
  if(blocks->base.uploadBut.clickDown(_x, _y)&&!isUploading()){
    ret=true;
    upload();
  }
  return ret;
}

