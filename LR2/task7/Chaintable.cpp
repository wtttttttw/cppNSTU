#include "Chaintable.h"
#include <iostream>

Chaintable::Chaintable(int cap) {
    capacity = cap;
    table.create();
    buckets = new ForwardList*[capacity];
    for (int i = 0; i < capacity; i++) {
        buckets[i] = new ForwardList();
        table.push_back("Bucket_" + to_string(i));
    }
}

Chaintable::~Chaintable() {
    for (int i = 0; i < capacity; i++) delete buckets[i];
    delete[] buckets;
}

int Chaintable::hashFunc(const string& key) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % capacity;
    }
    return hash;
}

int Chaintable::getSize() {
    int count = 0;
    for (int i = 0; i < capacity; i++) {
        ForwardList& list = *buckets[i];
        ForwardList temp;
        while (true) {
            string first = list.get_first();
            if (first == "EMPTY") break;
            list.pop_front();
            temp.push_front(first);
            count++;
        }
        while (true) {
            string first = temp.get_first();
            if (first == "EMPTY") break;
            temp.pop_front();
            list.push_front(first);
        }
    }
    return count;
}

void Chaintable::insert(const string& key, const string& value) {
    int index = hashFunc(key);
    
    ForwardList& list = *buckets[index];
    ForwardList temp;
    
    bool found = false;
    while (true) {
        string first = list.get_first();
        if (first == "EMPTY") break;
        
        list.pop_front();
        
        string prefix = key + ":";
        if (first.substr(0, prefix.length()) == prefix) {
            temp.push_front(first + "," + value);
            found = true;
        } else {
            temp.push_front(first);
        }
    }
    
    if (!found) {
        temp.push_front(key + ":" + value);
    }
    
    while (true) {
        string first = temp.get_first();
        if (first == "EMPTY") break;
        temp.pop_front();
        list.push_front(first);
    }
}

string Chaintable::get(const string& key) {
    int index = hashFunc(key);
    ForwardList& list = *buckets[index];
    ForwardList temp;
    string result = "NOT_FOUND";
    string prefix = key + ":";
    
    while (true) {
        string first = list.get_first();
        if (first == "EMPTY") break;
        
        list.pop_front();
        temp.push_front(first);
        
        if (first.substr(0, prefix.length()) == prefix) {
            result = first.substr(prefix.length());
            break; 
        }
    }
    
    while (true) {
        string first = temp.get_first();
        if (first == "EMPTY") break;
        temp.pop_front();
        list.push_front(first);
    }
    
    return result;
}

void Chaintable::remove(const string& key) {
    int index = hashFunc(key);
    ForwardList& list = *buckets[index];
    ForwardList temp;
    string prefix = key + ":";
    
    while (true) {
        string first = list.get_first();
        if (first == "EMPTY") break;
        
        list.pop_front();
        
        if (first.substr(0, prefix.length()) != prefix) {
            temp.push_front(first);
        }
    }
    
    while (true) {
        string first = temp.get_first();
        if (first == "EMPTY") break;
        temp.pop_front();
        list.push_front(first);
    }
}

void Chaintable::print() {
    cout << "--- Hash Table (Chaining) ---" << endl;
    for (int i = 0; i < capacity; i++) {
        cout << table.get(i) << ": ";
        buckets[i]->print(); 
    }
}
