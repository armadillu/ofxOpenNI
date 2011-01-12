#pragma once

#include "ofxOpenNIContext.h"

class ofxImageGenerator {

public:

	ofxImageGenerator();
	
	bool setup(ofxOpenNIContext * context, bool flipHorizontal = true);
	void generateTexture();
	void draw(float x=0, float y=0, float w=640, float h=480);
	xn::ImageGenerator* getXnImageGenerator();

private:
	
	xn::ImageGenerator image_generator;
	ofTexture _imageTexture;

	ofxOpenNIContext * _context;
};

