#pragma once
#include<bitset>

class Encoded_List {
public:
    Encoded_List();

    void Pop_Front();
    void Clear();
    void Push_back(uint8_t bit);
    void Push_front(uint8_t bit);
    void Pop_back(); 
    void Print_to_console();
    size_t GetSize();
    bool IsEmpty();
    uint8_t& operator[] (size_t index);
    void Remove(size_t index);
    void SetSym(char sym);
    char GetSym();
private:

    class Encoded_Node {
    public:
        Encoded_Node* pnext;
        uint8_t bit;
        Encoded_Node(uint8_t bit, Encoded_Node* pNext = nullptr) {
            this->bit = bit;
            this->pnext = pNext;
        }
    };
    size_t Size;
    Encoded_Node* head;    
    char sym; // the character that is encoded
};

Encoded_List::Encoded_List() {
    Size = 0;
    head = nullptr;

}

void Encoded_List::SetSym(char sym) {
    this->sym = sym;
}

char Encoded_List::GetSym() {
    return this->sym;
}

void Encoded_List::Pop_back() {
    Encoded_Node* cur = head;
    while (cur->pnext != nullptr) {
        cur = cur->pnext;
    }
    delete cur;
    Size--;
}

void Encoded_List::Pop_Front()
{
    Encoded_Node* tmp = head;
    head = head->pnext;
    delete tmp;
    Size--;
}

void Encoded_List::Push_front(uint8_t bit) {
    head = new Encoded_Node(bit, head);
    Size++;

}
void Encoded_List::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}

void Encoded_List::Push_back(uint8_t bit)
{
    if (head == nullptr) {
        head = new Encoded_Node(bit);
    }
    else {
        Encoded_Node* cur = head;
        while (cur->pnext != nullptr) {
            cur = cur->pnext;
        }
        cur->pnext = new Encoded_Node(bit);
    }
    Size++;
}

size_t Encoded_List::GetSize()
{
    return Size;
}



uint8_t& Encoded_List::operator[](size_t index)
{
    int count = 0;
    Encoded_Node* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->bit;
        } cur = cur->pnext;
        count++;
    }
}

void Encoded_List::Print_to_console() {
    Encoded_Node* cur = head;
    for (size_t i = 0; i < Size; i++) {
        std::cout << cur->bit << " ";
        cur = cur->pnext;
    }
    std::cout << "\n";
}

bool Encoded_List::IsEmpty() {

    return Size == 0;
}



void Encoded_List::Remove(size_t index) {
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
        Encoded_Node* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                Encoded_Node* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}