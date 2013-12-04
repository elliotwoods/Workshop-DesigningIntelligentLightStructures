#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.init();
	auto scenePanel = gui.add(this->scene, "Scene");
	scenePanel->onDraw += [] (ofxCvGui::DrawArguments&) {
		ofBackgroundGradient(40, 0);
	};
	scenePanel->onDraw3d += [this] (ofNode&) {
		this->pointCloud.drawVertices();
	};
	scenePanel->setGridEnabled(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
