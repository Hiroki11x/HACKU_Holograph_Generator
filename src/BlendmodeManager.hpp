//
//  BlendmodeManager.hpp
//  ofxVJComponent
//
//  Created by HirokiNaganuma on 2016/05/29.
//
//

#ifndef BlendmodeManager_hpp
#define BlendmodeManager_hpp

#include "ofMain.h"

class BlendmodeManager{
private:
    int blendmodeIndex;
    int max_num;
public:
    void init(int max_num);
    void nextIndex();
    string getBlendmodeName();
};

#endif /* BlendmodeManager_hpp */
