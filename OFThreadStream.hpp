//
//  OFThreadStream.hpp
//  QuadWindowSample
//
//  Created by HirokiNaganuma on 2016/06/11.
//
//

#ifndef OFThreadStream_hpp
#define OFThreadStream_hpp

#define SCREEN_NUM 4

#include "ofMain.h"
#include "MovieThread.hpp"


class OFThreadStream : public ofBaseApp{

public:
    MovieThread thread[2];
    ofImage myImage;

    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void drawDebugMasks(int i);
    void drawCheckerboard(float x, float y, int width, int height, int size);
};
#endif /* OFThreadStream_hpp */
