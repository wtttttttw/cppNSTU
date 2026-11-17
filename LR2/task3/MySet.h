#pragma once
#include <string>
#include "linkedList.h"
#include "array.h"

using namespace std;

class MySet {
private:
    static const int BUCKETS = 10007;
    ForwardList** table;
    int hash(const string& key) const;

public:
    MySet();
    ~MySet();
    void create();
    void set_add(const string& val);
    void set_del(const string& val);
    bool set_at(const string& val) const;
    
    void fillArray(MyArray& arr); 
};
