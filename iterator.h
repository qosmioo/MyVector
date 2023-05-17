#ifndef VECTOR_ITERATOR_H
#define VECTOR_ITERATOR_H
#include <iostream>
#include "vector.h"

template <typename T>

class Iterator {
private:
    size_t it;
    MyVector<T> &vec;
public:
    explicit Iterator<T>(MyVector <T> &container_obj, size_t size);
    Iterator<T> next();
    T value();
    bool is_end();
    bool is_begin();
    Iterator<T> &operator++();
    Iterator<T> &operator--();
    T &operator*();
    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
};

template<typename T>
Iterator<T>::Iterator(MyVector<T> &container_obj, size_t size):vec(container_obj), it(size) {
    if (size == -1) {
        it = vec.get_length();
    }
}

template<typename T>
Iterator<T> Iterator<T>::next() {
    it++;
    return *this;
}

template<typename T>
T Iterator<T>::value() {
    return **this;
}

template <typename T>
bool Iterator<T>::is_end() {
    return it == vec.get_length() - 1;
}

template <typename T>
bool Iterator<T>::is_begin() {
    return it == 0;
}

template <typename T>
Iterator<T> & Iterator<T>::operator++() {
    if (!this->is_end()) {
        it++;
    }
    return *this;
}

template <typename T>
Iterator<T> & Iterator<T>::operator--() {
    if (it != this->is_begin()) {
        it--;
    }
    return *this;
}

template <typename T> T& Iterator<T>::operator*() {
    return vec[it];
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> &b) {
    return it == b.it && &vec == &b.vec;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> &b) {
    if ((&vec == &b.vec && it != b.it) || &vec != &b.vec) {
        return true;
    } else {
        return false;
    }
}

#endif //VECTOR_ITERATOR_H
