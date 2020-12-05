#pragma once

template <typename Type>
class BidirectionalList {
public:
    BidirectionalList();                                 //Default constructor
    BidirectionalList(BidirectionalList<Type> & bdList); //Copy constructor
    BidirectionalList(int num);                          //Converting constructor

    void PushFront(Type value);
    void PushBack(value);
    void PopFront();
    void PopBack();
    Type Front();
    Type Back();
    bool Find(Type key);
    bool Empty();
    void Erase(Type key);
    void AddBefore(Node * pNode, Type value);
    void AddAfter(Node * pNode, Type value);

    ~BidirectionalList();
private:
    struct Node {
        Type _value;
        Type * _next;
        Type * _previous;
    };
    Node * _head;
    Node * _tail;
};
