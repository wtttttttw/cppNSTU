#pragma once
#include <string>
using namespace std;

class DoubleList {
private:
    struct Node {
        string value;
        Node* next;
        Node* prev;
        Node(string v) : value(v), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    DoubleList();
    ~DoubleList();

    void create();
    void push_front(string val);
    void push_back(string val);
    void insert_after(string target, string val);
    void insert_before(string target, string val);
    void remove(string val);
    bool find(string val);

    // Несколько способов чтения
    void print();       // Вывод всего списка
    string get_first(); // Чтение головы
    string get_last();  // Чтение хвоста
};
