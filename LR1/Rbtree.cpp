#include "Rbtree.h"
#include <iostream>

RBTree::RBTree() : root(nullptr) {}
RBTree::~RBTree() { destroyTree(root); }

void RBTree::create() { destroyTree(root); root = nullptr; }

void RBTree::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void RBTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RBTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    if (!x->parent) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RBTree::fixInsert(Node* z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { z = z->parent; rotateLeft(z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { z = z->parent; rotateRight(z); }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RBTree::insert(string key) {
    Node* z = new Node(key, RED);
    Node* y = nullptr;
    Node* x = root;
    int numKey = stoi(key); 
    
    while (x != nullptr) {
        y = x;
        int numX = stoi(x->key);
        if (numKey < numX) x = x->left;
        else if (numKey > numX) x = x->right;
        else { delete z; return; }
    }
    z->parent = y;
    if (!y) root = z;
    else if (numKey < stoi(y->key)) y->left = z;
    else y->right = z;
    fixInsert(z);
}

bool RBTree::find(string key) {
    Node* cur = root;
    int numKey = stoi(key);
    while (cur) {
        int numCur = stoi(cur->key);
        if (numCur == numKey) return true;
        if (numKey < numCur) cur = cur->left;
        else cur = cur->right;
    }
    return false;
}

RBTree::Node* RBTree::minimum(Node* node) {
    while (node->left) node = node->left;
    return node;
}

void RBTree::rbTransplant(Node* u, Node* v) {
    if (!u->parent) root = v;
    else if (u == u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if (v) v->parent = u->parent;
}

void RBTree::fixDelete(Node* x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color == BLACK) && (!w->right || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->right || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    w->color = RED;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right) w->right->color = BLACK;
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node* w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if ((!w->right || w->right->color == BLACK) && (!w->left || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (!w->left || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left) w->left->color = BLACK;
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}

// ИЗМЕНЕНО: Удаление с поиском как чисел
void RBTree::remove(string key) {
    int numKey = stoi(key);
    Node* z = root;
    while (z && stoi(z->key) != numKey) {
        if (numKey < stoi(z->key)) z = z->left;
        else z = z->right;
    }
    if (!z) return;

    Node* y = z;
    Node* x = nullptr;
    Color yOrigColor = y->color;

    if (!z->left) {
        x = z->right;
        rbTransplant(z, z->right);
    } else if (!z->right) {
        x = z->left;
        rbTransplant(z, z->left);
    } else {
        y = minimum(z->right);
        yOrigColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
        } else {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOrigColor == BLACK && x) fixDelete(x);
    else if (yOrigColor == BLACK && !x) { if (root) root->color = BLACK; }
}

void RBTree::savePreOrderHelper(Node* node, string& out) {
    if (!node) return;
    out += node->key + " " + (node->color == RED ? "R" : "B") + " ";
    savePreOrderHelper(node->left, out);
    savePreOrderHelper(node->right, out);
}

void RBTree::savePreOrder(string& out) { savePreOrderHelper(root, out); }

void RBTree::preOrderHelper(Node* node) {
    if (!node) return;
    cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
    preOrderHelper(node->left);
    preOrderHelper(node->right);
}

void RBTree::inOrderHelper(Node* node) {
    if (!node) return;
    inOrderHelper(node->left);
    cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
    inOrderHelper(node->right);
}

void RBTree::postOrderHelper(Node* node) {
    if (!node) return;
    postOrderHelper(node->left);
    postOrderHelper(node->right);
    cout << node->key << "(" << (node->color == RED ? "R" : "B") << ") ";
}

void RBTree::printPreOrder() {
    if (!root) { cout << "-> EMPTY" << endl; return; }
    cout << "-> PreOrder:  ";
    preOrderHelper(root);
    cout << endl;
}

void RBTree::printInOrder() {
    if (!root) { cout << "-> EMPTY" << endl; return; }
    cout << "-> InOrder:   ";
    inOrderHelper(root);
    cout << endl;
}

void RBTree::printPostOrder() {
    if (!root) { cout << "-> EMPTY" << endl; return; }
    cout << "-> PostOrder: ";
    postOrderHelper(root);
    cout << endl;
}
