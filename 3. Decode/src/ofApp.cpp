#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	this->setProperties();

	gui.init();
	auto instructions = gui.addInstructions();
	gui.add(this->decoder.getCameraInProjector(), "Camera in Projector");
	gui.add(this->decoder.getProjectorInCamera(), "Projector in Camera");
	
	instructions->onDraw += [this] (ofxCvGui::DrawArguments& args) {
		ofxCvGui::AssetRegister.drawText(this->statusText, 20, 300);
	};

	this->buildStatus();
}

//--------------------------------------------------------------
void ofApp::update(){
	decoder.update();
	this->buildStatus();
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
void ofApp::buildStatus() {
	stringstream status;
	status << "Projector Width (px):  " << this->payload.getWidth() << endl;
	status << "Projector Height (px):  " << this->payload.getHeight() << endl;
	status << "Thresold:              " << (int) this->decoder.getThreshold() << endl;
	this->statusText = status.str();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
	case 'p':
		this->setProperties();
		break;
	case OF_KEY_UP:
		{
		int threshold = this->decoder.getThreshold();
		threshold++;
		threshold = ofClamp(threshold, 0, 255);
		this->decoder.setThreshold(threshold);
		break;
		}
	case OF_KEY_DOWN:
		{
		int threshold = this->decoder.getThreshold();
		threshold--;
		threshold = ofClamp(threshold, 0, 255);
		this->decoder.setThreshold(threshold);
		break;
		}
	case 's':
		this->decoder.saveDataSet();
		break;
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
	this->decoder.reset();
	auto & files = dragInfo.files;
	sort(files.begin(), files.end());

	for(auto entry : files) {
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
