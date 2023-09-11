/**
 * @file imageTileColorPicker.h
 * Definition of an image tiling color picker.
 *
 */
#ifndef _IMAGETILECOLORPICKER_H_
#define _IMAGETILECOLORPICKER_H_

#include "colorPicker.h"

 /**
  * ImageTileColorPicker: a functor that determines the color that should be
  * used given an x and y coordinate by tiling one image over the dimensions
  * of the target image, aligned to (0, 0). You can create
  * private helper functions inside this class, as well as local storage, if
  * necessary. Remember to overload a destructor if you need to.
  */
class ImageTileColorPicker : public ColorPicker
{
public:
    /**
     * Constructs a new ImageTileColorPicker.
     *
     * @param secondary_img The image to be tiled
     */
    ImageTileColorPicker(PNG& secondary_img);

    /**
     * Picks the color for pixel (x, y).
     *
     * The tile image should be tiled over the dimensions of the destination image,
     * aligned to (0, 0) in the destination image.
     *
     * The returned value will be the colour of the appropriate pixel in the tile image,
     * where it would be over the specified location in the destination image.
     */
    virtual HSLAPixel operator()(PixelPoint p);

private:

    PNG tileimg; // image to be tiled

    /**
     * @todo Define any additional private member variables or helper
     *	functions in imageTileColorPicker_private.h as you see fit.
     */
    #include "imageTileColorPicker_private.h"
};

#endif
