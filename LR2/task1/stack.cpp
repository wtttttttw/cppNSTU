#include "stack.h"

template <typename T>
MyStack<T>::MyStack() : data(nullptr), size(0), capacity(0) {}

template <typename T>
MyStack<T>::~MyStack() { if (data) delete[] data; }

template <typename T>
void MyStack<T>::create() {
    if (data) delete[] data;
    capacity = 4;
    data = new T[capacity];
    size = 0;
}

template <typename T>
void MyStack<T>::push(const T& val) {
    if (!data) create();
    if (size == capacity) {
        capacity *= 2;
        T* newData = new T[capacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
    }
    data[size++] = val;
}

template <typename T>
T MyStack<T>::pop() {
    if (size == 0) return T();
    return data[--size];
}

template <typename T>
T MyStack<T>::peek() const {
    if (size == 0) return T();
    return data[size - 1];
}

template <typename T>
void MyStack<T>::print() const {
    if (size == 0) { cout << "-> EMPTY" << endl; return; }
    cout << "-> ";
    for (int i = size - 1; i >= 0; i--) cout << data[i] << " ";
    cout << endl;
}

template class MyStack<string>;
template class MyStack<int>;
template class MyStack<char>;
