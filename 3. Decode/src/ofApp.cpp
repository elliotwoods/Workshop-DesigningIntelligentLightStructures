#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	auto result = ofSystemTextBoxDialog("Projector Width (px)");
	int width = ofToInt(result);
	result = ofSystemTextBoxDialog("Projector Height (px)");
	int height = ofToInt(result);

	if (width <= 0 || height <= 0) {
		ofSystemAlertDialog("Invalid size selected, quitting.");
		ofExit();
	}

	this->payload.init(width, height);
	this->decoder.init(this->payload);

	auto folderResult = ofSystemLoadDialog("Select folder containing graycode captures", true);
	if (!folderResult.bSuccess) {
		ofSystemAlertDialog("Invalid folder selection (somehow :) )");
		ofExit();
	}

	ofDirectory folderList;
	folderList.listDir(folderResult.filePath);

	auto files = folderList.getFiles();
	for(auto file : files) {
		if (!(ofToUpper(file.getExtension()) == "JPG")) {
			continue;
		}
		ofImage loader;
		loader.loadImage(file);
		cout << "Decoding image " << file.getFileName() << endl;
		decoder << loader;
	}

	if (decoder.hasData()) {
		decoder.saveDataSet();
	}

	this->showProjector = false;
	this->keyPressed(' ');
}

//--------------------------------------------------------------
void ofApp::update(){
	decoder.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (showProjector) {
		decoder.getCameraInProjector().draw(0,0);
	} else {
		decoder.getProjectorInCamera().draw(0,0);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		showProjector ^= true;
		if(showProjector) {
			ofSetWindowShape(this->payload.getWidth(), this->payload.getHeight());
		} else {
			ofSetWindowShape(this->decoder.getWidth(), this->decoder.getHeight());
		}
	}
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
