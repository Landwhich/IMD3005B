#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "Constants.h"

class ofApp : public ofBaseApp{

	public:
		ofImage m_origImg;
        ofImage m_edittedImg;
    
        //GUI stuff
        float m_brightness;
        float m_contrast;
    
        ofxImGui::Gui m_gui;
    
		void setup();
		void update();
		void draw();
        void exit();
    
        void applyBrightness(float &intensity);
        void applyContrast(float &intensity);
        void enableSharpenFilter();
		void enableEdgeDetectionFilter();
		void enableEmbossFilter();
        void enableBoxBlurFilter();
        void applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType);

		//some extra functions you may want to explore
        void convertGrayscale(int x, int y);
		ofColor eyeDropper(int x, int y);
		void paint(ofColor color);
		ofRectangle magicWand(int x, int y);

		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		
};
