#include "ofxCamShiftWindow.h"


ofxCamShiftWindow::ofxCamShiftWindow()
{
	center = ofVec2f(-1, -1);
	color = ofColor::black;
	luminanceDensity = -1.0;
	size = -1;
	
}

ofxCamShiftWindow::ofxCamShiftWindow(ofVec2f window_center)
{
	center = window_center;
	color = ofColor::cyan;
	luminanceDensity = 0.0;
	size = DEFAULT_WINDOW_SIZE;
	
}

ofxCamShiftWindow::ofxCamShiftWindow(ofVec2f window_center, int window_size)
{
	center = window_center;
	color = ofColor::cyan;
	luminanceDensity = 0;
	size = size;
	
}

ofxCamShiftWindow::~ofxCamShiftWindow()
{
}

void ofxCamShiftWindow::shiftWindow(ofVec2f shiftVector)
{
	center += shiftVector;
}

ofVec2f ofxCamShiftWindow::getCenter()
{
	return center;
}

void ofxCamShiftWindow::setCenter(ofVec2f new_center)
{

}

ofxMatrix<int> ofxCamShiftWindow::getCoordinatesMatrix()
{
	int xStart = center.x - size / 2;
	int yStart = center.y - size / 2;
	int xEnd = center.x + size / 2;
	int yEnd = center.y + size / 2;

	ofxMatrix<int> ROICoordinates(size * size * 2, 2);

	int i = 0;
	for (int y = yStart; y < yEnd; y++)
	{
		for (int x = xStart; x < xEnd; x++)
		{
			ROICoordinates.matrix[i][0] = x;
			ROICoordinates.matrix[i][1] = y;
		}
	}

	return ROICoordinates;
}

ofColor ofxCamShiftWindow::getColor()
{
	return color;
}

void ofxCamShiftWindow::setColor(ofColor new_color)
{
	color = new_color;
}

double ofxCamShiftWindow::getLuminanceDensity()
{
	return luminanceDensity;
}

void ofxCamShiftWindow::setLuminanceDensity(double new_luminance_density)
{
	luminanceDensity = new_luminance_density;
}

int ofxCamShiftWindow::getSize()
{
	return size;
}

bool ofxCamShiftWindow::setSize(int new_size)
{
	if(size > 0)
	{
		size = new_size;
		return true;
	}
	return false;
}

void ofxCamShiftWindow::setDeafultSize()
{
	size = DEFAULT_WINDOW_SIZE;
}

void ofxCamShiftWindow::draw()
{
	ofNoFill();
	ofSetColor(color);
	ofRect(center.x - size / 2, center.y - size / 2, size, size);
	ofSetColor(255);
}