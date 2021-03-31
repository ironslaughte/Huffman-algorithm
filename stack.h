#pragma once
#include "Elem.h"
class Stack {
public:
    Stack();
    Node* Top();
    Node* Pop();
    void Pop_Front();
    void Clear();
    void Push(Node* node);
    size_t GetSize();
    bool IsEmpty();
    char& operator[] (size_t index);

private:
    size_t Size;
    Elem* head;
};



Stack::Stack() {
    Size = 0;
    head = nullptr;
}

Node* Stack::Top() {
    return head->node;
}

Node* Stack::Pop() {
    Node* data = head->node;
    Pop_Front();
    return data;
}
void Stack::Pop_Front()
{    
    Elem* tmp = head;
    head = head->pnext;
    delete tmp;
    Size--;
}

void Stack::Push(Node* node) {
    head = new Elem(node, head);
    Size++;
}
void Stack::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}



size_t Stack::GetSize()
{
    return Size;
}


char& Stack::operator[](size_t index)
{
    int count = 0;
    Elem* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->node->sym;
        } cur = cur->pnext;
        count++;
    }
}


bool Stack::IsEmpty() {

    return Size > 0;
}
