#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    ofSetFrameRate(Constants::FRAMERATE);
    
    m_origImg.load(Constants::IMG_PATH);
	m_edittedImg = m_origImg;
    
    m_gui.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    m_edittedImg.draw(0,0);
    m_origImg.draw(m_origImg.getWidth(), 0.0, m_origImg.getWidth()/4.0f,m_origImg.getHeight()/4.0f);
    
    //imgui uses "immediate" mode so everything is drawn and calculated precisely when drawn
    //i.e., no real setup which allows more flexibility / dynamic gui where all code is in one place and can be easily removed / hidden via a boolean
    m_gui.begin();
        ImGui::SetNextWindowPos(ofVec2f(m_origImg.getWidth() + 20, m_origImg.getHeight()/4.0f + 20.0f), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ofVec2f(300,300), ImGuiCond_Once);
        ImGui::Begin("Control Panel");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
            // if (ImGui::SliderFloat("Brightness", &m_brightness, -255.0f, 255.0f) ) {
            //     applyBrightness(m_brightness);
            // }
        
            // if(ImGui::SliderFloat("Contrast", &m_contrast, -255.0f, 255.0f)) {
            //     applyContrast(m_contrast);
            // }
    
            // if (ImGui::Button("Randomize!", ofVec2f(ImGui::GetWindowSize().x, 40.0f))) {
            //     m_brightness = ofRandom(-255.0f, 255.0f);
            //     m_contrast = ofRandom(-255.0f, 255.0f);
            //     applyBrightness(m_brightness);
            //     applyContrast(m_contrast);
            // }
    
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            // ImGui::SetNextItemWidth(100);
            // if (ImGui::Button("Enable Image Sharpen", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
            //     enableSharpenFilter();
            // }
        
            // ImGui::SetNextItemWidth(100);
            // if (ImGui::Button("Enable Edge Detection", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
            //     enableEdgeDetectionFilter();
            // }
            
            // ImGui::SetNextItemWidth(100);
            // if (ImGui::Button("Enable Emboss", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
            //     enableEmbossFilter();
            // }
            
            // ImGui::SetNextItemWidth(100);
            // if (ImGui::Button("Enable Box Blur", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
            //     enableBoxBlurFilter();
            // }
        ImGui::End();
    m_gui.end();
}

void ofApp::exit(){}

// --------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}
