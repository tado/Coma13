#include "Colorbar.h"

void Colorbar::setup(){
    shader.load("colorbar");
    for (int i = 0; i < NUM; i++) {
        freq[i] = 0;
        phase[i] = 0;
        amp[i] = 0.0;
        lfo[i] = 0.0;
    }
    counter = 0;
    
    fx = new ofxSCSynth("col_fx");
    fx->create();
}

void Colorbar::update(){
}

void Colorbar::draw(){
    ofBackground(0);
    
    float time = ofGetElapsedTimef();
    float resolution[] = {ofGetWidth(), ofGetHeight()};
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1fv("freq", freq, NUM);
    shader.setUniform1fv("phase", phase, NUM);
    shader.setUniform1fv("amp", amp, NUM);
    shader.setUniform1fv("lfo", lfo, NUM);


    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    
    if (counter > 0 && amp[counter - 1] < 1.0) {
        amp[counter - 1] += 0.1;
    }
}

void Colorbar::mousePressed(int x, int y, int button){
    bMousePressed = true;
    drawPos.x = x;
    drawPos.y = y;
}

void Colorbar::mouseReleased(int x, int y, int button){
    //GLSL
    if (counter < NUM) {
        freq[counter] = powf(ofMap(y, 0, ofGetHeight(), 15, 1), 3.0);
        
        float dir;
        if (counter % 2 == 0) {
            dir = 1.0;
        } else {
            dir = -1.0;
        }
        phase[counter] = ofRandom(40, 50) * dir;
        lfo[counter] = ofRandom(1,2);
        counter++;
        
        //SC
        float dist = drawPos.distance(ofVec2f(x, y));
        if (dist > 100.0) {
            dist = 100.0;
        }
        float amp = ofMap(dist, 0.0, 100.0, 0.0, 0.3);
        int note  = int(ofMap(drawPos.y, 0, ofGetHeight(), 85, 1));
        float freq = 20 + 20 * pow((13.0/12.0), note);
        float pan = ofMap(x, 0, ofGetWidth(), -1.0, 1.0);
        synth = new ofxSCSynth("col_sine");
        synth->create();
        synth->set("gate", 1);
        synth->set("freq", freq);
        synth->set("lfoFreq",1.0);
        synth->set("pan", pan);
        synth->set("amp", amp);
    }
}

string Colorbar::getName(){
    return "colorbar";
}

