#include "Blink.h"

float pulseFreq[20] = {};
ofVec3f col[20];

void Blink::setup(){
    shader.load("blink");
    for (int i = 0; i < 1; i++) {
        col[i] = ofVec3f(ofRandom(1.0),ofRandom(1.0),ofRandom(1.0));
        pulseFreq[i] = ofRandom(10,20) * 10.0 * pi;
    }
}

void Blink::update(){
}

void Blink::draw(){
    ofBackground(0);

    float time = ofGetElapsedTimef();
    float resolution[] = {width, height};

    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1fv("pulseFreq", pulseFreq, 20);

    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    shader.end();
    fbo.end();
}

string Blink::getName(){
    return "blink";
}

