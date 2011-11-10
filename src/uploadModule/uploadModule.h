/*
 *  uploadModule.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/10/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "blockGroup.h"
#include "ofxSystemCall.h"

class uploadModule {
protected:
  bGroup * blocks;
  ofSystemCall command;
	ofProgressSpinner spinner;
  ofFont label;
public:
  void setup(bGroup * blks);
  void upload();
  void drawUploadWait();
  bool isUploading();
  bool clickDown(int _x, int _y);
};