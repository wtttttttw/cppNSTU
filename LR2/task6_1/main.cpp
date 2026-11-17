#include <iostream>
#include <string>
#include "Chaintable.h"
#include "Cuckootable.h"

using namespace std;

int main() {
    cout << "========================================\n";
    cout << "   ТЕСТИРОВАНИЕ ХЕШ-ТАБЛИЦ (ЛР2)        \n";
    cout << "========================================\n\n";

    cout << "--- 1. Метод цепочек (Chaintable) ---\n";
    Chaintable chain(5);

    cout << "Вставляем элементы (apple, banana, cherry)...\n";
    chain.insert("apple", "red");
    chain.insert("banana", "yellow");
    chain.insert("cherry", "dark red");
    
    chain.insert("melon", "green"); 

    chain.print();

    cout << "\nИщем 'banana': " << chain.get("banana") << "\n";
    cout << "Ищем 'potato': " << chain.get("potato") << " (ожидаем NOT_FOUND)\n";

    cout << "\nУдаляем 'apple'...\n";
    chain.remove("apple");
    chain.print();

    cout << "\n--- 2. Хеширование кукушки (Cuckootable) ---\n";
    Cuckootable cuckoo(5);

    cout << "Вставляем элементы (apple, banana, cherry, date)...\n";
    cuckoo.insert("apple", "red");
    cuckoo.insert("banana", "yellow");
    cuckoo.insert("cherry", "dark red");
    cuckoo.insert("date", "brown");

    cuckoo.print();

    cout << "\nИщем 'date': " << cuckoo.get("date") << "\n";
    cout << "Ищем 'apple': " << cuckoo.get("apple") << "\n";

    cout << "\nУдаляем 'banana'...\n";
    cuckoo.remove("banana");
    cuckoo.print();

    cout << "\nТестирование завершено.\n";
    return 0;
}
