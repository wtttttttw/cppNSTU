#pragma once
#include <string>
using namespace std;

class RBTree {
private:
    enum Color { RED, BLACK };
    struct Node {
        string key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        Node(string k, Color c) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void fixInsert(Node* z);
    void fixDelete(Node* x);
    void rbTransplant(Node* u, Node* v);
    Node* minimum(Node* node);
    void destroyTree(Node* node);
    void savePreOrderHelper(Node* node, string& out);
    
    void preOrderHelper(Node* node);
    void inOrderHelper(Node* node);
    void postOrderHelper(Node* node);

public:
    RBTree();
    ~RBTree();

    void create();
    void insert(string key);
    bool find(string key);
    void remove(string key);
    void savePreOrder(string& out);
    
    void printPreOrder();
    void printInOrder();
    void printPostOrder();
};
