#pragma once

#include "ofxOpenNIContext.h"

class ofxImageGenerator {

public:

	ofxImageGenerator();
	
	bool setup(ofxOpenNIContext * context);
	void generateTexture();
	void draw(float x=0, float y=0, float w=640, float h=480);
	xn::ImageGenerator* getXnImageGenerator();

private:
	
	xn::ImageGenerator image_generator;
	ofTexture _imageTexture;
	unsigned char * imagePixels;
	ofxOpenNIContext * _context;
};

