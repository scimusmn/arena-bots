/*
 *  blockGroup.h
 *  arenaBot
 *
 *  Created by Exhibits on 11/1/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once
#include "../blocks.h"

/*****************************************************************
 * struct storageState 
 *
 *  Description:: 
 *
 *
 *  Vars:
 *
 *    vector<block> blocks:: _ _ _ _ 
 *    block base:: _ _ _ _ _ _ _ _ _ 
 */

struct storageState {
  vector<block> blocks;
  block base;
  storageState(){}
  storageState(vector<block> & k, block b){
    blocks=k;
    base=b;
  }
};

/*****************************************************************
 * class bGroup: public ofInterObj 
 *
 *  Description:: 
 *
 *
 *  Vars:
 *
 *    vector<block> blocks:: _ _ _ _ _ _ 
 *    map<string,bool> used::_ _ _ _ _ _
 *    deque<storageState> storedState::_
 *    int stateCount:: _ _ _ _ _ _ _ _ _
 *    ofImage rTop:: _ _ _ _ _ _ _ _ _ _
 *    ofImage rBot:: _ _ _ _ _ _ _ _ _ _
 *    ofImage rSide::_ _ _ _ _ _ _ _ _ _
 *    public: block base:: _ _ _ _ _ _ _
 *    clock_t dblClick:: _ _ _ _ _ _ _ _
 *    int lastBlock::_ _ _ _ _ _ _ _ _ _
 *    bool grabbed,inHand,ddopen:: _ _ _
 *    double dispx, dispy::_ _ _ _ _ _ _
 *    double placex, placey::_ _ _ _ _ _
 */

class bGroup: public ofInterObj {
	vector<block> blocks;
	map<string,bool> used;
	//deque<storageState> storedState;
	//int stateCount;
  stateSave<storageState> states;
	ofImage rTop;
	ofImage	rBot;
	ofImage rSide;
  
  block * current;
  
  ofTimer actionTime;
  bool bSequencePlay;
  bool bTesting;
public:
  ofImage mapp;
  ofTurtle turtle;
  
	block base;
	clock_t dblClick;
	int lastBlock;
	bool bGrabbed,inHand,ddopen;
	double dispx, dispy;
	double placex, placey;
	bGroup(double x, double y,double wid,double hgt);
	
	bGroup();
	
	~bGroup();
	
	void recordState();
	
	void undoState();
	
	void redoState();
	
	bool undoAvailable();
	
	bool redoAvailable();
	
	void setup(double x, double y,double wid,double hgt);
	
	int size();
	
	block operator[](int i);
  
  
  
  void parseActions();
  
  void startTesting();
  
  void stopTesting();
  
  void startSequence();
  
  bool idleSequence(block * search);
  
  bool checkAgainstImage();
  
  void pauseSequence();
  
  bool isTesting();
  
  block * currentTest;
  
  void drawCurrentBlock();
  
  bool interpretDataStr(string str);
  
  block * nextActionBlock(block & b,bool skip=false);
  
  
	
	void addFromSB(block t,int x,int y);
	
	void writeFile(ofstream *k);
  
  void writeFile(string filname);
	
	void resetUsed(block & t);
	
	void resetUsed();
	
	void draw();
	
	void drawBase(int _x, int _y);
	
	void drawIndicators(block & grab,block & k);
	
	void update();
	
	int heightUpdate(block& grab, block & comp);
	
	int add(vector<block> t, int j=0);
	
	void addNum(block & holder, block & held);
	
	void addFromClick(block & t, int x, int y);
	
	void blockDown(block & t,int x,int y);
	
	void doubleClick(double x, double y, void func());
	
	void clickDown(double x, double y);
	
	void clear();
	
	//bool isInsideBlockBelow(block &t);
	
	int onIf(int x,int y,block t);
	
	void drawForeground();
	
	void drag(double x, double y);
	
	void motion(double x, double y);
	
	void deleteBlock(block * delBlk);
	
	block * deleteLast(block * del);
	
	void deleteGroup(block * del);
	
	int handleClickUps(block & first, block & second, bool checkOn=true);
	
	void clickUp(double x, double y);
	
	int grabbedBlockBelow(int i, int j);
	
	int above(int i, int j);
  
  //--------------------- New functions ------------------------
  
  block held;
  
  bool newClickDown(int _x, int _y);
  
  bool newClickUp(int _x, int _y);
  
  bool newHandleClickUp(block & grab, block & chk);
  
  bool newHandleClick(vector<block> & chk, int indx, int _x, int _y, bool top=false);
  
  bool processBlockDrop(block & drop,block & target, bool reverse=false);
  
  bool pushBlocks(block & dropped, vector<block> & into, int i, bool top=false);
  
  void pullBlocks(vector<block> & chk, int i);
  
};