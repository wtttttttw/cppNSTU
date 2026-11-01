#pragma once
#include <string>
using namespace std;

class MyStack {
private:
    string* data;
    int size;
    int capacity;

public:
    MyStack();
    ~MyStack();

    void create();
    void push(string val);
    string pop();
    string peek();
    void print(); // <-- ДОБАВЛЕНО
};
