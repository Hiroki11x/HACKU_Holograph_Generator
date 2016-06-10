//
//  OFThreadStream.cpp
//  QuadWindowSample
//
//  Created by HirokiNaganuma on 2016/06/11.
//
//

#include "OFThreadStream.hpp"


void OFThreadStream::setup() {

    ofxOpenGLContextScope::setup();
    // start the thread
    for(int i = 0 ;i<2;i++){
        thread[i].init(i);
        thread[i].startThread();    // blocking, non verbose
    }
}

void OFThreadStream::update() {

}

void OFThreadStream::exit() {
    for(int i = 0 ;i<2;i++){
        thread[i].stopThread();
    }

}

void OFThreadStream::draw() {
    for(int i = 0 ;i<2;i++){
        thread[i].img.draw(600*i, 0,600,450);
    }
    ofSetWindowTitle("FPS: "+ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void OFThreadStream::keyPressed(int key){

}

//--------------------------------------------------------------
void OFThreadStream::drawDebugMasks(int i) {
    ofSetColor(255);
    int previewW = camW/2, previewH = camH/2, labelOffset = 10;

#ifdef CHROMAKEY
    mCvParallelThread[i].chromakey->drawBaseMask(camW + previewW, 0, previewW, previewH);
    ofDrawBitmapStringHighlight("Base mask", camW + previewW, labelOffset, ofColor(0, 125), ofColor::white);

    mCvParallelThread[i].chromakey->drawDetailMask(camW + previewW, previewH, previewW, previewH);
    ofDrawBitmapStringHighlight("Detailed mask", camW + previewW, previewH + labelOffset, ofColor(0, 125), ofColor::white);

    mCvParallelThread[i].chromakey->drawChromaMask(previewW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("Chroma mask", previewW, camH + labelOffset, ofColor(0, 125), ofColor::white);

    drawCheckerboard(camW, camH, previewW, previewH, 5);

    mCvParallelThread[i].chromakey->drawFinalMask(camW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("Final mask", camW, camH + labelOffset, ofColor(0, 125), ofColor::white);
#endif

    mCvParallelThread[i].img.draw(camW + previewW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("RGB image", camW + previewW, camH + labelOffset, ofColor(0, 125), ofColor::white);
}

//--------------------------------------------------------------
//チェス盤みたいなやつを描画
void OFThreadStream::drawCheckerboard(float x, float y, int width, int height, int size) {
    if (!checkerboardTex.isAllocated()) {
        checkerboardTex.allocate(width, height);

        ofPushStyle();
        checkerboardTex.begin();
        ofClear(255, 255, 255, 255);
        int numWidth = width/size;
        int numHeight = height/size;
        for(int h=0; h<numHeight; h++) {
            for(int w=0; w<numWidth; w++) {
                if ((h+w)%2 == 0) {
                    ofSetColor(ofColor::black);
                    ofDrawRectangle(w*size, h*size, size, size);
                }
            }
        }
        checkerboardTex.end();
        ofPopStyle();
    }

    ofSetColor(255, 255);
    checkerboardTex.draw(x, y);
}

//--------------------------------------------------------------
void OFThreadStream::keyReleased(int key){

}

//--------------------------------------------------------------
void OFThreadStream::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void OFThreadStream::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void OFThreadStream::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void OFThreadStream::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void OFThreadStream::windowResized(int w, int h){

}

//--------------------------------------------------------------
void OFThreadStream::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void OFThreadStream::dragEvent(ofDragInfo dragInfo){
    
}