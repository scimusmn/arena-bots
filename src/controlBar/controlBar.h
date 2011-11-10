/*
 *  controlBar.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofExtended.h"
#include "demoAnim.h"
#include "blockLoad.h"

#include "serialCheck.h"
#include "uploadModule.h"
#include "../../../dallasEng/dallasEng.h"

class buttonHolder : public ofInterObj {
protected:
  double space;
  double pad;
public:
  buttonHolder();
  ofRectangle area;
  vector<ofInterObj *> objs;
  void addObj(ofInterObj & obj);
  void internalSpace(int space);
  double maxHeight();
  void padding(int pad);
  void draw(int x, int y); 
};

class controlBar {
protected:
  bGroup * blocks;
  sbGroup * sideBar;
  
  demoAnim anim;
  
  dallasButton clearBut;
	ofButton redoBut;
	ofButton undoBut;
  dallasButton  demo;
  
  buttonHolder demoHldr;
  buttonHolder setsHldr;
  buttonHolder undoHldr;
  buttonHolder clearHldr;
  
  ofRectangle buttonBar;
  ofRectangle subBar;
  
  ofFont subtitle;
  
  uploadModule upload;
  
  ofButton skipBut;
  
  serialCheck serChk;
  
  rootGroup sets;
public:
  double x,y,w,h;
  //controlBar();
  void loadBlocks(blockGroup & bg);
  void setup(bGroup * bG, sbGroup * sbG);
  void draw(int x, int y);
  void drawForeground();
  void update();
  void setAvailableButtons();
  bool clickDown(int x, int y, int button=0);
  bool clickUp();
  bool mouseLockout(int button);
};
