#include "ofApp.h"

void ofApp::setup(){
    ofSetWindowShape(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT);
    ofSetFrameRate(Constants::FRAMERATE);
    
    m_imgIdx = 0;
    m_origImg.load(Constants::IMG_PATHS[m_imgIdx]);
	m_edittedImg = m_origImg; //this clones data
    m_eyeDropperColor.set(0,0,0);
    
    //for some really cool projects that use "dear imgui" https://github.com/ocornut/imgui/wiki/Software-using-dear-imgui
    m_gui.setup();
}

void ofApp::update(){

}

void ofApp::draw(){
    m_edittedImg.draw(0,0);
    m_origImg.draw(m_origImg.getWidth(), 0.0, m_origImg.getWidth()/4.0f,m_origImg.getHeight()/4.0f);
    
    //imgui uses "immediate" mode so everything is drawn and calculated precisely when drawn
    //i.e., no real setup which allows more flexibility / dynamic gui where all code is in one place and can be easily removed / hidden via a boolean
    m_gui.begin();
        ImGui::SetNextWindowPos(ofVec2f(m_origImg.getWidth() + 20, m_origImg.getHeight()/4.0f + 20.0f), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ofVec2f(580, m_origImg.getHeight()*3/4.0f - 20), ImGuiCond_Once);
        ImGui::Begin("Control Panel");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        
            if (ImGui::SliderFloat("Brightness", &m_brightness, -255.0f, 255.0f) ) {
                applyBrightness(m_brightness);
            }
        
            if(ImGui::SliderFloat("Contrast", &m_contrast, -255.0f, 255.0f)) {
                applyContrast(m_contrast);
            }
    
            if (ImGui::Button("Randomize!", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                m_brightness = ofRandom(-255.0f, 255.0f);
                m_contrast = ofRandom(-255.0f, 255.0f);
                applyBrightness(m_brightness);
                applyContrast(m_contrast);
            }
    
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();
            
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Image Sharpen", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableSharpenFilter();
            }
        
            // ImGui::SetNextItemWidth(120);
            if (ImGui::Button("Enable Vertical Edge Detection", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableVerticalEdgeDetectionFilter();
            }

            if (ImGui::Button("Enable Horizontal Edge Detection", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableHorizontalEdgeDetectionFilter();
            }
            
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Emboss", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableEmbossFilter();
            }
            
            // ImGui::SetNextItemWidth(100);
            if (ImGui::Button("Enable Box Blur", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableBoxBlurFilter();
            }

            if (ImGui::Button("Enable Edge Enhance", ofVec2f(ImGui::GetWindowSize().x, 20.0f))) {
                enableEdgeEnhanceFilter();
            }

            if (ImGui::Button("Enable Gauss Blur", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableGaussianBlurFilter();
            }

            if (ImGui::Button("Enable Box Blur 5x5", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableBoxBlur5X5Filter();
            }

            // if (ImGui::Button("Enable Sharpen 5x5", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
            //     enableSharpen5X5Filter();
            // }

            if (ImGui::Button("Enable Edge Detection 5x5", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableEdgeDetection5X5Filter();
            }

            if (ImGui::Button("Enable Emboss 5x5", ofVec2f(ImGui::GetWindowSize().x, 30.0f))) {
                enableEmboss5X5Filter();
            }

            if (ImGui::Button("Prev Img", ofVec2f(ImGui::GetWindowSize().x/3, 30.0f))) {
                int length = sizeof(Constants::IMG_PATHS) / sizeof(Constants::IMG_PATHS[0]);
                m_imgIdx = (m_imgIdx - 1 + length) % length;
                m_origImg.load(Constants::IMG_PATHS[m_imgIdx]);
                m_edittedImg = m_origImg;
            }
            ImGui::SameLine();
            if (ImGui::Button("Save Image", ofVec2f(ImGui::GetWindowSize().x/3, 30.0f))){
                m_edittedImg.save("savedImage.png");
            }
            ImGui::SameLine();
            if (ImGui::Button("Next Img", ofVec2f(ImGui::GetWindowSize().x/3, 30.0f))) {
                int length = sizeof(Constants::IMG_PATHS) / sizeof(Constants::IMG_PATHS[0]);
                m_imgIdx = (m_imgIdx + 1) % length;
                m_origImg.load(Constants::IMG_PATHS[m_imgIdx]);
                m_edittedImg = m_origImg;
            }

        ImGui::End();
        ImGui::SetNextWindowPos(ofVec2f(m_origImg.getWidth() + m_edittedImg.getWidth()/4 + 20, 20), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ofVec2f(580 - m_origImg.getWidth()/4, m_edittedImg.getHeight()/4 - 20), ImGuiCond_Once);
        ImGui::Begin("Eydropper Tool");
            ImGui::Text("EyeDropper color is: R: #%i, G: #%i, B: #%i", m_eyeDropperColor.r, m_eyeDropperColor.g, m_eyeDropperColor.b);
            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Button, m_eyeDropperColor);
            if (ImGui::Button("Eye Dropper Tool", ofVec2f(ImGui::GetWindowSize().x, 75.0f))) {
                // eyeDropper();
                m_eyeDropperActive = true;
            }
            ImGui::PopStyleColor();
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

// 3X3 CONV MATRICES

void ofApp::enableSharpenFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::SHARPEN);
};

void ofApp::enableVerticalEdgeDetectionFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EDGE_DETECTION_V);
};

void ofApp::enableHorizontalEdgeDetectionFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EDGE_DETECTION_H);
};

