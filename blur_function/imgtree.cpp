/**
 * @file imgtree.cpp
 * @description implementation of ImgTree class used for storing image data
 *              CPSC 221 2023S PA3
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

#include "imgtree.h"
#include <cfloat>

/* ImgTree constructor */
ImgTree::ImgTree(const PNG& imIn){ 
    Stats s(imIn);

    width = imIn.width();
    height = imIn.height();

    root = BuildTree(s, make_pair<unsigned int,unsigned int>(0,0), make_pair<unsigned int, unsigned int>(width - 1, height - 1));
}   

/* BuildTree helper for ImgTree constructor */
Node* ImgTree::BuildTree(Stats& s, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr) {
	// replace the stub below with your own implementation
	Node* newNode = new Node(ul, lr, s.GetAvg(ul, lr));

    unsigned int width = lr.first - ul.first + 1;
    unsigned int height = lr.second - ul.second + 1;

    if (width == 1 && height == 1) {
        newNode->LT = nullptr;
        newNode->RB = nullptr;
        return newNode;
    }

    double minimum = DBL_MAX;
    unsigned int split = 0;

    if (width >= height) { // horizontally
        for (unsigned int i = ul.first; i < lr.first; i++) {
            double first = s.Entropy(ul, make_pair(i, lr.second)) * (i - ul.first + 1) / width;
            double second = s.Entropy(make_pair(i + 1, ul.second), lr) * (lr.first - i) / width;
            if (first + second < minimum) {
                minimum = first + second;
                split = i;
            }
        }

        newNode->LT = BuildTree(s, ul, make_pair(split, lr.second));
        newNode->RB = BuildTree(s, make_pair(split + 1, ul.second), lr);
    } else { // vertically
        for (unsigned int i = ul.second; i < lr.second; i++) {
            double first = s.Entropy(ul, make_pair(lr.first, i)) * (i - ul.second + 1) / height;
            double second = s.Entropy(make_pair(ul.first, i + 1), lr) * (lr.second - i) / height;
            if (first + second < minimum) {
                minimum = first + second;
                split = i;
            }
        }

        newNode->LT = BuildTree(s, ul, make_pair(lr.first, split));
        newNode->RB = BuildTree(s, make_pair(ul.first, split + 1), lr);
    }

    return newNode;

}

/* Render your ImgTree into a png */
PNG ImgTree::Render() const{
	// replace the stub below with your own implementation
	PNG img(width, height);
    RenderHelper(root, img);
    return img;
}

/* Prune function modifies tree by cutting off
 * subtrees whose leaves are all within tol of 
 * the average pixel value contained in the root
 * of the subtree
 */
void ImgTree::Prune(double tol){
	// complete your implementation below
    PruneHelper(root, tol);
}

/* Modifies node contents so that the rendered tree
 * will appear to be flipped horizontally across
 * a vertical axis
 */
void ImgTree::FlipHorizontal() {
	// complete your implementation below
    FlipHelper(root);
    
}

/* helper function for destructor and op= */
/* frees dynamic memory associated w the ImgTree */
void ImgTree::Clear() {
	// complete your implementation below
    ClearHelper(root);
    root = nullptr;
}

/* helper function for copy constructor and op= */
void ImgTree::Copy(const ImgTree& orig){
	// complete your implementation below
    width = orig.width;
    height = orig.height;
    root = CopyHelper(orig.root);
}

/**
 * Add your private ImgTree function implementations below
 */

void ImgTree::RenderHelper(Node* currNode, PNG& img) const {
    if (currNode == nullptr) {
        return;
    }
    if (currNode->LT == nullptr && currNode->RB == nullptr) {
        for (unsigned int x = currNode->upLeft.first; x <= currNode->lowRight.first; x++) {
            for (unsigned int y = currNode->upLeft.second; y <= currNode->lowRight.second; y++) {
                *img.getPixel(x, y) = currNode->avg;
            }
        }
    }
    else {
        RenderHelper(currNode->LT, img);
        RenderHelper(currNode->RB, img);
    }
}

void ImgTree::ClearHelper(Node* currNode) {
    if (currNode == nullptr) {
        return;
    }
    ClearHelper(currNode->LT);
    ClearHelper(currNode->RB);
    delete currNode;
}

Node* ImgTree::CopyHelper(const Node* currNode) {
    if (currNode == NULL) {
        return NULL;
    }
    Node* newNode = new Node(currNode->upLeft, currNode->lowRight, currNode->avg);
    newNode->LT = CopyHelper(currNode->LT);
    newNode->RB = CopyHelper(currNode->RB);
    return newNode;
}

void ImgTree::FlipHelper(Node* curr) {
    if (curr == nullptr) {
        return;
    }


    pair<unsigned int, unsigned int> begin = curr->upLeft;
    pair<unsigned int, unsigned int> end = curr->lowRight;


    curr->upLeft = make_pair(width - end.first - 1, begin.second);
    curr->lowRight = make_pair(width - begin.first - 1, end.second);


    if (curr->lowRight.second - curr->upLeft.second < curr->lowRight.first - curr->upLeft.first) {
        Node* temp = curr->LT;
        curr->LT = curr->RB;
        curr->RB = temp;
        temp = nullptr;
  
    }

    FlipHelper(curr->LT);
    FlipHelper(curr->RB);

}



bool ImgTree::Tolerable(Node* curr, HSLAPixel pixel, double tol) {
    if((curr->lowRight.second - curr->upLeft.second == 0) &&(curr->lowRight.first - curr->upLeft.first == 0)) {
        return (pixel.distanceTo(curr->avg) <= tol);
    }

    return (Tolerable(curr->LT, pixel, tol) && Tolerable(curr->RB, pixel, tol));
}

void ImgTree::PruneHelper(Node* &root, double tol) {
    if (Tolerable(root, root->avg, tol)) {
        Erase(root->LT);
        Erase(root->RB);
    } else {
        PruneHelper(root->LT, tol);
        PruneHelper(root->RB, tol);
    }
    
}

void ImgTree::Erase(Node*& root) {
    if (root == nullptr) {
        return;
    }

    Erase(root->LT);
    Erase(root->RB);
    delete(root);
    root = nullptr;
}