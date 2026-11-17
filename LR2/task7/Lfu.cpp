#include "Lfu.h"
#include <iostream>

LFUCache::LFUCache(int cap) {
    capacity = cap;
    minFreq = 1;
    
    cacheMap = new Chaintable(cap * 2);
    
    freqLists.create();
    lists = new ForwardList*[capacity + 2];
    for (int i = 0; i <= capacity + 1; i++) {
        lists[i] = new ForwardList();
        freqLists.push_back("freq_" + to_string(i));
    }
}

LFUCache::~LFUCache() {
    delete cacheMap;
    for (int i = 0; i <= capacity + 1; i++) delete lists[i];
    delete[] lists;
}

void parseValFreq(const string& str, string& val, int& freq) {
    size_t pos = str.find(':');
    val = str.substr(0, pos);
    freq = stoi(str.substr(pos + 1));
}

void LFUCache::updateFreq(const string& key) {
    string info = cacheMap->get(key);
    if (info == "NOT_FOUND") return;
    
    string val;
    int freq;
    parseValFreq(info, val, freq);
    
    lists[freq]->remove(key);
    
    if (freq == minFreq && lists[freq]->get_first() == "EMPTY") {
        minFreq++;
    }
    
    int newFreq = freq + 1;
    lists[newFreq]->push_front(key);
    
    cacheMap->remove(key);
    cacheMap->insert(key, val + ":" + to_string(newFreq));
}

string LFUCache::get(const string& key) {
    string info = cacheMap->get(key);
    if (info == "NOT_FOUND") return "-1";
    
    string val;
    int freq;
    parseValFreq(info, val, freq);
    
    updateFreq(key);
    return val;
}

void LFUCache::set(const string& key, const string& value) {
    if (capacity <= 0) return;
    
    string info = cacheMap->get(key);
    if (info != "NOT_FOUND") {
        cacheMap->remove(key);
        string val;
        int freq;
        parseValFreq(info, val, freq);
        cacheMap->insert(key, value + ":" + to_string(freq));
        updateFreq(key);
        return;
    }
    
    if ((int)cacheMap->getSize() >= capacity) {
        string evictKey = lists[minFreq]->get_last();
        if (evictKey != "EMPTY") {
            lists[minFreq]->remove(evictKey);
            cacheMap->remove(evictKey);
        }
    }
    
    cacheMap->insert(key, value + ":1");
    lists[1]->push_front(key);
    minFreq = 1;
}
