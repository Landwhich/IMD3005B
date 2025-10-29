#pragma once

#include "ofMain.h"

namespace Constants {
    static const int WINDOW_WIDTH = 1280;
    static const int WINDOW_HEIGHT = 720;
    static const int FRAMERATE = 60;

    // static const std::string IMG_PATH = "happyTurtle.avif";
    static const std::string IMG_PATHS[3] = {
        "JupiterFromJunoSmall.jpg",
        "EarthFromSpace.png",
        "MarsFromSpace.png",
    };

        enum CONVOLUTION_MAT_TYPE {
        SHARPEN             = 0,
        EDGE_DETECTION_V    = 1,
        EDGE_DETECTION_H    = 2,
		EMBOSS			    = 3,
        BOX_BLUR            = 4,
        EDGE_ENHANCE        = 5,
        GAUSSIAN_BLUR       = 100,
        BOX_BLUR_5X5        = 101,
        SHARPEN_5X5         = 102,
        EDGE_DETECTION_5X5  = 103,
        EMBOSS_5X5          = 104
    };

	//https://en.wikipedia.org/wiki/Kernel_(image_processing), https://docs.gimp.org/2.8/en/plug-in-convmatrix.html
    static const float CONVOLUTION_MATS_3X3[] = {
        //sharpen 
        0.0f, -1.0f,  0.0f, 
        -1.0f,  5.0f, -1.0f, 
        0.0f, -1.0f,  0.0f,
        
        //edge detection vertical
        -1.0f, -1.0f, -1.0f, 
         0.0f,  0.0f,  0.0f, 
         1.0f,  1.0f,  1.0f, 

        //edge detection Horizontal
        -1.0f, 0.0f, 1.0f, 
        -1.0f, 0.0f, 1.0f, 
        -1.0f, 0.0f, 1.0f, 

        //emboss
        -2.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  1.0f,
        0.0f,  1.0f,  2.0f,
        
        //box blur
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f, 
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,
        1.0f/9.0f, 1.0f/9.0f, 1.0f/9.0f,

        //Edge enhance
        0.0f, 0.0f, 0.0f,
        -1.0f, 2.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
    };

    static const float CONVOLUTION_MATS_5X5[] = {
		//Gaussian 5x5
        1.0f/256.0f, 4.0f/256.0f, 6.0f/256.0f, 4.0f/256.0f, 1.0f/256.0f, 
        4.0f/256.0f, 16.0f/256.0f, 24.0f/256.0f, 16.0f/256.0f, 4.0f/256.0f, 
        6.0f/256.0f, 24.0f/256.0f, 36.0f/256.0f, 24.0f/256.0f, 6.0f/256.0f, 
        4.0f/256.0f, 16.0f/256.0f, 24.0f/256.0f, 16.0f/256.0f, 4.0f/256.0f, 
        1.0f/256.0f, 4.0f/256.0f, 6.0f/256.0f, 4.0f/256.0f, 1.0f/256.0f, 

        // 5x5 box blur
        1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f,
        1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f,
        1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f,
        1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f,
        1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f, 1.0f/25.0f,

        // sharpen
        0,  -1,  -1,  -1,   0,
        -1,   2,  -4,   2,  -1,
        -1,  -4,  13,  -4,  -1,
        -1,   2,  -4,   2,  -1,
        0,  -1,  -1,  -1,   0,

        // edge detection
        -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,
        -1,  -1,  24,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,

        // emboss
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
	};

    //map 1D array to 2D array coordinate for 3x3s
    static const float CONVOLUTION_3X3_KERNAL_CONVERT_X[] = {	
        -1,  0,  1, 
        -1,  0,  1,
        -1,  0,  1	
    };

    static const float CONVOLUTION_3X3_KERNAL_CONVERT_Y[] = {	
        -1, -1, -1, 
        0,  0,  0,
        1,  1,  1	
    };

    //map 1D array to 2D array coordinate for 5x5s
    static const float CONVOLUTION_5X5_KERNAL_CONVERT_X[] = {	
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
        -2, -1,  0,  1,  2,
    };

    static const float CONVOLUTION_5X5_KERNAL_CONVERT_Y[] = {	
        -2, -2, -2, -2, -2,
        -1, -1, -1, -1, -1,
         0,  0,  0,  0,  0,
         1,  1,  1,  1,  1,
         2,  2,  2,  2,  2,
    };
}