void ofApp::enableEmbossFilter() {
	applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EMBOSS);
};

void ofApp::enableBoxBlurFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::BOX_BLUR);
};

void ofApp::enableEdgeEnhanceFilter() {
    applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE::EDGE_ENHANCE);
};

// 5X5 CONV MATRICES

void ofApp::enableGaussianBlurFilter(){
    applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE::GAUSSIAN_BLUR);
}

void ofApp::enableBoxBlur5X5Filter(){
    applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE::BOX_BLUR_5X5);
}

void ofApp::enableSharpen5X5Filter(){
    applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE::SHARPEN_5X5);
}

void ofApp::enableEdgeDetection5X5Filter(){
    applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE::EDGE_DETECTION_5X5);
}

void ofApp::enableEmboss5X5Filter(){
    applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE::EMBOSS_5X5);
}

void ofApp::applyConvolution3x3(Constants::CONVOLUTION_MAT_TYPE matType) {
    
    if (!(matType >= 0  && matType < 100)){
        printf("matrix selected is not a 3X3");
        return;
    }
    
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
				neighbourX = x + Constants::CONVOLUTION_3X3_KERNAL_CONVERT_X[k % 9];
				if (neighbourX < 0) {
					neighbourX = 0;
				}
				else if (neighbourX > imgWidth - 1) {
					neighbourX = imgWidth - 1;
				}

				neighbourY = y + Constants::CONVOLUTION_3X3_KERNAL_CONVERT_Y[k % 9];
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

void ofApp::applyConvolution5x5(Constants::CONVOLUTION_MAT_TYPE matType) {

    if (!(matType > 99 && matType < 200)){
        printf("matrix selected is not one of type 5X5");
        return;
    }

    ofColor tempCol;
    ofColor newCol;
	ofVec3f sum;
	int neighbourX = 0;
	int neighbourY = 0;
    int startIndex = (int)(matType - 100) * 25; // -100 as we are using dewey decimal system to differentiate matrix types
    int imgWidth = m_origImg.getWidth();
    int imgHeight = m_origImg.getHeight();

	//std::cout << startIndex << std::endl;
        
    for(int y = 0; y < imgHeight; y++) {
        for(int x = 0; x < imgWidth; x++) {
			sum.set(0.0f, 0.0f, 0.0f);
            
            //go through kernel 3x3 = 9 length
			for (int k = startIndex; k < startIndex + 25; k++) {

				//std::cout << k << std::endl;

				//check if we are trying to access an image coordinate out of bounds. Extend edges if so.
				//note that we need k here to start at 0 so we use modulo (%) to get the integer remainder of k / 9
				neighbourX = x + Constants::CONVOLUTION_5X5_KERNAL_CONVERT_X[k % 25];
				if (neighbourX < 0) {
					neighbourX = 0;
				}
				else if (neighbourX > imgWidth - 1) {
					neighbourX = imgWidth - 1;
				}

				neighbourY = y + Constants::CONVOLUTION_5X5_KERNAL_CONVERT_Y[k % 25];
				if (neighbourY < 0) {
					neighbourY = 0;
				}
				else if (neighbourY > imgHeight - 1) {
					neighbourY = imgHeight - 1;
				}
                
                //find out which 2D coordinate of image this k belongs to
                tempCol = m_origImg.getColor(neighbourX, neighbourY);
                
                //sum up kernel factors
				sum.x += tempCol.r * Constants::CONVOLUTION_MATS_5X5[k];
				sum.y += tempCol.g * Constants::CONVOLUTION_MATS_5X5[k];
				sum.z += tempCol.b * Constants::CONVOLUTION_MATS_5X5[k];
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
    if (m_eyeDropperActive) {
        // Ensure click is within the image bounds
        if (x >= 0 && x < m_edittedImg.getWidth() && y >= 0 && y < m_edittedImg.getHeight()) {
            m_eyeDropperColor = m_edittedImg.getColor(x, y);

            m_eyeDropperActive = false;
        }
    }
}

void ofApp::mouseDragged(int x, int y, int button) {
    
}
