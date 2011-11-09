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

class baseBlock : public block {
protected:
public:
  ofButton uploadBut;
  baseBlock();
  baseBlock & operator=(baseBlock &t);
  void draw(int _x, int _y);
};