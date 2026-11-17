#include <iostream>
#include <string>
#include "Lfu.h"

using namespace std;

int main() {
    cout << "=== Задание 7: LFU Cache ===" << endl;

    // Тест 1 (из задания)
    cout << "\n--- Тест 1 (cap = 3) ---" << endl;
    LFUCache cache1(3);
    cache1.set("5", "7");
    cache1.set("4", "6");
    cache1.set("3", "5");
    cache1.set("2", "4");
    cache1.set("1", "3");
    cout << "GET 1: " << cache1.get("1") << endl;
    cout << "GET 2: " << cache1.get("2") << endl;
    cout << "GET 3: " << cache1.get("3") << endl;
    cout << "GET 4: " << cache1.get("4") << endl;
    cout << "GET 5: " << cache1.get("5") << endl;
    // Ожидается: 3 4 5 -1 -1

    // Тест 2 (из задания)
    cout << "\n--- Тест 2 (cap = 2) ---" << endl;
    LFUCache cache2(2);
    cache2.set("1", "10");
    cache2.set("2", "20");
    cout << "GET 1: " << cache2.get("1") << endl; // 10
    cout << "GET 1: " << cache2.get("1") << endl; // 10
    cout << "GET 2: " << cache2.get("2") << endl; // 20
    cache2.set("3", "30"); // Вытесняет ключ 2 (частота 1), т.к. у 1 частота 3
    cout << "GET 2: " << cache2.get("2") << endl; // -1
    // Ожидается: 10 10 20 -1

    return 0;
}
