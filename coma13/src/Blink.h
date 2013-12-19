#pragma once
#include "ofxState.h"

class Blink : public itg::ofxState<> {
    void setup();
    void update();
    void draw();
    string getName();
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
};