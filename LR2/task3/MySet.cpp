#include "MySet.h"
#include <sstream>
#include <iostream>

MySet::MySet() {
    table = new ForwardList*[BUCKETS];
    for (int i = 0; i < BUCKETS; i++) table[i] = new ForwardList();
}

MySet::~MySet() {
    for (int i = 0; i < BUCKETS; i++) delete table[i];
    delete[] table;
}

int MySet::hash(const string& key) const {
    unsigned long h = 0;
    for (char c : key) h = h * 31 + c;
    return h % BUCKETS;
}

void MySet::create() {
    for (int i = 0; i < BUCKETS; i++) table[i]->create();
}

void MySet::set_add(const string& val) {
    int idx = hash(val);
    if (!table[idx]->find(val)) {
        table[idx]->push_front(val);
    }
}

void MySet::set_del(const string& val) {
    int idx = hash(val);
    table[idx]->remove(val);
}

bool MySet::set_at(const string& val) const {
    int idx = hash(val);
    return table[idx]->find(val);
}

void MySet::fillArray(MyArray& arr) {
    for (int i = 0; i < BUCKETS; i++) {
        stringstream buffer;
        streambuf* old = cout.rdbuf(buffer.rdbuf());
        table[i]->print(); 
        cout.rdbuf(old);

        string output = buffer.str();
        if (output.find("EMPTY") != string::npos) continue;

        if (output.length() > 3) output = output.substr(3);

        stringstream ss(output);
        string val;
        while (ss >> val) {
            arr.push_back(val);
        }
    }
}
