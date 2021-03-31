#pragma once
#include "queue.h"
#include "stack.h"
#include "iterator.h"


class bft_iterator : public Iterator {
private:
    Node* current;
    Queue NodeQueue;
public:
    bft_iterator(Node* start) {
        current = start;
        if (current != nullptr) {
            NodeQueue.Enqueue(current);
        }
        else {
            throw std::out_of_range("this tree is empty\n");
        }
    }

    Node* next() override {
        if (NodeQueue.GetSize() > 0) {
            current = NodeQueue.Dequeue();
            if (current->LeftNode != nullptr) {
                NodeQueue.Enqueue(current->LeftNode);
            }
            if (current->RightNode != nullptr) {
                NodeQueue.Enqueue(current->RightNode);
            }
            return current;
        }
        else {
            current = nullptr;
            //throw std::out_of_range("No more elements\n");
        }
    }

    bool has_next() override {
        return current != nullptr;
    }
};

class dft_iterator : public Iterator {
private:
    Node* current;
    Stack NodeStack;
    uint8_t flag = 1;
public:
    dft_iterator(Node* start) {
        current = start;
        if (current != nullptr) {
            NodeStack.Push(current);
        }
        else {
            throw std::out_of_range("this tree is empty\n");
        }
    }

    Node* next() override {
            if (flag) { // Небольшой костыль, чтобы вернуть первым элементом корень дерева.
                flag = 0;
                return NodeStack.Pop();
            }
            if (current->RightNode != nullptr) {
                NodeStack.Push(current->RightNode);
            }
            if (current->LeftNode != nullptr) {
                current = current->LeftNode;
            }
            else if (NodeStack.IsEmpty()) {
                current = NodeStack.Pop();
            }
            else {
                current = nullptr;
                //throw std::out_of_range("No more elements\n");
            }
            return current;
    }

    bool has_next() override {
        return current != nullptr;
    }

};


class BST {
private:
    Node* root;
public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear_tree(root);
    }

    BST(Node* new_root) {
        root = new_root;
    }

    void insert(int& weight,char sym);
    bool contains(char& sym);
    void remove(char& sym);
    void clear_tree(Node* cur);
    
    Iterator* create_bft_iterator();
    Iterator* create_dft_iterator();
    
};

Iterator* BST::create_bft_iterator() {
    return new bft_iterator(root);
}

Iterator* BST::create_dft_iterator() {
    return new dft_iterator(root);
}

void BST::clear_tree(Node* cur) {
    if (cur) {
        clear_tree(cur->LeftNode);
        clear_tree(cur->RightNode);
        delete cur;
    }
}

void BST::insert(int& weight, char sym) {
    if (root == nullptr) {
        root = new Node(weight,sym);
    }
    else {
        Node* cur = root;
        while (true) {
            if (sym <= cur->sym) {
                if (cur->LeftNode != nullptr) {
                    cur = cur->LeftNode;
                }
                else {
                    cur->LeftNode = new Node(weight,sym,nullptr,nullptr,cur);
                    break;
                }
            }
            else {
                if (cur->RightNode != nullptr) {
                    cur = cur->RightNode;
                }
                else {
                    cur->RightNode = new Node(weight, sym, nullptr, nullptr, cur);
                    break;
                }
            }

        }
    }
}

bool BST::contains(char& sym) {
    Node* cur = root;
    while (sym != cur->sym) {
        if (sym < cur->sym) {
            if (cur->LeftNode != nullptr) {
                cur = cur->LeftNode;
            }
            else {
                return false;
            }
        }
        else {
            if (cur->RightNode != nullptr) {
                cur = cur->RightNode;
            }
            else {
                return false;
            }
        }
    } return true;
}

void BST::remove(char& sym) {
    if (!contains(sym)) {
        throw std::invalid_argument("the element to delete is not in the tree\n");
    }
    else {
        Node* cur = root;
        Node* prev = nullptr;
        while (sym != cur->sym) {
            if (sym < cur->sym) {
                prev = cur;
                cur = cur->LeftNode;
            }
            else {
                prev = cur;
                cur = cur->RightNode;
            }
        }

        if (cur->LeftNode == nullptr && cur->RightNode == nullptr) {
            if (prev->LeftNode->sym == cur->sym) {
                prev->LeftNode = nullptr;              
            }
            else {
                prev->RightNode = nullptr;
            }

            delete cur;
        }
        else if (cur->LeftNode != nullptr && cur->RightNode != nullptr) {
            Node* tmp;
            if (cur->RightNode->LeftNode != nullptr) {
                tmp = cur->RightNode->LeftNode;
                cur->weight = tmp->weight;
                cur->sym = tmp->sym;
                cur->RightNode->LeftNode = nullptr;
            }
            else {
                tmp = cur->RightNode;
                cur->weight = tmp->weight;
                cur->sym = tmp->sym;
                Node* new_Node = new Node(tmp->RightNode->weight, tmp->RightNode->sym, tmp->RightNode->LeftNode, tmp->RightNode->RightNode);
                cur->RightNode = new_Node;
            }
            delete tmp;
        }
        else {
            if (cur->LeftNode != nullptr) {
                cur->weight = cur->LeftNode->weight;
                cur->sym = cur->LeftNode->sym;
                delete cur->LeftNode;
                cur->LeftNode = nullptr;
            }
            else {
                cur->weight = cur->RightNode->weight;
                cur->sym = cur->RightNode->sym;
                delete cur->RightNode;
                cur->RightNode = nullptr;
            }
        }

    }
}