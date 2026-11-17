#include "MySet.h"

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
