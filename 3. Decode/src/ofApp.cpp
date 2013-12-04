#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->bangSetProperties = false;
	this->setProperties();

	gui.init();
	gui.addInstructions();
	gui.add(this->decoder.getCameraInProjector(), "Camera in Projector");
	gui.add(this->decoder.getProjectorInCamera(), "Projector in Camera");
	auto controlPanel = gui.addBlank("Controls");
	controlPanel->setWidgets(this->widgets);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (this->bangSetProperties) {
		this->setProperties();
		this->bangSetProperties = false;
	}
	decoder.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::setProperties() {
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
}

//--------------------------------------------------------------
void ofApp::buildWidgets() {
	this->widgets.removeWidgets();
	this->widgets.addButton("Set properties", this->bangSetProperties);
	this->widgets.addLabel("Projector width", ofToString(this->payload.getWidth()));
	this->widgets.addLabel("Projector height", ofToString(this->payload.getHeight()));
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
	this->decoder.reset();
	for(auto entry : dragInfo.files) {
		auto file = ofFile(entry, ofFile::Mode::Reference);
		if (!(ofToUpper(file.getExtension()) == "JPG")) {
			continue;
		}
		ofImage loader;
		loader.loadImage(file);
		cout << "Decoding image " << file.getFileName() << endl;
		decoder << loader;
	}
	if (!this->decoder.hasData()) {
		ofSystemAlertDialog("We didn't get enough frames for a full dataset. Check that you have " + ofToString(this->payload.getFrameCount()) + " images in your captures set.");
	}
}
