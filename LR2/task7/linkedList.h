#pragma once
#include <string>
using namespace std;

class ForwardList {
private:
    struct Node {
        string value;
        Node* next;
        Node(string v) : value(v), next(nullptr) {}
    };
    Node* head;

public:
    ForwardList();
    ~ForwardList();

    void create();
    void push_front(string val);
    void push_back(string val);
    void insert_after(string target, string val);
    void insert_before(string target, string val);
    void remove(string val);
    void pop_front();
    void pop_back();
    void remove_after(string target);
    void remove_before(string target);
    bool find(string val);
    void print();
    string get_first();
    string get_last();
};
