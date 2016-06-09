//
//  MainStream.cpp
//  QuadWindowSample
//
//  Created by HirokiNaganuma on 2016/06/09.
//
//

#include "MainStream.hpp"

//--------------------------------------------------------------
void MainStream::setup(){

    camW = 990; camH = 720;
    ofSetWindowShape(camW*2, camH*1.5f);//WindowSizeは1980*1080

    //---------------------------mjpg Connection-------------------------------------
    //192.168.145.238
//    cap[0] = cv::VideoCapture("192.168.150.181:8080?action=stream");
    cap[0] = cv::VideoCapture("http://192.168.150.181:8080/?action=stream");
    img[0].allocate(CAM_WIDTH, CROP_HEIGHT, OF_IMAGE_COLOR);

    //192.168.157.5
    //    cap[1] = cv::VideoCapture("http://192.168.157.5:7890/ipvideo.mjpg");
    //    img[1].allocate(CAM_WIDTH, CROP_HEIGHT, OF_IMAGE_COLOR);
    //
    //    //192.168.145.27
    //    cap[2] = cv::VideoCapture("http://192.168.145.27:7890/ipvideo.mjpg");
    //    img[2].allocate(CAM_WIDTH, CROP_HEIGHT, OF_IMAGE_COLOR);
    //---------------------------mjpg Connection--------------------------------------


    //-----------------------------------Chromakey Shader--------------------------------
    bShowGui = true;
    bUpdateBgColor = true;
    chromakey = new ofxChromaKeyShader(camW, camH);

    // maskee
    bg_image.load("black.jpg");//真っ黒背景(問題ないきがする)
    //-----------------------------------Chromakey Shader--------------------------------


    //---------------------GUI---------------------
    chromaGui.setDefaultHeight(18);
    chromaGui.setDefaultWidth(camW/2);
    chromaGui.setup();
    chromaGui.add(chromakey->generalParams);
    chromaGui.add(chromakey->positionParams);
    chromaGui.setPosition(0, 0);
    //---------------------GUI---------------------

}

//--------------------------------------------------------------
void MainStream::exit() {
    delete chromakey;
}

//--------------------------------------------------------------
void MainStream::update(){
    ofSetWindowTitle("[FPS]: "+ofToString(ofGetFrameRate()));

    //-------------取得した videocapture をchromakeyにセット--------------
    for(int i = 0; i<1;i++){
        if (cap[i].isOpened() ){
            cap[i] >> frame[i];
            if(frame[i].empty()){
                cout << "empty" << endl;
                exit();
            }else{
                img[i].setFromPixels(frame[i].ptr(), frame[i].cols, frame[i].rows, OF_IMAGE_COLOR);//RaspPiからの入力はBGRじゃないのでfalseを引数に入れない
                if(bUpdateBgColor && img[i].isAllocated())
                    chromakey->updateBgColor(img[i].getPixels());//Chromakeyに新しいPixelを入れる
                chromakey->updateChromakeyMask(img[i].getTexture(), bg_image.getTexture());
            }
            if(cv::waitKey(30) >= 0) exit();
        }
    }
    //-------------取得した videocapture をchromakeyにセット--------------


    /*
     //---------------------FBOに描画--------------------
     for(int i = 0 ;i<4 ;i++){
     screenFbo[i].begin();
     ofClear(0);
     if(img[i].isAllocated())img[i].draw(0,0);
     screenFbo[i].end();
     }
     //---------------------FBOに描画--------------------
     */
}

//--------------------------------------------------------------
void MainStream::draw(){
    ofSetColor(255);
    ofBackground(0);

    //------------------------Chromakeyを描画-------------------------
    // draw Cam mask
    chromakey->drawFinalImage(camW/2, 0, camW, camH);//chromacyかけたやつを描画
    drawDebugMasks();//Debug各種をサブルーチン化
    //------------------------Chromakeyを描画-------------------------

    //----------------------------GUIの描画--------------------------
    if(bShowGui) {
        chromaGui.draw();
        if(bUpdateBgColor) {
            ofPushStyle();
            ofNoFill();
            ofSetLineWidth(3);
            ofSetColor(255);
            ofVec2f bgColorPos = chromakey->bgColorPos.get();
            ofDrawRectangle(bgColorPos.x + camW/2, bgColorPos.y, chromakey->bgColorSize.get(), chromakey->bgColorSize.get());
            ofDrawBitmapString("bgColor", bgColorPos.x + camW/2, bgColorPos.y - 5);
            ofPopStyle();
        }
    }
    //----------------------------GUIの描画--------------------------
}

//--------------------------------------------------------------
void MainStream::drawDebugMasks() {
    ofSetColor(255);
    int previewW = camW/2, previewH = camH/2, labelOffset = 10;

    chromakey->drawBaseMask(camW + previewW, 0, previewW, previewH);
    ofDrawBitmapStringHighlight("Base mask", camW + previewW, labelOffset, ofColor(0, 125), ofColor::yellowGreen);

    chromakey->drawDetailMask(camW + previewW, previewH, previewW, previewH);
    ofDrawBitmapStringHighlight("Detailed mask", camW + previewW, previewH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);

    chromakey->drawChromaMask(previewW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("Chroma mask", previewW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);

    drawCheckerboard(camW, camH, previewW, previewH, 5);
    
    chromakey->drawFinalMask(camW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("Final mask", camW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);

    img[0].draw(camW + previewW, camH, previewW, previewH);
    ofDrawBitmapStringHighlight("RGB image", camW + previewW, camH + labelOffset, ofColor(0, 125), ofColor::yellowGreen);
}

//--------------------------------------------------------------
//チェス盤みたいなやつを描画
void MainStream::drawCheckerboard(float x, float y, int width, int height, int size) {
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
void MainStream::keyPressed(int key){

}

//--------------------------------------------------------------
void MainStream::keyReleased(int key){
    switch(key){
        case 'a':
            bUpdateBgColor = !bUpdateBgColor;
            break;
        case 'g':
            bShowGui = !bShowGui;
            break;
    }
}

//--------------------------------------------------------------
void MainStream::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void MainStream::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MainStream::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MainStream::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MainStream::windowResized(int w, int h){

}

//--------------------------------------------------------------
void MainStream::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MainStream::dragEvent(ofDragInfo dragInfo){ 
    
}
