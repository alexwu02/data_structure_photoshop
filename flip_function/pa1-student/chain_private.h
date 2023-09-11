/**
 * File: chain_private.h
 * Description: student declarations of private chain functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 * 
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

// begin your declarations below


void ReverseNodesBetween(Node* start, Node* end) {
    if (start == nullptr || end == nullptr || start == end) {
        return;
    }

    Node* startPrev = start->prev;
    Node* endNext = end->next;

    Node* curr = start;
    Node* prev = nullptr;
    while (curr != end) {
        Node* next = curr->next;
        curr->next = curr->prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }

    start->next = endNext;
    end->next = prev;
    end->prev = startPrev;

    if (startPrev != nullptr) {
        startPrev->next = end;
    }
    if (endNext != nullptr) {
        endNext->prev = start;
    }
}





