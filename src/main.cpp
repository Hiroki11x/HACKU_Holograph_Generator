#include "ofMain.h"
//#include "ofApp.h"
//#include "OpenCVTestScene.hpp"
//#include "OpenCVScene2.hpp"
//#include "OpenCVScene3.hpp"
#include "MainStream.hpp"
#include "GrabCutSample.hpp"
#include "CameraStreamerSample.hpp"

//========================================================================
int main( ){
	ofSetupOpenGL(1920,1080,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
    ofRunApp(new CameraStreamerSample());
}
