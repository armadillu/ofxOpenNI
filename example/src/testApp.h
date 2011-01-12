#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxOpenNI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
		void newUserEvent(ofxUserGeneratorEventsArgs &args){ printf("newUserEvent ID %d\n", args.userID); }
		void lostUserEvent(ofxUserGeneratorEventsArgs &args){ printf("lostUserEvent ID %d\n", args.userID); }
		void poseDetectedEvent(ofxUserGeneratorEventsArgs &args){ printf("poseDetectedEvent ID %d\n", args.userID); }
		void calibrationStartedEvent(ofxUserGeneratorEventsArgs &args){ printf("calibrationStartedEvent ID %d\n", args.userID); }
		void calibrationEndedEvent(ofxUserGeneratorEventsArgs &args){ printf("calibrationEndedEvent ID %d\n", args.userID); }
		void calibrationSucceededEvent(ofxUserGeneratorEventsArgs &args){ printf("calibrationSucceededEvent ID %d\n", args.userID); }
		void calibrationFailedEvent(ofxUserGeneratorEventsArgs &args){ printf("calibrationFailedEvent ID %d\n", args.userID); }
	
		ofxOpenNIContext context;
		ofxDepthGenerator depth;
		ofxImageGenerator image;
		ofxUserGenerator user;
		
};

#endif
