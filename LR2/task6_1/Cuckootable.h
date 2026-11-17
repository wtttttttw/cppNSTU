#pragma once
#include <string>
#include "array.h"

using namespace std;

class Cuckootable {
private:
    MyArray table1;
    MyArray table2;
    int capacity;
    int maxKicks;

    int hash1(const string& key);
    int hash2(const string& key);

public:
    Cuckootable(int cap = 10);
    ~Cuckootable();

    void insert(const string& key, const string& value);
    string get(const string& key);
    void remove(const string& key);
    void print();
};
