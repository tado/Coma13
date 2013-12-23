#include "ColorSphere.h"

void ColorSphere::setup(){
    
}

void ColorSphere::stateEnter(){
    shader.load("colorSphere");
    blinkShader.load("blink");
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
    drawPulse = false;
    sphereStartTime = ofGetElapsedTimef();
    bComb = false;
}

void ColorSphere::stateExit(){
    //fx->free();
    glitchSynth->free();
    pluseSynth->free();
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
    
    if (bComb) {
        float combAmp = ofMap(movePos.y, 0, ofGetHeight(), 1.0, 0.0);
        float delay = ofMap(movePos.x, 0, ofGetWidth(), 0.001, 0.1);
        if(delay < 0.001){
            delay = 0.001;
        }
        fx->set("combAmp", combAmp);
        fx->set("delay", delay);
    }
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
    float radius = sin((ofGetElapsedTimef() - sphereStartTime) / 60.0) * ofGetWidth()/7 + ofGetWidth()/2;
    //sphere.set(radius, 128);
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
        fbo2.draw(0, 0, ofGetWidth(), ofGetHeight());
        float lpf = ofMap(gscale, 0, 255, 0, 1200) + 10;
        float gain = ofMap(gscale, 0, 255, 0.0, 1.0);
        glitchSynth->set("lpf", lpf);
        glitchSynth->set("gain", gain);
    }
    if(drawPulse){
        //Pulse!!
        float pscale = (ofGetElapsedTimef() - pulseStartTime) * 2.0;
        if (pscale > 255) {
            pscale = 255;
        }
        float lpf = ofMap(pscale, 0, 255, 0, 800) + 10;
        pluseSynth->set("lpf", lpf);
        
        float imp = ofMap(pscale, 0, 255, 10, 16);
        pluseSynth->set("imp", imp);
    
        float gamp = ofMap(pscale, 0, 255, 1.0, 0.0);
        glitchSynth->set("amp", gamp);
        
        fbo3.begin();
        blinkShader.begin();
        blinkShader.setUniform1f("time", time);
        blinkShader.setUniform2fv("resolution", resolution);
        blinkShader.setUniform1f("amp", 1.0 - gamp);
        blinkShader.setUniform1f("freq", lpf * 40.0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        blinkShader.end();
        fbo3.end();
        fbo3.draw(0, ofGetHeight(), ofGetWidth(), -ofGetHeight());
    }
    
    if(bMousePressed){
        ofNoFill();
        ofSetColor(255,100);
        float radius = ofDist(draggedPos.x, draggedPos.y, drawPos.x, drawPos.y);
        ofCircle(drawPos.x, drawPos.y, radius);
        ofLine(0, drawPos.y, ofGetWidth(), drawPos.y);
        ofLine(drawPos.x, 0, drawPos.x, ofGetHeight());
        ofFill();
    }
    
    ofDisableBlendMode();

}

void ColorSphere::mouseMoved(int x, int y){
    movePos.x = x;
    movePos.y = y;
}

void ColorSphere::mousePressed(int x, int y, int button){
    drawPos.x = x;
    drawPos.y = y;
}

void ColorSphere::mouseDragged(int x, int y, int button){
    bMousePressed = true;
    draggedPos.x = x;
    draggedPos.y = y;
}

void ColorSphere::mouseReleased(int x, int y, int button){
    bMousePressed = false;
    //GLSL
    float dir;
    shaderParams.size() % 2 == 0 ? dir = 1.0 : dir = -1.0;
    ShaderParams sd;
    sd.col = counter % 4;
    sd.freq = powf(ofMap(y, 0, ofGetHeight(), 4, 0.5), 5.0);
    sd.phase = ofRandom(50, 100) * dir;
    sd.lfo = ofRandom(1,2);
    sd.amp = 0.0;
    
    //SC
    float dist = drawPos.distance(ofVec2f(x, y));
    if (dist > 100.0) {
        dist = 100.0;
    }
    float amp = ofMap(dist, 0.0, 100.0, 0.0, 0.1);
    int note  = int(ofMap(drawPos.y, 0, ofGetHeight(), 85, 1));
    float freq = 50 + 20 * pow((13.0/12.0), note);
    float pan = ofMap(x, 0, ofGetWidth(), -1.0, 1.0);
    //float pan = ofRandom(-0.5, 0.5);
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
        glitchSynth->set("gain", 0.0);
    }
    if (key == 'h') {
        drawPulse = true;
        pluseSynth = new ofxSCSynth("col_sawbass");
        pluseSynth->set("lpf", 100);
        pluseSynth->set("amp", 0.7);
        pluseSynth->create();
        pulseStartTime = ofGetElapsedTimef();
    }
    if(key == 'c'){
        if (bComb) {
            bComb = false;
            fx->set("combGate", 0.0);
        } else {
            bComb = true;
            fx->set("combGate", 1.0);
        }
    }
}

string ColorSphere::getName(){
    return "colorSphere";
}