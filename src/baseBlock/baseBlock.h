/*
 *  baseBlock.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/9/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "../blocks.h"

class bGroup;

class baseBlock : public block {
protected:
  ofPoint butArea;
  bGroup * group;
public:
  ofButton uploadBut;
  baseBlock();
  baseBlock & operator=(baseBlock &t);
  void draw(int _x, int _y);
  bool clickDown(int _x, int _y);
  bool newClickUp( int _x, int _y);
  void setup(bGroup * grp);
};