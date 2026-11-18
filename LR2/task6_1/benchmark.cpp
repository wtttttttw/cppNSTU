#include <iostream>
#include <string>
#include <chrono>
#include <cstdlib>
#include "Chaintable.h"
#include "Cuckootable.h"

using namespace std;
using namespace std::chrono;

string randomString(int len) {
    string s = "";
    for (int i = 0; i < len; i++) {
        s += (char)('a' + rand() % 26);
    }
    return s;
}

void runBenchmark(int numElements) {
    cout << "--- Тест: " << numElements << " элементов ---" << endl;
    
    string* keys = new string[numElements];
    for (int i = 0; i < numElements; i++) {
        keys[i] = randomString(10);
    }

    // ==========================================
    // 1. МЕТОД ЦЕПОЧЕК (Load Factor = 1.0 - нормально)
    // ==========================================
    int chainSize = numElements;
    Chaintable chain(chainSize);
    
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) chain.insert(keys[i], "val");
    auto stop = high_resolution_clock::now();
    auto insertChain = duration_cast<microseconds>(stop - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) chain.get(keys[i]);
    stop = high_resolution_clock::now();
    auto searchChain = duration_cast<microseconds>(stop - start).count();

    // ==========================================
    // 2. КУКУШКА (Load Factor = 0.25 - безопасно)
    // ==========================================
    int cuckooSize = numElements * 4;
    Cuckootable cuckoo(cuckooSize); 
    
    start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) cuckoo.insert(keys[i], "val");
    stop = high_resolution_clock::now();
    auto insertCuckoo = duration_cast<microseconds>(stop - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < numElements; i++) cuckoo.get(keys[i]);
    stop = high_resolution_clock::now();
    auto searchCuckoo = duration_cast<microseconds>(stop - start).count();

    cout << "Вставка (Chain): " << insertChain << " мкс | (Cuckoo): " << insertCuckoo << " мкс" << endl;
    cout << "Поиск  (Chain): " << searchChain << " мкс | (Cuckoo): " << searchCuckoo << " мкс" << endl;
    cout << endl;

    delete[] keys;
}

int main() {
    srand(42); 
    cout << "========================================\n";
    cout << "   БЕНЧМАРК ХЕШ-ТАБЛИЦ                  \n";
    cout << "========================================\n\n";

    runBenchmark(1000);
    runBenchmark(5000);
    runBenchmark(10000);
    runBenchmark(50000);

    return 0;
}
