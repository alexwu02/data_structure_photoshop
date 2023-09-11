/**
 * @file negativeBorderColorPicker_private.h
 * @description student declarations of private functions
 *              for NegativeBorderColorPicker, CPSC 221 2023S PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below

bool withinImage(int x, int y, unsigned int width, unsigned int height);

bool withinFill(int x, int y, PNG& img, double tol, PixelPoint source_px);