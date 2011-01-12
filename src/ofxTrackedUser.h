#ifndef OFXTRACKEDUSERH
#define OFXTRACKEDUSERH

#include <XnOpenNI.h>
#include <XnCppWrapper.h>
#include "ofMain.h"


#define NUM_COLOR_IDS	6
static unsigned char uniqueColors[NUM_COLOR_IDS][3] = { 
														{255,0,0}, {0,255,0}, {0,0,255},		// red, green, blue
														{255,255,0}, {255,0,255}, {0,255,255},
														};

struct ofxLimb {
	ofxLimb(XnSkeletonJoint nStartJoint, XnSkeletonJoint nEndJoint) 
		:start_joint(nStartJoint)
		,end_joint(nEndJoint)
		,found(false)
	{
		position[0].X = position[1].X = 0;
		position[0].Y = position[1].Y = 0;
		position[0].Z = position[1].Z = 0;
	}
	XnSkeletonJoint start_joint;
	XnSkeletonJoint end_joint;
	XnPoint3D position[2];
	bool found;
	
	void debugDraw(XnUserID ID) {
		
		if(!found)
			return;
		
		int index = ID % NUM_COLOR_IDS;
		
		glLineWidth(12);
		glPointSize(12);
		glColor3ub(0,0,0);

		glBegin(GL_POINTS);
			glVertex2i(position[0].X, position[0].Y);
			glVertex2i(position[1].X, position[1].Y);
		glEnd();

		glBegin(GL_LINES);
			//std::cout << position[0].X << ", " << position[0].Y << std::endl;
			glVertex2i(position[0].X, position[0].Y);
			glVertex2i(position[1].X, position[1].Y);
		glEnd();

		
		glLineWidth(5);
		glPointSize(5);
		glColor3f( uniqueColors[index][0], uniqueColors[index][1], uniqueColors[index][2] );		
		
		glBegin(GL_POINTS);
			glVertex2i(position[0].X, position[0].Y);
			glVertex2i(position[1].X, position[1].Y);
		glEnd();

		glBegin(GL_LINES);
			glVertex2i(position[0].X, position[0].Y);
			glVertex2i(position[1].X, position[1].Y);
		glEnd();
	}
	
};

class ofxUserGenerator;
class ofxDepthGenerator;
class ofxTrackedUser {
public: 
	void debugDraw();
		

	ofxLimb neck;
	
	// left arm + shoulder
	ofxLimb left_shoulder;
	ofxLimb left_upper_arm;
	ofxLimb left_lower_arm;
	
	// right arm + shoulder
	ofxLimb right_shoulder;
	ofxLimb right_upper_arm;
	ofxLimb right_lower_arm;
	
	// torso
	ofxLimb left_upper_torso;
	ofxLimb right_upper_torso;
	
	// left lower torso + leg
	ofxLimb left_lower_torso;
	ofxLimb left_upper_leg;
	ofxLimb left_lower_leg;
	
	// right lower torso + leg
	ofxLimb right_lower_torso;
	ofxLimb right_upper_leg;
	ofxLimb right_lower_leg;

	ofxLimb hip;
	XnUserID id;


private:
	ofxTrackedUser(ofxUserGenerator* pGenerator, ofxDepthGenerator* pDepthGenerator);
	
	void updateBonePositions();
	void updateLimb(ofxLimb& rLimb);
	
	ofxUserGenerator* user_generator;
	xn::UserGenerator* xn_user_generator;
	ofxDepthGenerator* depth_generator;

	friend class ofxUserGenerator;
};

#endif