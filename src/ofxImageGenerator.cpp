#include "ofxImageGenerator.h"


ofxImageGenerator::ofxImageGenerator(){
}

bool ofxImageGenerator::setup(ofxOpenNIContext * context){
	_context = context;
	
	//Create image generator
	XnStatus nRetVal = image_generator.Create(*_context->getXnContext());
	
	if (nRetVal != XN_STATUS_OK){
		
		printf("Setup image Camera failed: %s\n", xnGetStatusString(nRetVal));
		return false;
		
	} else {
	
		ofLog(OF_LOG_VERBOSE, "image camera inited");
		
		//Set the input to VGA (standard is QVGA wich is not supported on the Kinect)
		XnMapOutputMode mapMode; mapMode.nXRes = XN_VGA_X_RES; mapMode.nYRes = XN_VGA_Y_RES; mapMode.nFPS = 30;
		nRetVal = image_generator.SetMapOutputMode(mapMode);
		
		_imageTexture.allocate(mapMode.nXRes, mapMode.nYRes, GL_RGB);		
		imagePixels = new unsigned char[mapMode.nXRes * mapMode.nYRes * 3];
		memset(imagePixels, 0, mapMode.nXRes * mapMode.nYRes * 3 * sizeof(unsigned char));
		
		image_generator.StartGenerating();	
		
		return true;
	}
}

void ofxImageGenerator::draw(float x, float y, float w, float h){

	generateTexture();
	//glColor3f(1,1,1);
	_imageTexture.draw(x, y, w, h);	
}

xn::ImageGenerator* ofxImageGenerator::getXnImageGenerator() {
	return &image_generator;
}


void ofxImageGenerator::generateTexture(){
	
	xn::ImageMetaData pImageMD;
	image_generator.GetMetaData(pImageMD);	
	const XnRGB24Pixel* pImage = image_generator.GetRGB24ImageMap();
	XN_ASSERT(pImage);
		
	_imageTexture.loadData((unsigned char *)pImage, pImageMD.XRes(), pImageMD.YRes(), GL_RGB);	
}