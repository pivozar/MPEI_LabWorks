#pragma once
#include <iostream>
#include <stdexcept>

template<typename Type>
class Queue {
public:
    Queue();
    Queue(Queue<Type> & q);
    explicit Queue(Type item);

    void Push(Type value);
    Type Pop();
    Type Front() const;
    Type Back() const;

    bool Empty() const;
    unsigned int size() const;

    template<typename T>
    friend std::istream & operator >> (std::istream & stream, Queue<T> & q);
    template<typename T>
    friend std::ostream & operator << (std::ostream & stream, const Queue<T> & q);

    ~Queue();

private:
    Type * _data;
    unsigned int _size;
    unsigned int _capacity;
    unsigned int _begin;
    unsigned int _end;
    void _resize(unsigned int new_capacity);
    void _clear();
    Type & operator[](unsigned int i) const;
};

template<typename Type>
Queue<Type>::Queue()
    : _data(new Type[2]), _size(0), _capacity(2),
      _begin(0), _end(0) {}

template<typename Type>
Queue<Type>::Queue(Queue<Type> &q)
    : _data(new Type[q._capacity]), _size(q._size), _capacity(q._capacity),
      _begin(0), _end(q._size) {
    for (int i = q._begin; i != q._end; i = (i + 1) % q._capacity) {
        _data[(i + _capacity - q._begin) % _capacity] = q[i];
    }
}

template<typename Type>
Queue<Type>::Queue(Type item) : Queue() {
    Push(item);
}

template<typename Type>
void Queue<Type>::Push(Type value) {
    if (_capacity - _size < 3) {
        _resize(_capacity*2);
    }
    _data[(_begin + _size) % _capacity] = value;
    _size++;
    _end = (_end + 1) % _capacity;
}

template<typename Type>
Type Queue<Type>::Pop() {
    if (_size + 2 < _capacity / 2) {
        _resize(_capacity/2);
    }
    Type res = _data[_begin];
    _data[_begin] = 0;
    _begin = (_begin + 1) % _capacity;
    _size--;
    return res;
}

template<typename Type>
Type Queue<Type>::Front() const {
    return _data[_begin];
}

template<typename Type>
Type Queue<Type>::Back() const {
    return _data[(_capacity - 1 + _end) % _capacity];
}

template<typename Type>
bool Queue<Type>::Empty() const {
    return _size == 0;
}

template<typename Type>
unsigned int Queue<Type>::size() const {
    return _size;
}

template<typename Type>
Queue<Type>::~Queue() {
    delete[] _data;
}

template<typename Type>
void Queue<Type>::_resize(unsigned int new_capacity) {
    Type * old_data = _data;
    _data = new Type[new_capacity];
    for (int i = 0; i < _size; i++) {
        _data[i] = old_data[(_begin + i) % _capacity];
    }
    _begin = 0;
    _end = _size;
    _capacity = new_capacity;
    delete[] old_data;
}

template<typename Type>
void Queue<Type>::_clear() {
    _begin = 0;
    _end = 0;
    _size = 0;
    _resize(4);
}

template<typename Type>
Type &Queue<Type>::operator[](unsigned int i) const {
    if (i >= _size) {
        throw std::out_of_range("Queue index is out of range!");
    }
    return _data[(_begin + i) % _capacity];
}

template<typename T>
std::istream &operator>>(std::istream &stream, Queue<T> &q) {
    unsigned int sz;
    stream >> sz;
    q._clear();
    q._resize(sz);
    T tmp;
    for (int i = 0; i < sz; ++i) {
        stream >> tmp;
        q.Push(tmp);
    }
    return stream;
}

template<typename T>
std::ostream &operator<<(std::ostream &stream, const Queue<T> &q) {
    stream << "Queue object: { ";
    for (int i = 0; i < q._size; i++) {
        stream << q[i] << " ";
    }
    stream << "}";
    return stream;
}
