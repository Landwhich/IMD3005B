#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    ofSetFrameRate(Constants::FRAMERATE);
    
    m_origImg.load(Constants::IMG_PATH);
	m_edittedImg = m_origImg; //this clones data
    
    //for some really cool projects that use "dear imgui" https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui
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
        
            if (ImGui::SliderFloat("Brightness", &m_brightness, -255.0f, 255.0f) ) {
                applyBrightness(m_brightness);
            }
        
            if(ImGui::SliderFloat("Contrast", &m_contrast, -255.0f, 255.0f)) {
                applyContrast(m_contrast);
            }
    
            if (ImGui::Button("Randomize!", ofVec2f(ImGui::GetWindowSize().x, 40.0f))) {
                m_brightness = ofRandom(-255.0f, 255.0f);
                m_contrast = ofRandom(-255.0f, 255.0f);
                applyBrightness(m_brightness);
                applyContrast(m_contrast);
            }
    
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Image Sharpen", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableSharpenFilter();
            }
        
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Edge Detection", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableEdgeDetectionFilter();
            }
            
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Emboss", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableEmbossFilter();
            }
            
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Box Blur", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableBoxBlurFilter();
            }
        ImGui::End();
    m_gui.end();
}

void ofApp::exit(){}

//1
void ofApp::applyBrightness(float &intensity) {
    ofColor tempCol;
    ofColor newCol;
    
    for(int y = 0; y < m_origImg.getHeight(); y++){
        for(int x = 0; x < m_origImg.getWidth(); x++){
            tempCol = m_origImg.getColor(x, y);
        
//            integer overflow :( or ... maybe :)
//            newCol.set( tempCol.r + intensity,
//                        tempCol.g + intensity,
//                        tempCol.b + intensity );
            
            //no integer overflow :)
            newCol.set( MAX(MIN(tempCol.r + intensity, 255.0f), 0.0f),
                        MAX(MIN(tempCol.g + intensity, 255.0f), 0.0f),
                        MAX(MIN(tempCol.b + intensity, 255.0f), 0.0f) );
            
            m_edittedImg.setColor(x, y, newCol);
        }
    }
    
    m_edittedImg.update();
}

//2
void ofApp::applyContrast(float &intensity) {
    ofColor tempCol;
    ofColor newCol;
    
    //contrastfactoralgorithmF = 259*(255+C)/255*(259-C) https://ie.nitk.ac.in/blog/2020/01/19/algorithms-for-adjusting-brightness-and-contrast-of-an-image/
    float contrastFactor = (259.0f * (intensity + 255.0f)) / (255.0f * (259.0f - intensity));
    
    for(int y = 0; y < m_origImg.getHeight(); y++){
        for(int x = 0; x < m_origImg.getWidth(); x++){
            tempCol = m_origImg.getColor(x, y);
            
            //no integer overflow :)
            newCol.set( MAX(MIN(contrastFactor * (tempCol.r - 128.0f) + 128.0f, 255.0f), 0.0f),
                        MAX(MIN(contrastFactor * (tempCol.g - 128.0f) + 128.0f, 255.0f), 0.0f),
                        MAX(MIN(contrastFactor * (tempCol.b - 128.0f) + 128.0f, 255.0f), 0.0f) );
            
            m_edittedImg.setColor(x, y, newCol);
        }
    }
    
    m_edittedImg.update();
}

void ofApp::enableSharpenFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::SHARPEN);
};

void ofApp::enableEdgeDetectionFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EDGE_DETECTION);
};

void ofApp::enableEmbossFilter() {
	applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EMBOSS);
};

void ofApp::enableBoxBlurFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::BOX_BLUR);
};

void ofApp::applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType) {
    ofColor tempCol;
    ofColor newCol;
	ofVec3f sum;
	int neighbourX = 0;
	int neighbourY = 0;
    int startIndex = (int)matType * 9;
    int imgWidth = m_origImg.getWidth();
    int imgHeight = m_origImg.getHeight();

	//std::cout << startIndex << std::endl;
        
    for(int y = 0; y < imgHeight; y++) {
        for(int x = 0; x < imgWidth; x++) {
			//newCol.set(0, 0, 0);
			sum.set(0.0f, 0.0f, 0.0f);
            
            //go through kernel 3x3 = 9 length
			for (int k = startIndex; k < startIndex + 9; k++) {

				//std::cout << k << std::endl;

				//check if we are trying to access an image coordinate out of bounds. Extend edges if so.
				//note that we need k here to start at 0 so we use modulo (%) to get the integer remainder of k / 9
				neighbourX = x + Constants::CONVOLUTION_KERNAL_CONVERT_X[k % 9];
				if (neighbourX < 0) {
					neighbourX = 0;
				}
				else if (neighbourX > imgWidth - 1) {
					neighbourX = imgWidth - 1;
				}

				neighbourY = y + Constants::CONVOLUTION_KERNAL_CONVERT_Y[k % 9];
				if (neighbourY < 0) {
					neighbourY = 0;
				}
				else if (neighbourY > imgHeight - 1) {
					neighbourY = imgHeight - 1;
				}
                
                //find out which 2D coordinate of image this k belongs to
                tempCol = m_origImg.getColor(neighbourX, neighbourY);
                
                //sum up kernel factors
				sum.x += tempCol.r * Constants::CONVOLUTION_MATS_3X3[k];
				sum.y += tempCol.g * Constants::CONVOLUTION_MATS_3X3[k];
				sum.z += tempCol.b * Constants::CONVOLUTION_MATS_3X3[k];
            }
            
			//std::cout << newCol << std::endl;

            //make sure values are in bounds
            newCol.set( MAX(MIN(sum.x, 255.0f), 0.0f),
                        MAX(MIN(sum.y, 255.0f), 0.0f),
                        MAX(MIN(sum.z, 255.0f), 0.0f) );
            
            m_edittedImg.setColor(x, y, newCol);
        }
    }
    
    m_edittedImg.update();
}

void ofApp::keyPressed(int key){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseDragged(int x, int y, int button) {
    
}
