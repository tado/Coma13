#include "ColorSphere.h"

void ColorSphere::setup(){
    
}

void ColorSphere::stateEnter(){
    shader.load("colorSphere");
    counter = 0;
    fx = new ofxSCSynth("col_fx");
    fx->create();
    
    for (int i = 0; i < MAX_SYNTH; i++) {
        col[i] = 0;
        freq[i] = 0;
        phase[i] = 0;
        amp[i] = 0;
        lfo[i] = 0;
        shaderParams[i].col = 0;
        shaderParams[i].freq = 0.0;
        shaderParams[i].phase = 0.0;
        shaderParams[i].lfo = 0.0;
        shaderParams[i].amp = 0.0;
    }
    drawGlitch = false;
}

void ColorSphere::stateExit(){
    fx->free();
    glitchSynth->free();
    for(int i = 0; i < shaderParams.size(); i++){
        shaderParams[i].synth->set("gate", 0);
    }
    shaderParams.clear();
    shader.unload();
}

void ColorSphere::update(){
    /*
     for (int i = 0; i < shaderParams.size(); i++) {
     cout << shaderParams[i].amp << ", ";
     }
     cout << endl;
     */
}

void ColorSphere::draw(){
    ofBackground(0);
    
    float time = ofGetElapsedTimef();
    float resolution[] = {ofGetWidth(), ofGetHeight()};
    for (int i = 0; i < MAX_SYNTH; i++) {
        col[i] = 0;
        freq[i] = 0;
        phase[i] = 0;
        amp[i] = 0;
        lfo[i] = 0;
    }
    for (int i = 0; i < shaderParams.size(); i++) {
        col[i] = shaderParams[i].col;
        freq[i] = shaderParams[i].freq;
        phase[i] = shaderParams[i].phase;
        lfo[i] = shaderParams[i].lfo;
        if(shaderParams[i].amp < 1.0){
            shaderParams[i].amp += 0.005;
            if(shaderParams[i].amp > 1.0){
                shaderParams[i].amp  = 1.0;
            }
        }
        amp[i] = shaderParams[i].amp;
    }
    
    
    fbo.begin();
    shader.begin();
    shader.setUniform1f("time", time);
    shader.setUniform2fv("resolution", resolution);
    shader.setUniform1iv("col", col, MAX_SYNTH);
    shader.setUniform1fv("freq", freq, MAX_SYNTH);
    shader.setUniform1fv("phase", phase, MAX_SYNTH);
    shader.setUniform1fv("amp", amp, MAX_SYNTH);
    shader.setUniform1fv("lfo", lfo, MAX_SYNTH);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2, -ofGetWidth()/15.0);
    ofRotateX(ofGetElapsedTimef() * 5);
    ofRotateY(ofGetElapsedTimef() * 7);
    sphere.set(ofGetWidth()/2, 128);
    sphere.draw();
    ofPopMatrix();
    shader.end();
    fbo.end();

    //Glitch!!
    float gscale = (ofGetElapsedTimef() - glitchStartTime) * 1.0;
    if (gscale > 255) {
        gscale = 255;
    }
    if(drawGlitch) {
        ofSetColor(255,gscale);
        fbo2.allocate(ofRandom(500,1500),ofRandom(500,1500));
        fbo2.draw(ofGetWidth(), ofGetHeight(), -ofGetWidth(), -ofGetHeight());
        float lpf = ofMap(gscale, 0, 255, 0, 1000) + 10;
        float gain = ofMap(gscale, 0, 255, 1.0, 5.0);
        glitchSynth->set("lpf", lpf);
        glitchSynth->set("gain", gain);
    }

    ofDisableBlendMode();
}

void ColorSphere::mousePressed(int x, int y, int button){
    bMousePressed = true;
    drawPos.x = x;
    drawPos.y = y;
}

void ColorSphere::mouseReleased(int x, int y, int button){
    //GLSL
    float dir;
    shaderParams.size() % 2 == 0 ? dir = 1.0 : dir = -1.0;
    ShaderParams sd;
    sd.col = counter % 4;
    sd.freq = powf(ofMap(y, 0, ofGetHeight(), 4, 0.5), 5.0);
    sd.phase = ofRandom(200, 500) * dir;
    sd.lfo = ofRandom(1,2);
    sd.amp = 0.0;
    
    //SC
    float dist = drawPos.distance(ofVec2f(x, y));
    if (dist > 100.0) {
        dist = 100.0;
    }
    float amp = ofMap(dist, 0.0, 100.0, 0.0, 0.3);
    int note  = int(ofMap(drawPos.y, 0, ofGetHeight(), 85, 1));
    float freq = 50 + 20 * pow((13.0/12.0), note);
    //float pan = ofMap(x, 0, ofGetWidth(), -1.0, 1.0);
    float pan = ofRandom(-0.5, 0.5);
    sd.synth = new ofxSCSynth("col_sine");
    sd.synth->create();
    sd.synth->set("gate", 1);
    sd.synth->set("freq", freq);
    sd.synth->set("lfoFreq",1.0);
    sd.synth->set("pan", pan);
    sd.synth->set("amp", amp);
    shaderParams.push_back(sd);
    
    if (shaderParams.size() > MAX_SYNTH) {
        shaderParams[0].synth->set("gate", 0);
        shaderParams.pop_front();
    }
    
    counter++;
}

void ColorSphere::keyPressed(int key){
    if (key == 'd') {
        if(shaderParams.size() > 0){
            shaderParams[0].synth->set("gate", 0);
            shaderParams.pop_front();
        }
    }
    if (key == 'g') {
        drawGlitch = true;
        glitchStartTime = ofGetElapsedTimef();
        glitchSynth = new ofxSCSynth("col_harmony");
        glitchSynth->create();
        glitchSynth->set("lpf", 10);
    }
}

string ColorSphere::getName(){
    return "colorSphere";
}