#include "array.h"

MyArray::MyArray() : data(nullptr), size(0), capacity(0) {}
MyArray::~MyArray() {
    if (data != nullptr) delete[] data;
}

void MyArray::create() {
    if (data != nullptr) delete[] data;
    capacity = 4;
    data = new string[capacity];
    size = 0;
}

void MyArray::push_back(string val) {
    if (data == nullptr) create();
    if (size == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
    }
    data[size++] = val;
}

void MyArray::insert_at(int index, string val) {
    if (index < 0 || index > size) return;
    push_back("");
    for (int i = size - 1; i > index; i--) data[i] = data[i - 1];
    data[index] = val;
}

void MyArray::remove_at(int index) {
    if (index < 0 || index >= size) return;
    for (int i = index; i < size - 1; i++) data[i] = data[i + 1];
    size--;
}

string MyArray::get(int index) {
    if (index < 0 || index >= size) return "ERROR: Index out of bounds";
    return data[index];
}

void MyArray::set(int index, string val) {
    if (index >= 0 && index < size) data[index] = val;
}

int MyArray::length() { return size; }
