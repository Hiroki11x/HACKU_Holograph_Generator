#include "ofMain.h"
#include "ofApp.h"
#include "OpenCVTestScene.hpp"
#include "OpenCVScene2.hpp"
#include "OpenCVScene3.hpp"
#include "MainStream.hpp"

//========================================================================
int main( ){
	ofSetupOpenGL(800*2,600*2,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//	ofRunApp(new ofApp());
//    ofRunApp(new OpenCVTestScene());
//ofRunApp(new OpenCVScene2());
    ofRunApp(new MainStream());
}
