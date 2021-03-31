#pragma once
#include "Node.h"
class Elem {
public:
    Elem* pnext;
    Node* node;
    Elem(Node* new_node, Elem* pNext = nullptr) {
        node = new_node;
        pnext = pNext;
    }
};