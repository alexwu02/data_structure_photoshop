/**
 * @file negativeBorderColorPicker.cpp
 * @description Implements the NegativeBorderColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "negativeBorderColorPicker.h"
#include <math.h>

NegativeBorderColorPicker::NegativeBorderColorPicker(PNG &inputimg, PixelPoint src_px, unsigned int width, double tol) 
{
    referenceimg = inputimg;
    source_px = src_px;
    borderwidth = width;
    tolerance = tol;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Leaves a pixel unchanged if it is not on the border of a fill region
 *
 * If a pixel is on the border of a fill region, change it to the "negative"
 * of the original colour value in the Hue and Luminance channels.
 * Saturation and Alpha should remain unchanged.
 * Based on your understanding of HSL colour space from Lab_intro,
 * think about what would be an appropriate "negative" transformation for the
 * Hue and Luminance channels.
 *
 * Hint: a pixel is on the border of a fill region, if it is within "width"
 * pixels of a pixel which is NOT in the fill region!
 *
 * Also: the border of the image is considered to be a border of the fill region.
 */


HSLAPixel NegativeBorderColorPicker::operator()(PixelPoint p)
{
    int west = static_cast<int>(p.x) - borderwidth;
    int north = static_cast<int>(p.y) - borderwidth;
    int east = static_cast<int>(p.x) + borderwidth;
    int south = static_cast<int>(p.y) + borderwidth;

    if (p.x < static_cast<unsigned>(borderwidth) || p.y < static_cast<unsigned>(borderwidth) || p.x >= referenceimg.width() - borderwidth || p.y >= referenceimg.height() - borderwidth) {
        HSLAPixel pixel = *(referenceimg.getPixel(p.x, p.y));
        pixel.h = (static_cast<int>(pixel.h) + 180) % 360;
        pixel.l = 1.0 - pixel.l;
        return pixel;
    } else {
        for (int i = west; i <= east; i++) {
            for (int j = north; j <= south; j++) {
                int distance = ((static_cast<int>(p.x) - i) * (static_cast<int>(p.x) - i)) + ((static_cast<int>(p.y) - j) * (static_cast<int>(p.y) - j));
                if (distance <= (borderwidth * borderwidth)) {
                    if (referenceimg.getPixel(i, j)->distanceTo(source_px.color) > tolerance) {
                        HSLAPixel pixel = *(referenceimg.getPixel(p.x, p.y));
                        pixel.h = (static_cast<int>(pixel.h) + 180) % 360;
                        pixel.l = 1.0 - pixel.l;
                        return pixel;
                    }
                }
            }
        }
        return *(referenceimg.getPixel(p.x, p.y));
    }
}


// HSLAPixel NegativeBorderColorPicker::operator()(PixelPoint p)
// {
//     int west = (int)p.x - borderwidth;
//     int north = (int)p.y - borderwidth;
//     int east = (int)p.x + borderwidth;
//     int south = (int)p.y + borderwidth;

//     if (p.x < borderwidth || p.y < borderwidth || p.x >= referenceimg.width() - borderwidth || p.y >= referenceimg.height() - borderwidth) {
//         HSLAPixel pixel = *(referenceimg.getPixel(p.x, p.y));
//         // pixel.h = fmod(pixel.h + 180.0, 360.0);
//         pixel.h = (((int) pixel.h) + 180) % 360;
//         pixel.l = 1.0 - pixel.l;
//         return pixel;

//     } else {
//         for (int i = west; i <= east; i++) {
//             for (int j = north; j <= south; j++) {
//                 int distance = sqrt(((int) p.x-i) * ((int) p.x-i) + ((int) p.y-j) * ((int) p.y-j));
//                 if (distance <= borderwidth) {
//                     if (referenceimg.getPixel(i, j)->distanceTo(source_px.color) > tolerance) {
//                         HSLAPixel pixel = *(referenceimg.getPixel(p.x, p.y));
//                         pixel.h = fmod(pixel.h + 180.0, 360.0);
//                         pixel.l = 1.0 - pixel.l;
//                         return pixel;
//                     }
//                 }
//             }
//         }
//         return *(referenceimg.getPixel(p.x, p.y));
//     }
// }


/**
 * Add your private QuarterColorPicker function implementations below
 */

