#include "MySet.h"
#include <iostream>
#include <sstream>

MySet::MySet() {
    table = new ForwardList*[BUCKETS];
    for (int i = 0; i < BUCKETS; i++) {
        table[i] = new ForwardList();
    }
}

MySet::~MySet() {
    for (int i = 0; i < BUCKETS; i++) {
        delete table[i];
    }
    delete[] table;
}

void MySet::create() {
    for (int i = 0; i < BUCKETS; i++) {
        table[i]->create();
    }
}

bool MySet::set_add(const string& val) {
    int idx = hash(val);
    if (!table[idx]->find(val)) {
        table[idx]->push_front(val);
        return true;
    }
    return false;
}

bool MySet::set_del(const string& val) {
    int idx = hash(val);
    if (table[idx]->find(val)) {
        table[idx]->remove(val);
        return true;
    }
    return false;
}

bool MySet::set_at(const string& val) const {
    int idx = hash(val);
    return table[idx]->find(val);
}

void MySet::print() const {
    bool isEmpty = true;
    for (int i = 0; i < BUCKETS; i++) {
        if (table[i]->get_first() != "EMPTY") {
            isEmpty = false;
            break;
        }
    }
    if (isEmpty) {
        cout << "{}" << endl;
        return;
    }
    
    cout << "{";
    bool first = true;
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
            if (!first) cout << ", ";
            cout << val;
            first = false;
        }
    }
    cout << "}" << endl;
}
