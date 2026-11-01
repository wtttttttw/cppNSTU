#include "doublyList.h"
#include <iostream>

DoubleList::DoubleList() : head(nullptr), tail(nullptr) {}
DoubleList::~DoubleList() { create(); }

void DoubleList::create() {
    while (head) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

void DoubleList::push_front(string val) {
    Node* newNode = new Node(val);
    if (!head) { head = tail = newNode; return; }
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
}

void DoubleList::push_back(string val) {
    Node* newNode = new Node(val);
    if (!tail) { head = tail = newNode; return; }
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
}

void DoubleList::insert_after(string target, string val) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur) return;

    Node* newNode = new Node(val);
    newNode->next = cur->next;
    newNode->prev = cur;
    if (cur->next) cur->next->prev = newNode;
    else tail = newNode;
    cur->next = newNode;
}

void DoubleList::insert_before(string target, string val) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur) return;

    Node* newNode = new Node(val);
    newNode->prev = cur->prev;
    newNode->next = cur;
    if (cur->prev) cur->prev->next = newNode;
    else head = newNode;
    cur->prev = newNode;
}

void DoubleList::remove(string val) {
    Node* cur = head;
    while (cur) {
        if (cur->value == val) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;
            delete cur;
            return;
        }
        cur = cur->next;
    }
}

bool DoubleList::find(string val) {
    Node* cur = head;
    while (cur) {
        if (cur->value == val) return true;
        cur = cur->next;
    }
    return false;
}

void DoubleList::print() {
    Node* cur = head;
    if (!cur) { cout << "-> EMPTY" << endl; return; }
    cout << "-> ";
    while (cur) {
        cout << cur->value << " ";
        cur = cur->next;
    }
    cout << endl;
}
