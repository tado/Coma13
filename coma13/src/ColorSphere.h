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
    void stateEnter();
    void stateExit();
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);
    string getName();

    static const int MAX_SYNTH = 6;
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
    ofVec2f draggedPos;
    bool bMousePressed;
    
    ofSpherePrimitive sphere;
    
    bool drawGlitch;
    bool drawPulse;
    float glitchStartTime;
    float pulseStartTime;
    ofFbo fbo2;
    ofxSCSynth *glitchSynth;
    ofxSCSynth *pluseSynth;
    
    ofShader blinkShader;
    ofFbo fbo3;
    
    float sphereStartTime;
    
    bool bComb;
    ofVec2f movePos;
};