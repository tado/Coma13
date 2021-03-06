#include "testApp.h"
#include "ColorSphere.h"
#include "Waves.h"

//--------------------------------------------------------------
void testApp::setup(){
    //ofSetVerticalSync(true);
    ofxSuperColliderServer::init(57110, 96000);
    ofSetCircleResolution(32);
    
	stateMachine.addState<ColorSphere>();
    stateMachine.addState<Waves>();
	stateMachine.changeState("waves");
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'q':
            stateMachine.changeState("colorSphere");
            break;
        case 'w':
            stateMachine.changeState("waves");
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
