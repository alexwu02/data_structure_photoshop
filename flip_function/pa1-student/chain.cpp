/**
 * File: chain.cpp
 * Description: student implementation for Chain functions 
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include <math.h>
#include "chain.h"
#include <algorithm> 

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
 */
Chain::Chain(PNG& img, unsigned int dimension) {
    unsigned int imgHeight = img.height();
    unsigned int imgWidth = img.width();

    if (imgWidth == 0 || imgHeight == 0 || imgWidth % dimension != 0 || imgHeight % dimension != 0) {
        throw std::invalid_argument("Invalid Argument");
    }

    unsigned int nodeY = imgHeight / dimension;
    unsigned int nodeX = imgWidth / dimension;

    NW = nullptr;
    SE = nullptr;
    length_ = 0;

    Node* prevNode = nullptr;

    for (unsigned int y = 0; y < nodeY; y++) {
        for (unsigned int x = 0; x < nodeX; x++) {
            unsigned int strtX = x * dimension;
            unsigned int strtY = y * dimension;

            Block block;
            block.Build(img, strtX, strtY, dimension);

            Node* newNode = new Node(block);
            newNode->prev = prevNode;

            if (prevNode != nullptr) {
                prevNode->next = newNode;
            } else {
                NW = newNode;
            }

            prevNode = newNode;
            SE = newNode;
            length_++;
        }
    }
}





/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 */
PNG Chain::Render(unsigned int cols) {
    unsigned int totalLength = Length();
    unsigned int numRows = (totalLength + cols - 1) / cols;
    unsigned int nodeDimension = NW->data.Dimension();
    unsigned int imageWidth = cols * nodeDimension;
    unsigned int imageHeight = numRows * nodeDimension;

    PNG image(imageWidth, imageHeight);

    Node* currentNode = NW;

    for (unsigned int y = 0; y < numRows; y++) {
        for (unsigned int x = 0; x < cols; x++) {
            if (currentNode != nullptr) {
                unsigned int nodeX = x * nodeDimension;
                unsigned int nodeY = y * nodeDimension;
                currentNode->data.Render(image, nodeX, nodeY);
                currentNode = currentNode->next;
            }
        }
    }

    return image;
}

/**
 * Inserts a new Node containing ndata at the back of the Chain
 */
void Chain::InsertBack(const Block& ndata) {
	Node* newNode = new Node(ndata);

	if (NW == nullptr) {
		NW = newNode; 
		SE = newNode;
	} else {
		newNode->prev = SE;
        newNode->next = nullptr;
		SE->next = newNode;
		SE = newNode;
	}

	length_++;
}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
 */

void Chain::Reverse() {
	if (length_ == 1 || IsEmpty()) {
    return;
    }

    Node* temp = NW;
    NW = SE;
    SE = temp;

    Node* curr = NW;

    while (curr != nullptr) {
        Node* tempNext = curr->next;
        curr->next = curr->prev;
        curr->prev = tempNext;
        curr = curr->next; 
    }
}





/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */

void Chain::FlipHorizontal(unsigned int cols) {
    if (cols <= 1 || length_ % cols != 0) {
        return;
    }

    unsigned int rows = length_ / cols;

    Node* currNode = NW;

    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            currNode->data.FlipHorizontal();
            currNode = currNode->next;
        }
    }

    currNode = NW;

    for (unsigned int row = 0; row < rows; row++) {
        Node* rowStart = currNode;
        Node* rowEnd = currNode;

        for (unsigned int col = 0; col < cols; col++) {
            if (col == 0) {
                rowStart = currNode;
            }

            if (col == (cols - 1) && (row == 0)) {
                NW = currNode;
            }

            if ((col == 0) && row == (rows - 1)) {
                SE = currNode;
            }

            if (col == (cols - 1)) {
                rowEnd = currNode;
            }

            currNode = currNode->next;
        }

        ReverseNodesBetween(rowStart, rowEnd);
    }

    NW->prev = nullptr;
    SE->next = nullptr;
}

/**
 * Rearranges the Node structure and internal pixel data to be rotated counter-clockwise.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, rotating with 3 columns (2 rows):
 *            ^     ^     ^
 *      NW -> A <-> B <-> C <->
 *            ^     ^     ^
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 2 columns (3 rows):
 * 
 *      NW -> <C <-> <F <->
 *            <B <-> <E <->
 *            <A <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */

void Chain::RotateCCW(unsigned int cols) {
    if (cols <= 1 || NW == nullptr) {
        return;
    }

    unsigned int rows = length_ / cols;
    unsigned int groupSize = cols - 1;

    Node* curr = NW;

    for (unsigned int row = 0; row < rows; row++) {
        Node* first = curr;
        for (unsigned int col = 0; col < row; col++) {
            if (first != nullptr) {
                first = first->next;
            }
        }
        Node* current = first;

        for (unsigned int col = 0; col < groupSize; col++) {
            if (current != nullptr) {
                current->data.RotateCCW();
                current = current->next;
            }
        }

        curr = first->next;
    }
}






/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
 */
void Chain::Clear() {
	Node* curr = NW;
    while (curr != nullptr) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    NW = nullptr;
    SE = nullptr;
    length_ = 0;
}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
 */
void Chain::Copy(const Chain& other) {
    if (other.NW == nullptr) {
        NW = nullptr;
        SE = nullptr;
        length_ = 0;
        return;
    }

    NW = new Node(other.NW->data);
    NW->prev = nullptr;

    Node* currentOther = other.NW->next;
    Node* prev = NW;
    Node* current = NW;

    while (currentOther != nullptr) {
        Node* newNode = new Node(currentOther->data);

        newNode->prev = current;
        current->next = newNode;

        prev = current;
        current = newNode;
        currentOther = currentOther->next;
    }

    SE = current;
    length_ = other.length_;
    current->next = nullptr;
}


/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
 */


