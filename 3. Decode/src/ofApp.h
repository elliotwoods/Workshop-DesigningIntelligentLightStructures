#pragma once

#include "ofMain.h"
#include "ofxGraycode.h"
#include "ofxCvGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void setProperties();
		void buildWidgets();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		ofxGraycode::PayloadGraycode payload;
		ofxGraycode::Decoder decoder;

		bool showProjector;
		ofxCvGui::Builder gui;
		ofxUICanvas widgets;

		//widget controls;
		bool bangSetProperties;
};
