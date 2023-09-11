/**
 * @file negativeBorderColorPicker.h
 * Definition of a negative border color picker.
 *
 */
#ifndef _NEGATIVEBORDERCOLORPICKER_H_
#define _NEGATIVEBORDERCOLORPICKER_H_

#include "colorPicker.h"

 /**
  * NegativeBorderColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate if it is on the border of a fill region. You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  */
class NegativeBorderColorPicker : public ColorPicker
{
public:
    /**
     * Constructs a new NegativeBorderColorPicker.
     *
     * @param inputimg The original image to be filled
     * @param width The width of the coloured border, in pixels
     * @param tol The tolerance of the colour difference for determining whether
     *            a pixel will be inside or outside of the fill region
     */
    NegativeBorderColorPicker(PNG& inputimg, PixelPoint src_px, unsigned int width, double tol);

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
    virtual HSLAPixel operator()(PixelPoint p);

private:

    PNG referenceimg; // original image used in the flood fill algorithm
    PixelPoint source_px; // starting point of the flood fill in the original image
    unsigned int borderwidth; // width of the fill region's border to be coloured, in pixels
    double tolerance; // colour difference threshold for determining inside/outside fill region

    /**
     * @todo Define any additional private member variables or helper
     *	functions in quarterColorPicker_private.h as you see fit.
     */
    #include "negativeBorderColorPicker_private.h"
};

#endif
