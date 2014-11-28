#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxCamShift.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofxKinect kinect;
	int height;
	int width;
	ofxCvColorImage colorImage;

	ofxCvFloatImage HOGImage;
	ofxCvGrayscaleImage depthImage; // grayscale depth image
	ofxCvGrayscaleImage depthThresholdNear; // the near thresholded image
	ofxCvGrayscaleImage depthThresholdFar; // the far thresholded image


	ofxCamShift* meanShift;
	int nearThreshold;
	int farThreshold;

	int angle;
};