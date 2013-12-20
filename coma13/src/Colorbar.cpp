#include "Colorbar.h"

void Colorbar::setup(){
    shader.load("colorbar");

    //init array & deque
    for (int i = 0; i < NUM; i++) {
        dfreq.push_back(0.0);
        dphase.push_back(0.0);
        damp.push_back(0.0);
        dlfo.push_back(0.0);
    }
    float* freq = &dfreq[0];
    float* phase = &dphase[0];
    float* lfo = &dlfo[0];
    float* amp = &damp[0];
    //check array
    for (int i = 0; i < NUM; i++) {
        cout << freq[i] << ", ";
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
    
     //if (counter > 0 && amp[counter - 1] < 1.0) {
     //    amp[counter - 1] += 0.01;
     //}
}

void Colorbar::mousePressed(int x, int y, int button){
    bMousePressed = true;
    drawPos.x = x;
    drawPos.y = y;
}

void Colorbar::mouseReleased(int x, int y, int button){
    //GLSL
    //if (counter < NUM) {
    
    float dir;
    if (counter % 2 == 0) {
        dir = 1.0;
    } else {
        dir = -1.0;
    }
    
    dfreq.push_back(powf(ofMap(y, 0, ofGetHeight(), 10, 0.1), 5.0));
    dfreq.pop_front();
    dphase.push_back(ofRandom(40, 50) * dir);
    dphase.pop_front();
    dlfo.push_back(ofRandom(1,2));
    dlfo.pop_front();
    damp.push_back(1.0);
    damp.pop_front();
    
    std::copy(dfreq.begin(), dfreq.end(), freq);
    std::copy(dphase.begin(), dphase.end(), phase);
    std::copy(dlfo.begin(), dlfo.end(), lfo);
    std::copy(damp.begin(), damp.end(), amp);
    
    counter++;
    
    //SC
    float dist = drawPos.distance(ofVec2f(x, y));
    if (dist > 100.0) {
        dist = 100.0;
    }
    float amp = ofMap(dist, 0.0, 100.0, 0.0, 0.3);
    int note  = int(ofMap(drawPos.y, 0, ofGetHeight(), 85, 1));
    float sfreq = 20 + 20 * pow((13.0/12.0), note);
    float pan = ofMap(x, 0, ofGetWidth(), -1.0, 1.0);
    ofxSCSynth *s = new ofxSCSynth("col_sine");
    s->create();
    s->set("gate", 1);
    s->set("freq", sfreq);
    s->set("lfoFreq",1.0);
    s->set("pan", pan);
    s->set("amp", amp);
    synth.push_back(s);
    
    //}
    
    for (int i = 0; i < NUM; i++) {
        cout << freq[i] << ", ";
    }
    cout << endl;
}

void Colorbar::keyPressed(int key){
    if (key == 'd') {
        dfreq.pop_back();
        dfreq.push_front(0);
        dphase.pop_back();
        dphase.push_front(0);
        dlfo.pop_back();
        dlfo.push_front(0);
        
        if (synth.size() > 0) {
            //synth[synth.size()-1]->free();
            synth[synth.size()-1]->set("gate", 0);
            synth.pop_back();
        }
        
        cout << "synth:" << endl;
        for (int i = 0; i < synth.size(); i++) {
            cout << synth[i] << ", ";
        }
        cout << endl;
        
        std::copy(dfreq.begin(), dfreq.end(), freq);
        std::copy(dphase.begin(), dphase.end(), phase);
        std::copy(dlfo.begin(), dlfo.end(), lfo);
        std::copy(damp.begin(), damp.end(), amp);
        
        //check array
        for (int i = 0; i < NUM; i++) {
            cout << freq[i] << ", ";
        }
    }

}

string Colorbar::getName(){
    return "colorbar";
}

