#pragma once
#include <string>
#include "array.h"
#include "linkedList.h"

using namespace std;

class Chaintable {
private:
    MyArray table;
    ForwardList** buckets;
    int capacity;

    int hashFunc(const string& key);

public:
    Chaintable(int cap = 10);
    ~Chaintable();

    void insert(const string& key, const string& value);
    string get(const string& key);
    void remove(const string& key);
    void print();
};
