#pragma once
#include <string>
#include "linkedList.h"

using namespace std;

class SubsetPartitioner {
private:
    int* elements;
    int  n;
    ForwardList subsetA;
    ForwardList subsetB;
    int diff;

    void clearElements();

public:
    SubsetPartitioner();
    ~SubsetPartitioner();

    bool load(const string& input);
    bool solve();
    void printResult();
    int getDiff() const { return diff; }
};
