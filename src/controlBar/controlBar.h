/*
 *  controlBar.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "ofMain.h"
#include "ofExtended.h"
#include "demoAnim.h"

#include "serialCheck.h"

class controlBar {
protected:
  bGroup * blocks;
  sbGroup * sideBar;
  
  demoAnim anim;
  
  ofButton clearBut;
	ofButton redoBut;
	ofButton undoBut;
  dallasButton  demo;
public:
  //controlBar();
  void setup(bGroup * bG, sbGroup * sbG);
  void draw(int x, int y, int w, int h);
  void update();
  bool clickDown(int x, int y);
  bool clickUp();
};
