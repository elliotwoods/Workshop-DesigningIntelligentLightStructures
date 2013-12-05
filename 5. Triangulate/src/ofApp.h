#pragma once

#include "ofMain.h"
#include "ofxCvGui.h"
#include "ofxTriangulate.h"
#include "ofxGraycode.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void calc();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxCvGui::Builder gui;
		ofMesh pointCloud;
		ofNode node;
		ofxRay::Camera camera;
		ofxRay::Projector projector;

		ofImage imageCamera;
		ofImage imageProjector;
		ofFloatImage worldImage;

		ofPtr<ofxCvGui::Panels::Node> nodePanel;
};
