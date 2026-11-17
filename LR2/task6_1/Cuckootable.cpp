#include "Cuckootable.h"
#include <iostream>

Cuckootable::Cuckootable(int cap) {
    capacity = cap;
    maxKicks = cap * 2;
    
    table1.create();
    table2.create();
    
    for (int i = 0; i < capacity; i++) {
        table1.push_back("");
        table2.push_back("");
    }
}

Cuckootable::~Cuckootable() {}

int Cuckootable::hash1(const string& key) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash * 31 + key[i]) % capacity;
    }
    return hash;
}

int Cuckootable::hash2(const string& key) {
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++) {
        hash = (hash * 17 + key[i]) % capacity;
    }
    return hash;
}

string extractKey(const string& pair) {
    size_t pos = pair.find(':');
    if (pos == string::npos) return pair;
    return pair.substr(0, pos);
}

void Cuckootable::insert(const string& key, const string& value) {
    if (get(key) != "NOT_FOUND") {
        remove(key); 
    }

    string pair = key + ":" + value;
    
    string curPair = pair;
    int kicks = 0;

    while (kicks < maxKicks) {
        int i1 = hash1(extractKey(curPair));
        string occupant1 = table1.get(i1);
        
        if (occupant1 == "") {
            table1.set(i1, curPair);
            return;
        }
        
        table1.set(i1, curPair);
        curPair = occupant1;

        int i2 = hash2(extractKey(curPair));
        string occupant2 = table2.get(i2);
        
        if (occupant2 == "") {
            table2.set(i2, curPair);
            return;
        }

        table2.set(i2, curPair);
        curPair = occupant2;
        
        kicks++;
    }
    
    cout << "Error: Cuckoo hash cycle detected! Could not insert " << key << endl;
}

string Cuckootable::get(const string& key) {
    int i1 = hash1(key);
    string val1 = table1.get(i1);
    if (val1 != "" && extractKey(val1) == key) {
        return val1.substr(key.length() + 1);
    }
    
    int i2 = hash2(key);
    string val2 = table2.get(i2);
    if (val2 != "" && extractKey(val2) == key) {
        return val2.substr(key.length() + 1); 
    }
    
    return "NOT_FOUND";
}

void Cuckootable::remove(const string& key) {
    int i1 = hash1(key);
    string val1 = table1.get(i1);
    if (val1 != "" && extractKey(val1) == key) {
        table1.set(i1, "");
        return;
    }
    
    int i2 = hash2(key);
    string val2 = table2.get(i2);
    if (val2 != "" && extractKey(val2) == key) {
        table2.set(i2, "");
        return;
    }
}

void Cuckootable::print() {
    cout << "--- Hash Table (Cuckoo) ---" << endl;
    cout << "Table 1:" << endl;
    for (int i = 0; i < capacity; i++) {
        string val = table1.get(i);
        cout << "  [" << i << "] " << (val == "" ? "EMPTY" : val) << endl;
    }
    cout << "Table 2:" << endl;
    for (int i = 0; i < capacity; i++) {
        string val = table2.get(i);
        cout << "  [" << i << "] " << (val == "" ? "EMPTY" : val) << endl;
    }
}
