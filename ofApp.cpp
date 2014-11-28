#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(100, 100, 100);
	ofSetLogLevel(OF_LOG_VERBOSE);
	// enable depth->video image calibration
	kinect.setRegistration(true);

	kinect.init(false, false); // disable video image (faster fps)
	//kinect.init();

	kinect.open(true);

	height = kinect.height;
	width = kinect.width;
	colorImage.allocate(kinect.width, kinect.height);
	depthImage.allocate(kinect.width, kinect.height);
	depthThresholdNear.allocate(kinect.width, kinect.height);
	depthThresholdFar.allocate(kinect.width, kinect.height);
	HOGImage.allocate(kinect.width, kinect.height);
	nearThreshold = 255;
	farThreshold = 248;

	ofSetFrameRate(30);

	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);

	meanShift = new ofxCamShift(depthImage);
}

//--------------------------------------------------------------
void ofApp::update()
{
	kinect.update();

	// there is a new frame and we are connected
	if (kinect.isFrameNew())
	{
		// load grayscale depth image from the kinect source
		depthImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		colorImage.setFromPixels(kinect.getPixels(), kinect.width, kinect.height);
		// we do two thresholds - one for the far plane and one for the near plane
		// and get the pixels which are a union of the two thresholds
		unsigned char* pix = depthImage.getPixels();

		int numPixels = depthImage.getWidth() * depthImage.getHeight();
		for (int i = 0; i < numPixels; i++)
		{
			if (pix[i] > nearThreshold || pix[i] < farThreshold)
			{
				pix[i] = 0;
			}
		}
		// update the cv images
		depthImage.flagImageChanged();
		colorImage.flagImageChanged();
		meanShift->update();
		// find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
		// also, find holes is set to true so we will get interior contours as well....
		//contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofSetColor(255);
	depthImage.draw(0, 0, width, height);
	//colorImage.draw(0, 0, width, height);
	meanShift->draw();
	ofSetColor(255);
	stringstream reportStream;

	if (kinect.hasAccelControl())
	{
		reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
			<< ofToString(kinect.getMksAccel().y, 2) << " / "
			<< ofToString(kinect.getMksAccel().z, 2) << endl;
	}
	else
	{
		reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
			<< "motor / led / accel controls are not currently supported" << endl << endl;
	}

	reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
		<< "set near threshold " << nearThreshold << " (press: + -)" << endl
		<< "set far threshold " << farThreshold << " (press: < >)"
		<< ", fps: " << ofGetFrameRate() << endl
		<< "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;

	if (kinect.hasCamTiltControl())
	{
		reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
			<< "press 1-5 & 0 to change the led mode" << endl;
	}

	ofDrawBitmapString(reportStream.str(), 20, 652);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	delete meanShift;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch (key)
	{
	case '>':
	case '.':
		farThreshold ++;
		if (farThreshold > 255) farThreshold = 255;
		break;

	case '<':
	case ',':
		farThreshold --;
		if (farThreshold < 0) farThreshold = 0;
		break;

	case '+':
	case '=':
		nearThreshold ++;
		if (nearThreshold > 255) nearThreshold = 255;
		break;

	case '-':
		nearThreshold --;
		if (nearThreshold < 0) nearThreshold = 0;
		break;

	case 'w':
		kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
		break;

	case 'o':
		kinect.setCameraTiltAngle(angle); // go back to prev tilt
		kinect.open();
		break;

	case 'c':
		kinect.setCameraTiltAngle(0); // zero the tilt
		kinect.close();
		break;

	case '1':
		kinect.setLed(ofxKinect::LED_GREEN);
		break;

	case '2':
		kinect.setLed(ofxKinect::LED_YELLOW);
		break;

	case '3':
		kinect.setLed(ofxKinect::LED_RED);
		break;

	case '4':
		kinect.setLed(ofxKinect::LED_BLINK_GREEN);
		break;

	case '5':
		kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
		break;

	case '0':
		kinect.setLed(ofxKinect::LED_OFF);
		break;

	case OF_KEY_UP:
		angle++;
		if (angle > 30) angle = 30;
		kinect.setCameraTiltAngle(angle);
		break;

	case OF_KEY_DOWN:
		angle--;
		if (angle < -30) angle = -30;
		kinect.setCameraTiltAngle(angle);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}