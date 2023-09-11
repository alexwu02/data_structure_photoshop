/**
 * File: block.cpp
 * Description: student implementation for Block functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include "block.h"
#include <algorithm>


/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
 */
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	data.resize(dimension);
	
	for (unsigned int i = 0; i < dimension; i++) {
		data[i].resize(dimension);

		for (unsigned int j = 0; j < dimension; j++) {
			HSLAPixel * hslaPixel = img.getPixel(x + i, y + j);
			data[i][j] = *hslaPixel;
		}
	}

}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y) const {
    unsigned int blockDimension = Dimension();

    for (unsigned int i = 0; i < blockDimension; i++) {
        for (unsigned int j = 0; j < blockDimension; j++) {
            *img.getPixel(x + i, y + j) = data[i][j];
        }
    }
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
 */
void Block::FlipHorizontal() {
    unsigned int blockDimension = Dimension();

    for (unsigned int i = 0; i < blockDimension / 2; i++) {
        for (unsigned int j = 0; j < blockDimension; j++) {
            swap(data[i][j], data[blockDimension - 1 - i][j]);
        }
    } 
}

/**
 * Rotates the Block's pixel data 90 degrees counter-clockwise.
 */
void Block::RotateCCW() {
    unsigned int dimensions = Dimension();
    
	vector<vector<HSLAPixel>> rotate(dimensions, vector<HSLAPixel>(dimensions));

	for (unsigned int i = 0; i < dimensions; ++i) {
        for (unsigned int j = 0; j < dimensions; ++j) {
            rotate[j][dimensions - 1 - i] = data[i][j];
        }
    }
    data = move(rotate);
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	  return data.size();
}