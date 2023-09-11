/**
 * @file imgtree_private.h
 * @description student declarations of private functions
 *              for ImgTree, CPSC 221 2023S PA3
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below
void RenderHelper(Node* currNode, PNG& img) const;
void ClearHelper(Node* currNode);
Node* CopyHelper(const Node* currNode);
void FlipHelper(Node* currNode);
void FlipHelper(Node* currNode, PNG& img);
void Flipper(Node* curr);