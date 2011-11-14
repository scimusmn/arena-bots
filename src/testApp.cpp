#include "testApp.h"

string curDir="basic";
extern string ROOT_NAME;
extern string ROOT_DIR;

extern int pixPerInch;

extern ofColor black,white,yellow,blue,orange, gray;

//--------------------------------------------------------------
void testApp::setup(){
	
	//--------- Initialize the valid working space for the blocks
	blocks.setup(250, 0, ofGetWidth(), ofGetHeight());
  
	//--------- Load font for drawing on screen
  
  topTitle.loadFont("fonts/DinC.ttf", 35);

  
	ofHideCursor();
  
  mapps.loadImage("maps/map_2.jpg");
  
  controls.setup(&blocks, &sidebar);
}

//--------------------------------------------------------------
void testApp::update(){
	
  controls.update();
}


//--------------------------------------------------------------
void testApp::draw(){
    
  //--------- Draw background with slightly yellow grid over it.
  ofBackground(0x33, 0x33, 0x33);
  
  
  ofSetColor(black);
  drawHatching(0, 0, ofGetWidth(), ofGetHeight(), 15,1);
  
  //******************** Menu Bar **************************
  
  blocks.draw(sidebar.area.width,controls.h+topTitle.h,ofGetWidth()-sidebar.area.width,ofGetHeight()-(controls.h+topTitle.h));
  
  sidebar.draw(0,controls.h+topTitle.h);
  
  controls.draw(0, topTitle.h);

  topTitle.draw("Program the "+ROOT_NAME+" behaviors",0,0);
  
  //********************** Draw the blocks which are being held by the mouse ********
  
  blocks.drawForeground();
	
	//************************ if we're uploading, draw a fancy "uploading..." on screen
	
  
  if(blocks.isTesting()){
    ofSetColor(0x33, 0x33, 0x33);
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    
    
    ofSetColor(black);
    drawHatching(0, 0, ofGetWidth(), ofGetHeight(), 15,1);
    
    blocks.base.draw(ofGetHeight(), 75);
    blocks.drawCurrentBlock();
    
    ofSetColor(0xCFCFCF);
    ofRect(0,0, ofGetWidth(), 75);
    ofSetShadowDarkness((0xCF-0xA8)/255.);
    ofShade(0, 0, 75, ofGetWidth(), OF_DOWN);
    ofSetShadowDarkness(.15);
    ofShade(0, 75, 10, ofGetWidth(), OF_UP);
    ofShade(0, 75, 10, ofGetWidth(), OF_DOWN);
    
    ofPushMatrix();
    ofTranslate(100,100, 0);
    ofScale(((double)ofGetHeight()-200.)/(double)blocks.mapp.width, (double(ofGetHeight())-200.)/double(blocks.mapp.width), 1);
    ofSetColor(255, 255, 255);
    blocks.mapp.draw(0, 0);
    
    blocks.turtle.draw(0, 0);
    
    if(!blocks.turtle.frontIsClear(4*pixPerInch, blocks.mapp)) ofSetColor(255, 0, 0);
    else ofSetColor(0, 255, 0);
    ofPoint ps = blocks.turtle.pos+blocks.turtle.bearing.unit()*4*pixPerInch;
    ofCircle(ps.x, ps.y, 5);
    
    if(!blocks.turtle.leftIsClear(2*pixPerInch, blocks.mapp)) ofSetColor(255, 0, 0);
    else ofSetColor(0, 255, 0);
    ps = blocks.turtle.pos+blocks.turtle.bearing.ortho().unit()*blocks.turtle.w/2-blocks.turtle.bearing.unit()*blocks.turtle.w/2+blocks.turtle.bearing.unit().rotate(270)*2*pixPerInch;
    ofCircle(ps.x, ps.y, 5);
    ofPopMatrix();
  }
  
  controls.drawForeground();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
  if(key=='t'){
    if (blocks.isTesting()) blocks.stopTesting();
    else blocks.startTesting();
  }
  if(key==OF_KEY_UP){
    blocks.turtle.move(6);
  }
  if(key==OF_KEY_RIGHT){
    blocks.turtle.turn(6);
  }
  if(key==OF_KEY_LEFT){
    blocks.turtle.turn(-6);
  }
  if(key==OF_KEY_DOWN){
    blocks.turtle.move(-6);
  }
  if(key=='P'){
    blocks.startSequence();
  }
}


//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	//--------- if the mouse is moving and not clicked, inform the blocks
	blocks.motion(x, y);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
	//--------- if we are dragging the mouse, tell blocks so it can update the positions of any of the held blocks
  if(controls.mouseLockout(button))
     blocks.drag(x, y);
}

//***************** Mouse Click down function ***************
void testApp::mousePressed(int x, int y, int button){
  
  controls.clickDown(x, y);
  
  //--------- Check the blocks in the sidebar, to see if they have been clicked
  sidebar.clickDown(x, y);
  
  //--------- Check the blocks in the comp area
  blocks.clickDown(x, y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
  controls.clickUp();
	if(controls.mouseLockout(button)){
    //--------- do a bunch of clickups
    blocks.newClickUp(x, y);
  }
  controls.setAvailableButtons();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

