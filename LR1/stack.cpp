#include "stack.h"
#include <iostream>

MyStack::MyStack() : data(nullptr), size(0), capacity(0) {}
MyStack::~MyStack() { if (data) delete[] data; }

void MyStack::create() {
    if (data) delete[] data;
    capacity = 4;
    data = new string[capacity];
    size = 0;
}

void MyStack::push(string val) {
    if (!data) create();
    if (size == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
    }
    data[size++] = val;
}

string MyStack::pop() {
    if (size == 0) return "EMPTY";
    return data[--size];
}

string MyStack::peek() {
    if (size == 0) return "EMPTY";
    return data[size - 1];
}

// <-- ДОБАВЛЕНО: Вывод от вершины к дну
void MyStack::print() {
    if (size == 0) {
        cout << "-> EMPTY" << endl;
        return;
    }
    cout << "-> ";
    for (int i = size - 1; i >= 0; i--) {
        cout << data[i] << " ";
    }
    cout << endl;
}
