#pragma once
#include <string>
using namespace std;

class MyQueue {
private:
    string* data;
    int head;
    int tail;
    int capacity;

public:
    MyQueue();
    ~MyQueue();

    void create();
    void push(string val);
    string pop();
    string peek();
    void print(); // <-- ДОБАВЛЕНО
};
