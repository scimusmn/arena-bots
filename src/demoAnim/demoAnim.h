/*
 *  demoAnim.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "../sideBar/sideBar.h"

class demoAnim {
protected:
  int animStep;
  ofXML animXML;
  ofButton skipBut;
  ofVMouse anim;
	ofImage pointer;
  
  bGroup * blocks;
  sbGroup * sideBar;
public:
  void setup(bGroup * bG, sbGroup * sbG);
  void animationStepRequested(ofXML & animXML);
  ofInterObj * searchForObject(ofTag & tag, int & _x, int & _y);
  ofInterObj * searchBlock(vector<string> spl, block & b, int offset);

};