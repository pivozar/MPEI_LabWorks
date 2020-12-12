#pragma once
#include <stdexcept>
#include <iostream>

template <typename Type>
class BidirectionalList {
private:
    struct Node {
        Node(Type new_value, Node * prev, Node * next)
            : _value(new_value), _previous(prev), _next(next) {};
        Type _value;
        Node * _previous;
        Node * _next;
    };
    Node * _head;
    Node * _tail;
    unsigned int _size;
public:
    class Iterator {
    public:
        explicit Iterator(Node * node);
        bool operator == (const Iterator& other) const;
        bool operator != (const Iterator& other) const;
        const Type & operator * () const;
        Type & operator * ();
        void operator ++ ();
        friend BidirectionalList::Node * BidirectionalList::_get_node(Iterator it);
    private:
        Node * m_node;
    };

    BidirectionalList();                                 //Default constructor
    BidirectionalList(BidirectionalList<Type> & bdList); //Copy constructor
    explicit BidirectionalList(Type item);               //Converting constructor

    void AddBefore(Iterator it, Type value);
    void AddAfter(Iterator it, Type value);
    void PushFront(Type value);
    void PushBack(Type value);
    void Erase(Iterator key);
    Type PopFront();
    Type PopBack();
    Type Front();
    Type Back();
    Iterator Find(Type key);
    bool Empty();

    template<typename T>
    friend std::istream & operator >> (std::istream & stream, BidirectionalList<T> & list);
    template<typename T>
    friend std::ostream & operator << (std::ostream & stream, const BidirectionalList<T> & list);

    Iterator begin() const;
    Iterator end() const;

    unsigned int size() const;

    ~BidirectionalList();

private:
    Node * _get_node(Iterator it) { return it.m_node; }
    void _clear();
};

//-----------------------------------------------------------------------------
//Iterator member functions definition
template<typename Type>
BidirectionalList<Type>::Iterator::Iterator(BidirectionalList::Node *node) : m_node(node) {}

template<typename Type>
bool BidirectionalList<Type>::Iterator::operator==(const BidirectionalList::Iterator &other) const {
    return this == &other || m_node == other.m_node;
}

template<typename Type>
bool BidirectionalList<Type>::Iterator::operator!=(const BidirectionalList::Iterator &other) const {
    return !(*this == other);
}

template<typename Type>
const Type &BidirectionalList<Type>::Iterator::operator*() const {
    if (!m_node) {
        throw std::out_of_range("This is the end-pointer iterator!");
    }
    return m_node->_value;
}

template<typename Type>
Type &BidirectionalList<Type>::Iterator::operator*() {
    if (!m_node) {
        throw std::out_of_range("This is the end-pointer iterator!");
    }
    return m_node->_value;
}

template<typename Type>
void BidirectionalList<Type>::Iterator::operator++() {
    if (!m_node) {
        throw std::out_of_range("End of list reached!");
    }
    m_node = m_node->_next;
};

//-----------------------------------------------------------------------------
//BidirectionalList member functions definition

template<typename Type>
BidirectionalList<Type>::BidirectionalList()
    : _head(nullptr), _tail(nullptr), _size(0) {}

template<typename Type>
BidirectionalList<Type>::BidirectionalList(BidirectionalList<Type> &bdList)
    : _size(bdList.size()) {
    _head = new Node(*(bdList.begin()), nullptr, nullptr);
    Node * prev_node = _head;
    for (auto i = bdList.begin(); i != bdList.end(); ++i) {
        if (i == bdList.begin())
            continue;
        prev_node->_next = new Node(*i, prev_node, nullptr);
        prev_node = prev_node->_next;
    }
    _tail = prev_node;
}

template<typename Type>
BidirectionalList<Type>::BidirectionalList(Type item) : _size(1) {
    _head = new Node(item, nullptr, nullptr);
    _tail = _head;
}

