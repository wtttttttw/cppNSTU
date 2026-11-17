#include "partition.h"
#include <iostream>
#include <sstream>

SubsetPartitioner::SubsetPartitioner() : elements(nullptr), n(0), diff(0) {}

SubsetPartitioner::~SubsetPartitioner() { clearElements(); }

void SubsetPartitioner::clearElements() {
    delete[] elements;
    elements = nullptr;
    n = 0;
}

bool SubsetPartitioner::load(const string& input) {
    clearElements();

    istringstream iss1(input);
    int cnt = 0;
    int tmp;
    while (iss1 >> tmp) ++cnt;

    if (cnt == 0) {
        cerr << "Ошибка: пустое множество\n";
        return false;
    }

    elements = new int[cnt];
    n = 0;

    istringstream iss2(input);
    int x;
    while (iss2 >> x) {
        if (x <= 0) {
            cerr << "Ошибка: множество должно состоять из натуральных чисел\n";
            clearElements();
            return false;
        }
        elements[n++] = x;
    }
    return true;
}

bool SubsetPartitioner::solve() {
    subsetA.create();
    subsetB.create();

    long long S = 0;
    for (int i = 0; i < n; ++i) S += elements[i];

    int target = (int)(S / 2);

    char* dp = new char[target + 1];
    for (int w = 0; w <= target; ++w) dp[w] = 0;

    int* parent = new int[target + 1];
    for (int w = 0; w <= target; ++w) parent[w] = -1;

    dp[0] = 1;

    for (int i = 0; i < n; ++i) {
        int x = elements[i];
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

    char* used = new char[n];
    for (int i = 0; i < n; ++i) used[i] = 0;

    int cur = best;
    while (cur > 0) {
        int idx = parent[cur];
        if (idx < 0 || used[idx]) break;
        used[idx] = 1;
        cur -= elements[idx];
    }

    for (int i = 0; i < n; ++i) {
        if (used[i]) subsetA.push_back(to_string(elements[i]));
        else         subsetB.push_back(to_string(elements[i]));
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
