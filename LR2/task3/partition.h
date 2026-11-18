#pragma once
#include <string>
#include "linkedList.h"
#include "MySet.h"
#include "array.h"

using namespace std;

class SubsetPartitioner {
private:
    MyArray elementsArr;
    int n;
    ForwardList subsetA;
    ForwardList subsetB;
    int diff;

public:
    SubsetPartitioner();
    ~SubsetPartitioner();

    bool load(const string& input);
    bool solve();
    void printResult();
    int getDiff() const { return diff; }
};
