#include "linkedList.h"
#include <iostream>

ForwardList::ForwardList() : head(nullptr) {}
ForwardList::~ForwardList() { create(); }

void ForwardList::create() {
    while (head != nullptr) {
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }
}

void ForwardList::push_front(string val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

void ForwardList::push_back(string val) {
    Node* newNode = new Node(val);
    if (!head) { head = newNode; return; }
    Node* cur = head;
    while (cur->next) cur = cur->next;
    cur->next = newNode;
}

void ForwardList::insert_after(string target, string val) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (cur) {
        Node* newNode = new Node(val);
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

void ForwardList::insert_before(string target, string val) {
    if (!head) return;
    if (head->value == target) { push_front(val); return; }
    Node* cur = head;
    while (cur->next && cur->next->value != target) cur = cur->next;
    if (cur->next) {
        Node* newNode = new Node(val);
        newNode->next = cur->next;
        cur->next = newNode;
    }
}

void ForwardList::remove(string val) {
    if (!head) return;
    if (head->value == val) { pop_front(); return; }
    Node* cur = head;
    while (cur->next && cur->next->value != val) cur = cur->next;
    if (cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
}

void ForwardList::pop_front() {
    if (!head) return;
    Node* tmp = head;
    head = head->next;
    delete tmp;
}

void ForwardList::pop_back() {
    if (!head) return;
    if (!head->next) { delete head; head = nullptr; return; }
    Node* cur = head;
    while (cur->next->next) cur = cur->next;
    delete cur->next;
    cur->next = nullptr;
}

void ForwardList::remove_after(string target) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (cur && cur->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
}

void ForwardList::remove_before(string target) {
    if (!head || head->value == target) return;
    if (head->next && head->next->value == target) { pop_front(); return; }
    Node* cur = head;
    while (cur->next && cur->next->next && cur->next->next->value != target) cur = cur->next;
    if (cur->next && cur->next->next) {
        Node* tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
}

bool ForwardList::find(string val) {
    Node* cur = head;
    while (cur) {
        if (cur->value == val) return true;
        cur = cur->next;
    }
    return false;
}

void ForwardList::print() {
    Node* cur = head;
    if (!cur) { cout << "-> EMPTY" << endl; return; }
    cout << "-> ";
    while (cur) { cout << cur->value << " "; cur = cur->next; }
    cout << endl;
}

string ForwardList::get_first() { return head ? head->value : "EMPTY"; }

string ForwardList::get_last() {
    if (!head) return "EMPTY";
    Node* cur = head;
    while (cur->next) cur = cur->next;
    return cur->value;
}
