#pragma once

template <typename Type>
class BidirectionalList {
private:
    struct Node {
        Type _value;
        Node * _next;
        Node * _previous;
    };
    Node * _head;
    Node * _tail;
public:
    class Iterator {
    public:
        Iterator(Node * node);
        bool operator == (const Iterator& other) const;
        bool operator != (const Iterator& other) const;
        Type & operator * () const;
        void operator ++ ();
    private:
        Node * m_node;
    };

    BidirectionalList();                                 //Default constructor
    BidirectionalList(BidirectionalList<Type> & bdList); //Copy constructor
    explicit BidirectionalList(int num);                          //Converting constructor

    void AddBefore(Iterator it, Type value);
    void AddAfter(Iterator it, Type value);
    void PushFront(Type value);
    void PushBack(Type value);
    Type PopFront();
    Type PopBack();
    void Erase(Iterator key);
    Type Front();
    Type Back();
    bool Find(Type key);
    bool Empty();

    Iterator begin() const;
    Iterator end() const;

    ~BidirectionalList();
};
