#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Chaintable.h"

using namespace std;

static vector<string> splitSubs(const string& subs) {
    vector<string> out;
    if (subs == "NOT_FOUND" || subs.empty()) return out;
    string cur;
    for (size_t i = 0; i <= subs.size(); i++) {
        if (i == subs.size() || subs[i] == ',') {
            if (!cur.empty()) out.push_back(cur);
            cur.clear();
        } else {
            cur += subs[i];
        }
    }
    return out;
}

static int countAllSubs(const string& emp, Chaintable& table, set<string>& visited) {
    if (visited.count(emp)) return 0;
    visited.insert(emp);

    vector<string> direct = splitSubs(table.get(emp));

    int total = 0;
    for (const string& sub : direct) {
        if (sub == emp) continue;
        if (visited.count(sub)) continue;
        total += 1 + countAllSubs(sub, table, visited);
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
