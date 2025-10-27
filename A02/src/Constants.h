#pragma once

#include "ofMain.h"

namespace Constants {
    static const int WINDOW_WIDTH = 1280;
    static const int WINDOW_HEIGHT = 720;
    static const int FRAMERATE = 60;

    // static const std::string IMG_PATH = "happyTurtle.avif";
    static const std::string IMG_PATH = "JupiterFromJunoSmall.jpg";

        enum CONVOLUTION_MAT_TYPE {
        SHARPEN         = 0,
        EDGE_DETECTION  = 1,
		EMBOSS			= 2,
        BOX_BLUR        = 3,
    };

	//https://en.wikipedia.org/wiki/Kernel_(image_processing), https://docs.gimp.org/2.8/en/plug-in-convmatrix.html
    static const float CONVOLUTION_MATS_3X3[] = {
        //sharpen 
        0.0f, -1.0f,  0.0f, 
        -1.0f,  5.0f, -1.0f, 
        0.0f, -1.0f,  0.0f,
        
        //edge detection
        -1.0f, -1.0f, -1.0f, 
        -1.0f,  8.0f, -1.0f, 
        -1.0f, -1.0f, -1.0f,

        //emboss
        -2.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  2.0f,
        
        //box blur
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,
    };

    //a way to convert between 1D array and 2D array coordinates
    static const float CONVOLUTION_KERNAL_CONVERT_X[] = {	
        -1,  0,  1, 
        -1,  0,  1,
        -1,  0,  1	
    };

    static const float CONVOLUTION_KERNAL_CONVERT_Y[] = {	
        -1, -1, -1, 
        0,  0,  0,
        1,  1,  1	
    };
}