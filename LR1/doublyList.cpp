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

void DoubleList::pop_front() {
    if (!head) return;
    Node* tmp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete tmp;
}

void DoubleList::pop_back() {
    if (!tail) return;
    Node* tmp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete tmp;
}

void DoubleList::remove_after(string target) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (cur && cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        if (tmp->next) tmp->next->prev = cur;
        else tail = cur;
        delete tmp;
    }
}

void DoubleList::remove_before(string target) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (cur && cur->prev) {
        Node* tmp = cur->prev;
        cur->prev = tmp->prev;
        if (tmp->prev) tmp->prev->next = cur;
        else head = cur;
        delete tmp;
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
    while (cur) { cout << cur->value << " "; cur = cur->next; }
    cout << endl;
}

string DoubleList::get_first() { return head ? head->value : "EMPTY"; }
string DoubleList::get_last() { return tail ? tail->value : "EMPTY"; }
