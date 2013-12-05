#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	gui.init();
	gui.addInstructions();

	this->nodePanel = gui.add(node, "Scene");
	nodePanel->onDraw3d += [this] (ofNode&) {
		this->pointCloud.drawVertices();

		this->projector.draw();
		this->camera.draw();

		if (this->imageCamera.isAllocated()) {
			this->camera.drawOnNearPlane(this->imageCamera);
		}
		if (this->imageProjector.isAllocated()) {
			this->projector.drawOnNearPlane(this->imageProjector);
		}
	};
	nodePanel->setGridEnabled(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::calc() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'c') {
		bool enabled = false;
		enabled = !enabled;
		this->nodePanel->setCursorEnabled(enabled);
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
vector<double> loadDoubles(string& filename) {
	ifstream file;
	file.open(ofToDataPath(filename).c_str(), ios::in | ios::binary);
	vector<double> result;
	if (file.is_open()) {
		while(!file.eof()) {
			double peek;
			file.read((char*)&peek, sizeof(double));
			result.push_back(peek);
		}
		result.pop_back();
	} else {
		ofLogError() << "Failed to load file " << filename;
	}
	return result;
}

ofMatrix4x4 loadMatrix(string& filename) {
	auto buffer = loadDoubles(filename);
	if (buffer.size() >= 16) {
		ofMatrix4x4 m;
		auto floatBuffer = m.getPtr();
		for(int i=0; i<16; i++) {
			floatBuffer[i] = buffer[i];
		}

		ofMatrix4x4 reverseZ;
		reverseZ.scale(1.0f, 1.0f, -1.0f);
		return reverseZ * m * reverseZ;
	} else {
		return ofMatrix4x4();
	}
}

bool isCamera(string filename) {
	return filename.find("camera") != string::npos;
}

bool isProjector(string filename) {
	return filename.find("projector") != string::npos;
}

bool isView(string filename) {
	return filename.find("view") != string::npos;
}

bool isProjection(string filename) {
	return filename.find("projection") != string::npos;
}

bool isGraycode(string filename) {
	return filename.find(".sl") != string::npos;
}

void ofApp::dragEvent(ofDragInfo dragInfo){ 
	for(auto filename : dragInfo.files) {
		cout << "Loading file " << filename << endl;
		if (isCamera(filename)) {
			if (isView(filename)) {
				this->camera.setView(loadMatrix(filename));
			} else if (isProjection(filename)) {
				this->camera.setProjection(loadMatrix(filename));
			}
		} else if (isProjector(filename)) {
			if (isView(filename)) {
				this->projector.setView(loadMatrix(filename));
			} else if (isProjection(filename)) {
				this->projector.setProjection(loadMatrix(filename));
			}
		} else if (isGraycode(filename)) {
			ofxGraycode::PayloadGraycode payload;
			ofxGraycode::Decoder decoder;

			int projectorWidth = ofToInt(ofSystemTextBoxDialog("Projector Width"));
			int projectorHeight = ofToInt(ofSystemTextBoxDialog("Projector Height"));
			if (projectorWidth < 1 || projectorHeight < 1) {
				ofSystemAlertDialog("Please select valid projector width and height");
				return;
			}
			payload.init(projectorWidth, projectorHeight);
			decoder.init(payload);
			decoder.loadDataSet(filename);
			
			this->camera.setWidth(decoder.getWidth());
			this->camera.setHeight(decoder.getHeight());
			this->projector.setWidth(projectorWidth);
			this->projector.setHeight(projectorHeight);

			cout << "Triangulating with Camera [" << this->camera.getWidth() << "," << this->camera.getHeight() << "], Projetor [" << this->projector.getWidth() << "," << this->projector.getHeight() << "]" << endl;
			
			ofxTriangulate::Triangulate(decoder.getDataSet(), this->camera, this->projector, this->pointCloud, 0.4f); 
			imageCamera = decoder.getDataSet().getMedian();
			imageProjector = decoder.getDataSet().getMedianInverse();
			imageCamera.update();
			imageProjector.update();

			ofFloatImage world;
			world.allocate(projector.getWidth(), projector.getHeight(), OF_IMAGE_COLOR);
			int pixelCount = projector.getWidth() * projector.getHeight();
			ofVec3f * xyz = (ofVec3f*) world.getPixels();
			for(int i=0; i<pixelCount; i++) {
				*xyz++ = ofVec3f(0.0f, 0.0f, 0.0f);
			}

			xyz = (ofVec3f*) world.getPixels();
			for(const auto pixel : decoder.getDataSet()) {
				ofVec3f newPoint;
				bool success = ofxTriangulate::Triangulate(pixel.camera, pixel.projector, this->camera, this->projector, newPoint, 0.4f);		
				if (success) {
					xyz[pixel.projector] = newPoint;
				}
			}

			auto saveDialog = ofSystemSaveDialog("output.exr", "Save World map");
			if (saveDialog.bSuccess) {
				world.saveImage(saveDialog.fileName);
			}
		}
	}
}
