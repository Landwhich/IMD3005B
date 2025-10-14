#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "Constants.h"

class ofApp : public ofBaseApp{

	public:
		ofImage m_origImg;
        ofImage m_edittedImg;

		// GUI
		ofxImGui::Gui m_gui;

		void setup();
		void update();
		void draw();
		void exit();


		void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		
};
