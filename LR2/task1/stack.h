#pragma once
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class MyStack{
private:
    T* data;
    int size;
    int capacity;

public:
    MyStack();
    ~MyStack();

    void create();
    void push(const T& val);
    T pop();
    T peek() const;
    bool empty() const { return size == 0; }
    int getSize() const { return size; }
    void print() const;
};
