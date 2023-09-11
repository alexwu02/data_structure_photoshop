/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"
#include <cmath>

QuarterColorPicker::QuarterColorPicker(PNG& inputimg)
{
    // Complete your implementation below
    referenceimg = inputimg;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image.
 *
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the H/S/L/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 *
 * Since interpolation will be the exact average between exactly two pixels, then
 * the Hue channel should be averaged over the shortest arc between the two values.
 * e.g. The average of H_1 = 10 and H_2 = 320 is H_avg = 345 and NOT 165.
 * In the case of two diametric hues being averaged, e.g. 10 and 190, the average will
 * have the smaller value, i.e. 100 and NOT 280.
 * 
 * @pre referenceimg width and height are both even
 */
HSLAPixel QuarterColorPicker::operator()(PixelPoint p)
{

    int x = p.x * 2 % referenceimg.width();
    int y = p.y * 2 % referenceimg.height();

    HSLAPixel p1 = *(referenceimg.getPixel(x, y));
    HSLAPixel p2 = *(referenceimg.getPixel(x, y + 1));
    HSLAPixel p3 = *(referenceimg.getPixel(x + 1, y));
    HSLAPixel p4 = *(referenceimg.getPixel(x + 1, y + 1));

    HSLAPixel interpolatedPixel;

    interpolatedPixel.h = averageHue(averageHue(p1.h, p2.h), averageHue(p3.h, p4.h));
    interpolatedPixel.s = ((p1.s + p2.s)/2 + (p3.s + p4.s)/2)/2;
    interpolatedPixel.l = ((p1.l + p2.l)/2 + (p3.l + p4.l)/2)/2;
    interpolatedPixel.a = ((p1.a + p2.a)/2 + (p3.a + p4.a)/2)/2;

    return interpolatedPixel;

}

/**
 * Add your private QuarterColorPicker function implementations below
 */

double QuarterColorPicker::averageHue(double hue1, double hue2) {
    double diff = std::abs(hue1 - hue2);

    if (diff > 180.0) {
        if (hue1 > hue2)
            hue2 += 360.0;
        else
            hue1 += 360.0;
    }

    double avg = (hue1 + hue2) / 2.0;

    while (avg >= 360.0) {
        avg -= 360.0;
    }

    return avg;
}