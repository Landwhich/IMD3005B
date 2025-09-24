#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{
	public:
		
	ofCamera camera; 
	ofLight light;

	// entity models
	ofxAssimpModelLoader sol;
	ofxAssimpModelLoader mars; // too lazy to get unique planet models
	ofxAssimpModelLoader mars2;
	ofxAssimpModelLoader mars3;
	ofxAssimpModelLoader mars4;
	ofxAssimpModelLoader phobos;
	ofxAssimpModelLoader deimos;

	// entity textures
	ofTexture marsTexture;
	ofTexture moonTexture;
	ofTexture solTexture;

	// entity attributes
	ofVec2f m_solPos;
	ofVec2f m_marsPos;
	ofVec2f m_marsPos2;
	ofVec2f m_marsPos3;
	ofVec2f m_marsPos4;
	float m_rotFast;
	float m_rotMed;
	float m_rotSlow;
	ofVec2f m_phobosPos;
	ofVec2f m_deimosPos;

	void setup();
	void update();
	void draw();
	
	// void keyPressed(int key);
	// void keyReleased(int key);
	// void mouseMoved(int x, int y);
	// void mouseDragged(int x, int y, int button);
	// void mousePressed(int x, int y, int button);
	// void mouseReleased(int x, int y, int button);
	// void windowResized(int w, int h);
	// void dragEvent(ofDragInfo dragInfo);
	// void gotMessage(ofMessage msg);

	ofShader shader;
	ofPlanePrimitive plane;


};
