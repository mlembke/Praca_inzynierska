#pragma once
#include "ofMain.h"
#include "ofxMatrix.h"


class ofxCamShiftWindow
{
public:
	static const int DEFAULT_WINDOW_SIZE = 100;

	ofxCamShiftWindow();
	ofxCamShiftWindow(ofVec2f window_center);
	ofxCamShiftWindow(ofVec2f window_center, int window_size);
	~ofxCamShiftWindow();

	void shiftWindow(ofVec2f shift_vector);
	ofVec2f getCenter();
	void setCenter(ofVec2f new_center);
	ofxMatrix<int> getCoordinatesMatrix();
	ofColor getColor();
	void setColor(ofColor new_color);
	double getLuminanceDensity();
	void setLuminanceDensity(double new_luminance_density);
	int getSize();
	bool setSize(int new_size);
	void setDeafultSize();
	void draw();

private:
	ofColor color;
	ofVec2f center;
	double luminanceDensity;
	int size;
};