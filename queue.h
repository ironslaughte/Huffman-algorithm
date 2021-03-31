#pragma once
#include "Elem.h"
class Queue {
public:
    Queue();


    void Pop_Front();
    void Clear();
    size_t GetSize();
    bool IsEmpty();
    char& operator[] (size_t index);
    Node* Dequeue();

    void Enqueue(Node* node) {
        if (head == nullptr) {
            head = new Elem(node);
        }
        else {
            Elem* cur = head;
            while (cur->pnext != nullptr) {
                cur = cur->pnext;
            }
            cur->pnext = new Elem(node);
        }
        Size++;
    }


    Node* Peek() {
        return head->node;
    }
private:
    size_t Size;
    Elem* head;
};

Queue::Queue() {
    Size = 0;
    head = nullptr;
}



void Queue::Pop_Front()
{
    Elem* tmp = head;
    head = head->pnext;
    delete tmp;
    Size--;
}

Node* Queue::Dequeue() {
    Node* data = head->node;
    Pop_Front();
    return data;
}

void Queue::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}



size_t Queue::GetSize()
{
    return Size;
}



char& Queue::operator[](size_t index)
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


bool Queue::IsEmpty() {

    return Size > 0;
}
