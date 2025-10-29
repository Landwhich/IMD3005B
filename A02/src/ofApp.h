#pragma once

#include "ofMain.h"
#include "ofxImGui.h"
#include "Constants.h"

class ofApp : public ofBaseApp{

	public:
		ofImage m_origImg;
        ofImage m_edittedImg;
        int m_imgIdx;
    
        //GUI stuff
        float m_brightness;
        float m_contrast;
        // eyedropper GUI
        ofColor m_eyeDropperColor;
        bool m_eyeDropperActive = false;
    
        ofxImGui::Gui m_gui;
    
		void setup();
		void update();
		void draw();
        void exit();
    
        void applyBrightness(float &intensity);
        void applyContrast(float &intensity);
        // 3X3 CONV MATRICES
        void enableSharpenFilter();
		void enableVerticalEdgeDetectionFilter();
        void enableHorizontalEdgeDetectionFilter();
		void enableEmbossFilter();
        void enableBoxBlurFilter();
        void enableEdgeEnhanceFilter();
        // 5X5 CONV MATRICES
        void enableGaussianBlurFilter();
        void enableBoxBlur5X5Filter();
        void enableSharpen5X5Filter();
        void enableEdgeDetection5X5Filter();
        void enableEmboss5X5Filter();

        void applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType);
        void applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE matType);
        // float[] rotate5x5Matrix(float[] matrix)

        // void eyeDropper();
		//some extra functions you may want to explore
        // void convertGrayscale(int x, int y);
		// void paint(ofColor color);
		// ofRectangle magicWand(int x, int y);

		void keyPressed(int key);
        void mousePressed(int x, int y, int button);
		void mouseDragged(int x, int y, int button);
		
};
