#pragma once
#include <string>
#include "array.h"
#include "linkedList.h"
#include "Chaintable.h"
using namespace std;

class LFUCache {
private:
    int capacity;
    int minFreq;
    
    Chaintable* cacheMap;
    
    MyArray freqLists; 
    ForwardList** lists;

    void updateFreq(const string& key);

public:
    LFUCache(int cap);
    ~LFUCache();

    void set(const string& key, const string& value);
    string get(const string& key);
};
