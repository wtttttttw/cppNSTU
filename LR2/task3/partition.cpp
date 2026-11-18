#include "partition.h"
#include <iostream>
#include <sstream>

SubsetPartitioner::SubsetPartitioner() : n(0), diff(0) {}

SubsetPartitioner::~SubsetPartitioner() {}

bool SubsetPartitioner::load(const string& input) {
    MySet uniqueSet;
    istringstream iss(input);
    int x;
    bool hasNumbers = false;

    while (iss >> x) {
        if (x <= 0) {
            cerr << "Ошибка: множество должно состоять из натуральных чисел\n";
            return false;
        }
        uniqueSet.set_add(to_string(x));
        hasNumbers = true;
    }

    if (!hasNumbers) {
        cerr << "Ошибка: пустое множество\n";
        return false;
    }

    elementsArr.create();
    uniqueSet.fillArray(elementsArr);
    n = elementsArr.length();

    return true;
}

bool SubsetPartitioner::solve() {
    subsetA.create();
    subsetB.create();

    if (n <= 0) return false;

    long long S = 0;
    for (int i = 0; i < n; ++i) {
        S += stoi(elementsArr.get(i));
    }

    int target = (int)(S / 2);

    char* dp = new char[target + 1];
    for (int w = 0; w <= target; ++w) dp[w] = 0;

    int* parent = new int[target + 1];
    for (int w = 0; w <= target; ++w) parent[w] = -1;

    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        int x = stoi(elementsArr.get(i));
        for (int w = target; w >= x; --w) {
            if (!dp[w] && dp[w - x]) {
                dp[w] = 1;
                parent[w] = i;
            }
        }
    }

    int best = 0;
    for (int w = target; w >= 0; --w) {
        if (dp[w]) { best = w; break; }
    }

    size_t allocSize = (n > 0) ? (size_t)n : 1;
    char* used = new char[allocSize];
    for (int i = 0; i < n; ++i) used[i] = 0;

    int cur = best;
    while (cur > 0) {
        int idx = parent[cur];
        if (idx < 0 || used[idx]) break;
        used[idx] = 1;
        cur -= stoi(elementsArr.get(idx));
    }

    for (int i = 0; i < n; ++i) {
        if (used[i]) subsetA.push_back(elementsArr.get(i));
        else         subsetB.push_back(elementsArr.get(i));
    }

    diff = (int)(S - 2LL * best);

    delete[] dp;
    delete[] parent;
    delete[] used;
    return true;
}

void SubsetPartitioner::printResult() {
    cout << "Подмножество A: ";
    subsetA.print();
    cout << "Подмножество B: ";
    subsetB.print();
    cout << "Разница сумм: " << diff << "\n";
}
