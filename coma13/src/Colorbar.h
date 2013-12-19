#pragma once
#include "ofxState.h"
#include "ofxSuperCollider.h"

class Colorbar : public itg::ofxState<> {
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    string getName();
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
    
    static const int NUM = 50;
    float freq[NUM];
    float phase[NUM];
    float amp[NUM];
    float lfo[NUM];
    int counter;
    
    ofxSCSynth *fx;
    ofxSCSynth *synth;
    ofVec2f drawPos;
    bool bMousePressed;
};