#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include "exceptions.h"

template<typename T>
class Iterator;

template <typename T>

class MyVector {
private:
    T *data;
    size_t count;
    void copy_data(T* arr);
    void memory_alloc();
public:
    explicit MyVector(int length);
    MyVector(const MyVector<T>& vect);
    explicit MyVector(std::initializer_list<T> lst);
    ~MyVector();

    int get_length() const;
    void set_elem(int index,const T& elem);
    T& get_elem(int index);
    T* to_array();

    T& operator[](int index);
    MyVector<T>& operator =(const MyVector<T>& lst);
    MyVector<T>& operator +=(const MyVector<T>& vect);
    MyVector<T>& operator -=(const MyVector<T>& vect);
    MyVector<T>& operator *=(const T& val);
    MyVector<T>& operator /=(const T& val);

    template <typename _T> friend MyVector<_T> operator +(const MyVector<_T>& v1, const MyVector<_T>& v2);
    template <typename _T> friend MyVector<_T> operator -(const MyVector<_T>& v1, const MyVector<_T>& v2);
    template<typename _T> friend MyVector<_T> operator /(const MyVector<_T>& v1, const _T& val);
    template<typename _T> friend MyVector<_T> operator *(const MyVector<_T>& v1, const _T& val);
    template <typename _T> friend std::ostream& operator <<(std::ostream &os, MyVector<_T> &lst);

    Iterator<T> iterator_begin(){return Iterator<T>(*this, 0);};
    Iterator<T> iterator_end(){return Iterator<T>(*this, get_length() - 1);};
};

template<typename T>
void MyVector<T>::copy_data(T *arr) {
    for (int i = 0; i < count; ++i) {
        data[i] = arr[i];
    }
}

template<typename T>
void MyVector<T>::memory_alloc() {
    try {
        data = new T[count];
    } catch (std::bad_alloc &ex) {
        throw Exceptions("memory allocation error.");
    }
}

template <typename T>
MyVector<T>::MyVector(int length) { // конструктор с указанием размерности
    if (length < 0) {
        throw Exceptions("incorrect size.");
    }
    count = (size_t)length;
    memory_alloc();
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T> &vect) { // конструктор копирования
    count = vect.get_length();
    if (count == 0) {
        throw Exceptions("memory allocation error.");
    }
    memory_alloc();
    copy_data( vect.data);
}

template <typename T>
int MyVector<T>::get_length() const { // получить текущий размер
    return count;
}

template <typename T>
MyVector<T>::~MyVector() { // деструктор
    delete []data;
}

template<typename T>
MyVector<T>::MyVector(std::initializer_list<T> lst):count(lst.size()){ // конструктор со списком инициализации
    if (count == 0) {
        throw Exceptions("memory allocation error.");
    }
    memory_alloc();
    int i = 0;
    for (T val : lst) {
        data[i] = val;
        ++i;
    }
}

template <typename T>
void MyVector<T>::set_elem(int index, const T &elem) { // изменить элемент вектора по индексу
    if (index < 0 || index >= this->get_length()) {
        throw Exceptions ("incorrect index.");
    }
    data[index] = elem;
}

template <typename T>
T &MyVector<T>::get_elem(int index) { // получить элемент списка по индексу
    if (index < 0 || index > get_length()) {
        throw Exceptions("incorrect index.");
    }
    return data[index - 1];
}

template <typename T>
T* MyVector<T>::to_array() { // создание массива
    try {
        T* array = new T[count];
        for (int i = 0; i < count; ++i) {
            array[i] = data[i];
        }
        return array;
    } catch (std::bad_alloc &ex) {
        throw Exceptions("memory allocation error.");
    }
}

template<typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector<T> &lst) { // перегрузка оператора присваивания
    delete[] data;
    count = lst.get_length();

    memory_alloc();
    copy_data(lst.data);
    return *this;
}

template <typename _T>
std::ostream& operator <<(std::ostream &os, MyVector<_T> &lst) {
    os << "vector (";
    for (int i = 0; i < lst.get_length() - 1; ++i) {
        os << lst.data[i] << ", ";
    }
    os << lst.data[lst.get_length() - 1] << ")\n";
    return os;
}

template<typename T>
T &MyVector<T>::operator[](int index) {
    if (index < 0 || index >= count) {
        throw Exceptions("incorrect index.");
    }
    return data[index];
}

template<typename T>
MyVector<T> &MyVector<T>::operator+=(const MyVector<T> &vect) {
    if (count != vect.get_length()) {
        throw Exceptions("different sizes of vectors.");
    } else {
        for (int i = 0; i < count; ++i) {
            data[i] += vect.data[i];
        }
    }
    return *this;
}

template<typename T>
MyVector<T> &MyVector<T>::operator-=(const MyVector<T> &vect) {
    if (count != vect.get_length()) {
        throw Exceptions("different sizes of vectors.");
    } else {
        for (int i = 0; i < count; ++i) {
            data[i] -= vect.data[i];
        }
    }
    return *this;
}

template<typename T>
MyVector<T> &MyVector<T>::operator*=(const T &val) {
    for (size_t i = 0; i < count; ++i) {
        data[i] *= val;
    }
    return *this;
}

template<typename T>
MyVector<T> &MyVector<T>::operator/=(const T &val) {
    if (val == 0) {
        throw Exceptions("division by zero.");
    }
    for (size_t i = 0; i < count; ++i) {
        data[i] /= val;
    }
    return *this;
}

template<typename _T>
MyVector<_T> operator+(const MyVector<_T> &v1, const MyVector<_T> &v2) {
    MyVector<_T> new_vector (v1);
    new_vector += v2;

    return new_vector;
}

template<typename _T>
MyVector<_T> operator-(const MyVector<_T> &v1, const MyVector<_T> &v2) {
    MyVector<_T> new_vector (v1);
    new_vector -= v2;

    return new_vector;
}

template<typename _T>
MyVector<_T> operator*(const MyVector<_T> &v1, const _T &val) {
    MyVector<_T> new_vector (v1);
    v1 *= val;

    return new_vector;
}

template<typename _T>
MyVector<_T> operator/(const MyVector<_T> &v1, const _T &val) {
    if (val == 0) {
        throw Exceptions("division by zero.");
    }
    MyVector<_T> new_vector (v1);
    v1 /= val;

    return new_vector;
}

#endif //VECTOR_VECTOR_H
