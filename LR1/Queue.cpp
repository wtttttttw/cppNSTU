#include "Queue.h"
#include <iostream>

MyQueue::MyQueue() : data(nullptr), head(0), tail(0), capacity(0) {}
MyQueue::~MyQueue() { if (data) delete[] data; }

void MyQueue::create() {
    if (data) delete[] data;
    capacity = 4;
    data = new string[capacity];
    head = 0; tail = 0;
}

void MyQueue::push(string val) {
    if (!data) create();
    if (tail == capacity) {
        capacity *= 2;
        string* newData = new string[capacity];
        int newHead = 0;
        for (int i = head; i < tail; i++) newData[newHead++] = data[i];
        delete[] data;
        data = newData;
        tail = newHead;
        head = 0;
    }
    data[tail++] = val;
}

string MyQueue::pop() {
    if (head == tail) return "EMPTY";
    return data[head++];
}

string MyQueue::peek() {
    if (head == tail) return "EMPTY";
    return data[head];
}

void MyQueue::print() {
    if (head == tail) {
        cout << "-> EMPTY" << endl;
        return;
    }
    cout << "-> ";
    for (int i = head; i < tail; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}
