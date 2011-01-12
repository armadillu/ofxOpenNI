#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	context.initFromXMLFile();
	depth.setup(&context);
	image.setup(&context);
	user.setup(&context, &depth);
}

//--------------------------------------------------------------
void testApp::update(){
	context.update();
	user.update();
}

//--------------------------------------------------------------
void testApp::draw(){

	ofEnableAlphaBlending();
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	
	depth.draw(0,0,640,480);
	image.draw(640,0,640,480);
	//user.draw();
	
	ofxTrackedUser* tracked = user.getTrackedUser(0);
	if(tracked != NULL) {
		
		tracked->debugDraw();	//on top of depth image
		
		glPushMatrix();
			glTranslatef(640,0,0);	//on top of rgb image
			tracked->debugDraw();
		glPopMatrix();
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

