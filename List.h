#pragma once
#include "Elem.h"
class List {
public:
    List();
    void Pop_Front();
    void Clear();
    void Push_back(Node* node);
    void Push_front(Node* node);
    void Pop_back();
    void Insert(Node* s, size_t index);
    void Print_to_console();
    size_t GetSize();
    bool IsEmpty();
    int Contains(char sym);
    Node* operator[] (size_t index);
    void Remove(size_t index);
    void Sort();
private:
    size_t Size;
    Elem* head;
};

int List::Contains(char sym) {
    if (head == nullptr) {
        throw std::logic_error("List is empty\n");
    }
    Elem* cur = head;
    int index = 0;
    while (sym != cur->node->sym && cur->pnext != nullptr) {
        cur = cur->pnext;
        index++;
    }
    if (sym == cur->node->sym) return index;
    return -1;
}


List::List() {
    Size = 0;
    head = nullptr;
}


void List::Pop_back() {
    Elem* cur = head;
    while (cur->pnext != nullptr) {
        cur = cur->pnext;
    }
    delete cur;
    cur = nullptr;
    Size--;
}


void List::Pop_Front()
{
    Elem* cur = head;
    head = head->pnext;
    delete cur;
    Size--;
}


void List::Push_front(Node* node) {
    head = new Elem(node, head);
    Size++;
}


void List::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}




void List::Push_back(Node* node)
{
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


size_t List::GetSize()
{
    return Size;
}


void List::Insert(Node* s, size_t index)
{
    if (index > Size + 1) {
        throw std::out_of_range("Wrong index\n");
    }
    else if (index == Size) {
        Push_back(s);
    }
    else if (index == 0) {
        Push_front(s);
    }
    else {
        Elem* prev = head;
        for (int i = 0; i < (index - 1); i++) {
            prev = prev->pnext;
        }
        Elem* newNode = new Elem(s, prev->pnext);
        prev->pnext = newNode;
        Size++;
    }

}


Node* List::operator[](size_t index)
{
    int count = 0;
    Elem* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->node;
        } cur = cur->pnext;
        count++;
    }
}


void List::Print_to_console() {
    Elem* cur = head;
    for (size_t i = 0; i < Size; i++) {
        std::cout << cur->node << " ";
        cur = cur->pnext;
    }
    std::cout << "\n";
}


bool List::IsEmpty() {

    return Size == 0;
}




void List::Remove(size_t index) {
    if (index > Size - 1) {
        throw std::out_of_range("Wrong index\n");
    }
    if (index == 0) {
        Pop_Front();
    }
    else if (index == Size - 1) {
        Pop_back();
    }
    else {
        Elem* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                Elem* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}


// Quick sort block
int partition(List& list, int low, int high)
{
    Node* pivot = new Node(list[high]->weight,list[high]->sym, list[high]->LeftNode, list[high]->RightNode);
    int i = (low - 1); // index of smaller element 
    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot 
        if (list[j]->weight < pivot->weight)
        {
            i++;
            // swap list[i] and list[j] 

            Node* tmp = new Node(list[j]->weight, list[j]->sym, list[j]->LeftNode, list[j]->RightNode);
            *list[j] = list[i];
            *list[i] = *tmp;
        }
    }

    // swap list[i+1] and list[high] (or pivot) 
    Node* tmp = new Node(list[high]->weight, list[high]->sym, list[high]->LeftNode, list[high]->RightNode);
    //Node* tmp = list[high];
    *list[high] = list[i+1];
    *list[i+1] = tmp;
    return i + 1;
}


/* The main function that implements QuickSort()
  list[] --> list to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void Qsort(List& list, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, list[pi] is
          now at right place */
        int pi = partition(list, low, high);

        // Recursively sort elements before 
        // partition and after partition 
        Qsort(list, low, pi - 1);
        Qsort(list, pi + 1, high);
    }
}

void List::Sort() {
    List sorted_list = *this;
    Qsort(sorted_list, 0, this->Size-1);
    *this = sorted_list;
}
