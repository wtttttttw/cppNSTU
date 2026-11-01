#pragma once
#include <string>
using namespace std;

class MyArray {
private:
    string* data;
    int size;
    int capacity;

public:
    MyArray();
    ~MyArray();

    void create();
    void push_back(string val);
    void insert_at(int index, string val);
    void remove_at(int index);
    string get(int index);
    void set(int index, string val);
    int length();
};