template<typename Type>
void BidirectionalList<Type>::AddBefore(BidirectionalList::Iterator it, Type value) {
    if (it == end()) {
        throw std::invalid_argument("Cannot add before end-iterator!");
    }
    Node * cur_node = _get_node(it);
    Node * old_prev = cur_node->_previous;
    cur_node->_previous = new Node(value, old_prev, cur_node);
    if (cur_node == _head) {
        _head = cur_node->_previous;
    }
    else {
        old_prev->_next = cur_node->_previous;
    }
    _size++;
}

template<typename Type>
void BidirectionalList<Type>::AddAfter(Iterator it, Type value) {
    if (it == end()) {
        if (_tail) {
            it = Iterator(_tail);
        }
        else {
            _head = new Node(value, nullptr, nullptr);
            _tail = _head;
            _size++;
            return;
        }
    }
    Node * cur_node = _get_node(it);
    Node * old_next = cur_node->_next;
    cur_node->_next = new Node(value, cur_node, old_next);
    if (cur_node == _tail) {
        _tail = cur_node->_next;
    }
    else {
        old_next->_previous = cur_node->_next;
    }
    _size++;
}

template<typename Type>
void BidirectionalList<Type>::PushFront(Type value) {
    AddBefore(begin(), value);
}

template<typename Type>
void BidirectionalList<Type>::PushBack(Type value) {
    AddAfter(end(), value);
}

template<typename Type>
void BidirectionalList<Type>::Erase(BidirectionalList::Iterator key) {
    Node * to_delete = _get_node(key);
    if (to_delete != _head) {
        to_delete->_previous->_next = to_delete->_next;
    }
    else {
        _head = to_delete->_next;
    }
    if (to_delete != _tail) {
        to_delete->_next->_previous = to_delete->_previous;
    }
    else {
        _tail = to_delete->_previous;
    }
    delete to_delete;
    _size--;
}

template<typename Type>
Type BidirectionalList<Type>::PopFront() {
    Type res = _head->_value;
    Erase(begin());
    return res;
}

template<typename Type>
Type BidirectionalList<Type>::PopBack() {
    Type res = _tail->_value;
    Erase(Iterator(_tail));
    return res;
}

template<typename Type>
Type BidirectionalList<Type>::Front() {
    return _head->_value;
}

template<typename Type>
Type BidirectionalList<Type>::Back() {
    return _tail->_value;
}

template<typename Type>
typename BidirectionalList<Type>::Iterator BidirectionalList<Type>::Find(Type key) {
    for (auto i = begin(); i != end(); ++i) {
        if (key == *i) {
            return i;
        }
    }
    return Iterator(nullptr);
}

template<typename Type>
bool BidirectionalList<Type>::Empty() {
    return _head == nullptr || _size == 0;
}

template<typename Type>
typename BidirectionalList<Type>::Iterator BidirectionalList<Type>::begin() const {
    return BidirectionalList::Iterator(_head);
}

template<typename Type>
typename BidirectionalList<Type>::Iterator BidirectionalList<Type>::end() const {
    return BidirectionalList::Iterator(nullptr);
}

template<typename Type>
unsigned int BidirectionalList<Type>::size() const {
    return _size;
}

template<typename Type>
void BidirectionalList<Type>::_clear() {
    while (_size) {
        PopBack();
    }
}

template<typename Type>
BidirectionalList<Type>::~BidirectionalList<Type>() {
    _clear();
}

//-----------------------------------------------------------------------------
//input/output operators

template<typename T>
std::istream & operator >> (std::istream & stream, BidirectionalList<T> & list) {

    if (!list.Empty()) {
        list._clear();
    }
    T tmp;
    int sz;
    stream >> sz;
    for (int i = 0; i < sz; ++i) {
        stream >> tmp;
        list.PushBack(tmp);
    }
    return stream;
}

template<typename T>
std::ostream & operator << (std::ostream & stream, const BidirectionalList<T> & list) {
    stream << "BidirectionalList object : { ";
    for (auto i = list.begin(); i != list.end(); ++i) {
        stream << *i << " ";
    }
    stream << "}";
    return stream;
}
