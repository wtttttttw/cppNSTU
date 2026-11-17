#pragma once
#include <string>
#include "array.h"

using namespace std;

struct HuffNode {
    char ch;
    int freq;
    HuffNode* left;
    HuffNode* right;
    
    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

class Huffman {
private:
    HuffNode* root;
    
    void destroyTree(HuffNode* node);
    void buildCodes(HuffNode* node, string currentCode, MyArray& codes);

public:
    Huffman();
    ~Huffman();
    
    void build(const string& text);
    string encode(const string& text, MyArray& codes);
    string decode(const string& encoded);
    void printCodes(MyArray& codes);
};
