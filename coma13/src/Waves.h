#pragma once
#include "ofxState.h"
#include "ofxSuperCollider.h"

class WaveParams {
public:
    float amp;
    ofxSCSynth *synth;
};

class Waves : public itg::ofxState<> {
    void setup();
    void stateEnter();
    void stateExit();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    string getName();
    
    static const int MAX = 20;
    deque<WaveParams> waveParams;
    int counter;
    int fadeCount;
    bool fadeout;
    float level;
    float amp[MAX];
    
    ofxSCSynth *fx;
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
    
    bool bMousePressed;
    vector<ofVec2f> path;
};