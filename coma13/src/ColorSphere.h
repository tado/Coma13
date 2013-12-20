#pragma once
#include "ofxState.h"
#include "ofxSuperCollider.h"

class ShaderParams {
public:
    int col;
    float freq;
    float phase;
    float amp;
    float lfo;
    ofxSCSynth *synth;
};

class ColorSphere : public itg::ofxState<> {
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    string getName();

    static const int MAX_SYNTH = 8;
    deque<ShaderParams> shaderParams;
    int col[MAX_SYNTH];
    float freq[MAX_SYNTH];
    float phase[MAX_SYNTH];
    float amp[MAX_SYNTH];
    float lfo[MAX_SYNTH];
    int counter;
    
    ofFbo fbo;
    ofShader shader;
    float width, height;
    
    ofxSCSynth *fx;
    ofVec2f drawPos;
    bool bMousePressed;
    
    ofSpherePrimitive sphere;
};