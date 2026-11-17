#include <iostream>
#include <string>
#include <cstdio>
#include "partition.h"

using namespace std;

int main(int argc, char* argv[]) {
    string input;

    if (argc >= 2) {
        string a1 = argv[1];
        if (a1 == "--file" && argc >= 3) {
            FILE* f = fopen(argv[2], "r");
            if (!f) { cerr << "Не удалось открыть файл\n"; return 1; }
            char buf[4096];
            while (fgets(buf, sizeof(buf), f)) input += buf;
            fclose(f);
        } else {
            for (int i = 1; i < argc; ++i) { input += argv[i]; input += ' '; }
        }
    } else {
        cout << "Введите множество натуральных чисел: ";
        getline(cin, input);
    }

    SubsetPartitioner sp;
    if (!sp.load(input)) return 1;
    if (!sp.solve())    return 1;
    sp.printResult();
    return 0;
}
