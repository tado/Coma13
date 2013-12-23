#include "Waves.h"

void Waves::setup(){
    width = 640;
    height = 480;
    fbo.allocate(width,height);
}

void Waves::stateEnter(){
    shader.load("waves");
    counter = 0;
    level = 0;
    for (int i = 0; i < MAX; i++) {
        amp[i] = 0;
    }
    
    fx = new ofxSCSynth("col_closefx");
    fx->create();
    fadeout = false;
    fadeCount = 0;
}

void Waves::stateExit(){
    fx->free();
    for(int i = 0; i < waveParams.size(); i++){
        waveParams[i].synth->set("gate", 0);
    }
    waveParams.clear();
    shader.unload();
}

void Waves::update(){
    if(!fadeout){
        for (int i = 0; i < counter; i++) {
            amp[i] += 0.001;
            if(amp[i] > 1.0){
                amp[i] = 1.0;
            }
        }
    } else {
        for (int i = 0; i < fadeCount; i++) {
            amp[i] -= 0.005;
            if(amp[i] < 0.0){
                amp[i] = 0.0;
            }
        }
    }
}
void Waves::draw(){
    ofBackground(0);
    ofSetColor(255);
    float time = ofGetElapsedTimef();
    float resolution[] = {width, height};
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1f("num", counter);
    shader.setUniform1fv("amp", amp, MAX);
    
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
    fbo.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    
    if (bMousePressed) {
        ofNoFill();
        ofSetColor(255,63);
        ofBeginShape();
        for (int i = 0; i < path.size(); i++) {
            ofVertex(path[i].x, path[i].y);
        }
        ofEndShape();
        ofFill();
    }
}

void Waves::mouseDragged(int x, int y, int button){
    bMousePressed = true;
    path.push_back(ofVec2f(x, y));
}

void Waves::mousePressed(int x, int y, int button){
    path.clear();
}

void Waves::mouseReleased(int x, int y, int button){
    bMousePressed = false;
    if(counter < MAX){
        counter++;
        fadeout = false;
        level = 0.0;
        
        WaveParams w;
        w.synth = new ofxSCSynth("col_closesaw");
        w.synth->create();
        
        float detune = ofRandom(-0.15, 0.15);
        int nth = counter;
        //startTime = ofGetElapsedTimef();
        
        w.synth->set("gate", 1);
        w.synth->set("amp", 0.75);
        w.synth->set("rq", 1.0);
        w.synth->set("n", nth);
        w.synth->set("detune", detune);
        w.synth->create();
        waveParams.push_back(w);
    }
}

void Waves::keyPressed(int key){
    if (key == 'a') {
        if(counter < MAX){
            counter++;
            fadeout = false;
            level = 0.0;
            
            WaveParams w;
            w.synth = new ofxSCSynth("col_closesaw");
            w.synth->create();
            
            float detune = ofRandom(-0.15, 0.15);
            int nth = counter;
            //startTime = ofGetElapsedTimef();
            
            w.synth->set("gate", 1);
            w.synth->set("amp", 0.75);
            w.synth->set("rq", 1.0);
            w.synth->set("n", nth);
            w.synth->set("detune", detune);
            w.synth->create();
            waveParams.push_back(w);
        }
    }
    if (key == 'd') {
        if(counter - fadeCount > 0){
            cout << "node ID = " << waveParams[fadeCount].synth->nodeID << endl;
            //if (waveParams[fadeCount].synth->nodeID < 3000 && waveParams[fadeCount].synth->nodeID > 2000) {
            waveParams[fadeCount].synth->set("gate", 0);
            //}
            fadeCount++;
            if (fadeCount < 0) {
                fadeCount = 0;
            }
            fadeout = true;
        }
    }
    if (key == 's') {
        waveParams[0].synth->free();
    }
}
string Waves::getName(){
    return "waves";
}
