#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Poco/Random.h"
#include "ofxKernelType.h"
#include "ofxCamShiftWindow.h"
#include "ofxHog.h"


class ofxCamShift
{
public:
	ofxCamShift();
	ofxCamShift(unsigned char* pixels, int width, int height);
	ofxCamShift(ofxCvGrayscaleImage& image);
	~ofxCamShift();

	void update();
	void draw();
	void calculateMeanShift(ofxCamShiftWindow& window);
	void seek();
	int getWindowsCount();
	ofxCvFloatImage getHog();
private:
	static const int SEEK_THRESHOLD = 150;
	unsigned char* pixels;
	ofxMatrix<unsigned char> pixMat;
	vector<ofxCamShiftWindow*> windows;
	ofxMatrix<float> HOG;
	ofxMatrix<int> ROI;
	ofxCvFloatImage HOGImage;
	ofVec2f meanShiftVector;
	KernelType kernelType;
	int width;
	int height;

	Poco::Random random;
};