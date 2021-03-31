#pragma once

class Node {
public:
    Node* LeftNode; // дочерний левый узел
    Node* RightNode; // дочерний правый узел
    Node* Parent;
    int weight;  // вес узла
    char sym; // значение элемента в узле
    Node(int new_weight, char new_sym, Node* Left = nullptr, Node* Right = nullptr, Node* parent = nullptr) {
        weight = new_weight;
        sym = new_sym;
        LeftNode = Left;
        RightNode = Right;
        Parent = parent;        
    }

    Node() {
        LeftNode = nullptr;
        RightNode = nullptr;
        Parent = nullptr;
    }
    Node& operator=(Node* rhs) {
        this->LeftNode = rhs->LeftNode;
        this->RightNode = rhs->RightNode;
        this->sym = rhs->sym;
        this->weight = rhs->weight;
        return *this;
    }
    bool IsLeaf() {
        return (this->LeftNode == nullptr) && (this->RightNode == nullptr);
    }
};


