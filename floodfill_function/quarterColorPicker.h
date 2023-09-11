/**
 * @file quarterColorPicker.h
 * Definition of a quarter color picker.
 *
 */
#ifndef _QUARTERCOLORPICKER_H_
#define _QUARTERCOLORPICKER_H_

#include "colorPicker.h"

 /**
  * QuarterColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate using a quartered image pattern. You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  */
class QuarterColorPicker : public ColorPicker
{
public:
    /**
     * Constructs a new QuarterColorPicker.
     *
     * @param inputimg The original image to be filled
     * @pre inputimg width and height are both even
     */
    QuarterColorPicker(PNG& inputimg);

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
    virtual HSLAPixel operator()(PixelPoint p);

private:

    PNG referenceimg; // original image used in the flood fill algorithm

    /**
     * @todo Define any additional private member variables or helper
     *	functions in quarterColorPicker_private.h as you see fit.
     */
    #include "quarterColorPicker_private.h"
};

#endif
