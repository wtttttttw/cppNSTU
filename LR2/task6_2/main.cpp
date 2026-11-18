#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include "Chaintable.h"

using namespace std;

static void splitSubs(const string& subs, string* out, int& n) {
    n = 0;
    if (subs == "NOT_FOUND" || subs.empty()) return;
    string cur;
    for (size_t i = 0; i <= subs.size(); i++) {
        if (i == subs.size() || subs[i] == ',') {
            if (!cur.empty()) out[n++] = cur;
            cur.clear();
        } else {
            cur += subs[i];
        }
    }
}

static int countAllSubs(const string& emp, Chaintable& table, set<string>& visited) {
    if (visited.count(emp)) return 0;
    visited.insert(emp);

    string raw = table.get(emp);
    static string direct[256];
    int n = 0;
    splitSubs(raw, direct, n);

    int total = 0;
    for (int i = 0; i < n; i++) {
        if (direct[i] == emp) continue;
        if (visited.count(direct[i])) continue;
        total += 1 + countAllSubs(direct[i], table, visited);
    }
    return total;
}

int main() {
    cout << "=== Задание 6.2 (Вариант 5: Количество сотрудников) ===" << endl;

    Chaintable table(5);

    table.insert("B", "A");
    table.insert("B", "C");
    table.insert("E", "D");
    table.insert("E", "B");
    table.insert("E", "E");

    cout << "\nТаблица менеджеров:" << endl;
    table.print();

    cout << "\nРезультат (Сотрудник - Количество подчиненных):" << endl;

    string employees[] = {"A", "B", "C", "D", "E"};

    for (int i = 0; i < 5; i++) {
        set<string> visited;
        int count = countAllSubs(employees[i], table, visited);
        cout << employees[i] << "-" << count << endl;
    }

    return 0;
}
