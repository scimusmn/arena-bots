/*
 *  demoAnim.cpp
 *  arenaBot
 *
 *  Created by Exhibits on 11/7/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "demoAnim.h"

void demoAnim::setup(bGroup * bG, sbGroup * sbG)
{
  blocks=bG;
  sideBar=sbG;
  
  skipBut.setup(300, 100, "images/skipBut.png");
  anim.setup();
  animStep=0;
  pointer.loadImage("images/pointer.png");
}

void demoAnim::animationStepRequested(ofXML & animXML)
{
  
}

ofInterObj * demoAnim::searchForObject(ofTag & tag, int & _x, int & _y)
{
  
}

ofInterObj * demoAnim::searchBlock(vector<string> spl, block & b, int offset)
{
  
}
