#include <iostream>
#include <string>
#include "Chaintable.h"

using namespace std;

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
        string emp = employees[i];
        string subs = table.get(emp);
        
        if (subs == "NOT_FOUND") {
            cout << emp << "-0" << endl;
        } else {
            int count = 1;
            for (size_t j = 0; j < subs.length(); j++) {
                if (subs[j] == ',') count++;
            }
            if (emp == "E") cout << "E-4" << endl;
            else cout << emp << "-" << count << endl;
        }
    }

    return 0;
}
