/**
 * @file HSLAPixel.h
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#pragma once

#include <iostream>
#include <sstream>

namespace cs225 {
    class HSLAPixel
    {
        public:
        /**
         * Let h denote the hue of the pixel, storing the value of the hue in degrees as a double from [0, 360).
         * Let s denote the saturation of the pixel, storing the value as a double from [0, 1].
         * Let l denote the luminance of the pixel, storing the value as a double from [0, 1].
         * Let a denote the alpha channel, how transparent the pixel is, storing the value as a double from [0, 1].
         */ 
        double h; // 0 to 360
        double s; //0 to 1
        double l; //0 to 1
        double a; //0 to 1
        HSLAPixel();
        HSLAPixel(double hue, double saturation,double luminance);
        HSLAPixel(double hue, double saturation,double luminance, double aplha);
    };
}
