#include "ofxTrackedUser.h"
#include "ofxDepthGenerator.h"
#include "ofxUserGenerator.h"

ofxTrackedUser::ofxTrackedUser(
	 ofxUserGenerator* pUserGenerator
	,ofxDepthGenerator* pDepthGenerator
) 
:neck(XN_SKEL_HEAD, XN_SKEL_NECK)

// left arm + shoulder
,left_shoulder(XN_SKEL_NECK, XN_SKEL_LEFT_SHOULDER)
,left_upper_arm(XN_SKEL_LEFT_SHOULDER, XN_SKEL_LEFT_ELBOW)
,left_lower_arm(XN_SKEL_LEFT_ELBOW, XN_SKEL_LEFT_HAND)

// right arm + shoulder
,right_shoulder(XN_SKEL_NECK, XN_SKEL_RIGHT_SHOULDER)
,right_upper_arm(XN_SKEL_RIGHT_SHOULDER, XN_SKEL_RIGHT_ELBOW)
,right_lower_arm(XN_SKEL_RIGHT_ELBOW, XN_SKEL_RIGHT_HAND)

// upper torso
,left_upper_torso(XN_SKEL_LEFT_SHOULDER, XN_SKEL_TORSO)
,right_upper_torso(XN_SKEL_RIGHT_SHOULDER, XN_SKEL_TORSO)

// left lower torso + leg
,left_lower_torso(XN_SKEL_TORSO, XN_SKEL_LEFT_HIP)
,left_upper_leg(XN_SKEL_LEFT_HIP, XN_SKEL_LEFT_KNEE)
,left_lower_leg(XN_SKEL_LEFT_KNEE, XN_SKEL_LEFT_FOOT)

// right lower torso + leg
,right_lower_torso(XN_SKEL_TORSO, XN_SKEL_RIGHT_HIP)
,right_upper_leg(XN_SKEL_RIGHT_HIP, XN_SKEL_RIGHT_KNEE)
,right_lower_leg(XN_SKEL_RIGHT_KNEE, XN_SKEL_RIGHT_FOOT)

,hip(XN_SKEL_LEFT_HIP, XN_SKEL_RIGHT_HIP)
,user_generator(pUserGenerator)
,depth_generator(pDepthGenerator) 
,xn_user_generator(user_generator->getXnUserGenerator())
{
}

void ofxTrackedUser::updateBonePositions() {
	updateLimb(neck);
	
	// left arm + shoulder
	updateLimb(left_shoulder);
	updateLimb(left_upper_arm);
	updateLimb(left_lower_arm);
	
	// right arm + shoulder
	updateLimb(right_shoulder);
	updateLimb(right_upper_arm);
	updateLimb(right_lower_arm);
	
	// upper torso
	updateLimb(left_upper_torso);
	updateLimb(right_upper_torso);
	
	// left lower torso + leg
	updateLimb(left_lower_torso);
	updateLimb(left_upper_leg);
	updateLimb(left_lower_leg);
	
	// right lower torso + leg
	updateLimb(right_lower_torso);
	updateLimb(right_upper_leg);
	updateLimb(right_lower_leg);

	updateLimb(hip);	
}

void ofxTrackedUser::updateLimb(ofxLimb& rLimb) {
	if(!xn_user_generator->GetSkeletonCap().IsTracking(id)) {
		printf("Not tracking this user: %d\n", id);
		return;
	}
	
	XnSkeletonJointPosition a,b;
	xn_user_generator->GetSkeletonCap().GetSkeletonJointPosition(id, rLimb.start_joint, a);
	xn_user_generator->GetSkeletonCap().GetSkeletonJointPosition(id, rLimb.end_joint, b);
	if(a.fConfidence < 0.3f || b.fConfidence < 0.3f) {
		rLimb.found = false; 
		return;
	}
	rLimb.found = true;
	rLimb.position[0] = a.position;
	rLimb.position[1] = b.position;
	depth_generator->getXnDepthGenerator()->ConvertRealWorldToProjective(2, rLimb.position, rLimb.position);
}

void ofxTrackedUser::debugDraw() {
	neck.debugDraw(id);
	
	// left arm + shoulder
	left_shoulder.debugDraw(id);
	left_upper_arm.debugDraw(id);
	left_lower_arm.debugDraw(id);
	
	// right arm + shoulder
	right_shoulder.debugDraw(id);
	right_upper_arm.debugDraw(id);
	right_lower_arm.debugDraw(id);
	
	// upper torso
	left_upper_torso.debugDraw(id);
	right_upper_torso.debugDraw(id);
	
	// left lower torso + leg
	left_lower_torso.debugDraw(id);
	left_upper_leg.debugDraw(id);
	left_lower_leg.debugDraw(id);

	// right lower torso + leg
	right_lower_torso.debugDraw(id);
	right_upper_leg.debugDraw(id);
	right_lower_leg.debugDraw(id);
	
	hip.debugDraw(id);
}
