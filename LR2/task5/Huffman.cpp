#include "Huffman.h"
#include <iostream>

Huffman::Huffman() : root(nullptr) {}
Huffman::~Huffman() { destroyTree(root); }

void Huffman::destroyTree(HuffNode* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void Huffman::build(const string& text) {
    // 1. Подсчет частот
    int freq[256] = {0};
    for (size_t i = 0; i < text.size(); i++) {
        freq[(unsigned char)text[i]]++;
    }

    // 2. Создание списка свободных узлов в виде массива указателей
    int capacity = 256;
    HuffNode** nodes = new HuffNode*[capacity];
    int count = 0;
    
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            nodes[count++] = new HuffNode((char)i, freq[i]);
        }
    }

    // 3-6. Построение дерева Хаффмана
    while (count > 1) {
        // Ищем два минимальных узла
        int min1 = 0;
        int min2 = 1;
        if (nodes[0]->freq > nodes[1]->freq) {
            min1 = 1; min2 = 0;
        }

        for (int i = 2; i < count; i++) {
            if (nodes[i]->freq < nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->freq < nodes[min2]->freq) {
                min2 = i;
            }
        }

        // Создаем родителя
        HuffNode* parent = new HuffNode('\0', nodes[min1]->freq + nodes[min2]->freq);
        parent->left = nodes[min1];
        parent->right = nodes[min2];

        // Удаляем из массива два использованных узла (сначала с большим индексом)
        if (min1 > min2) {
            int temp = min1; min1 = min2; min2 = temp;
        }
        // Сдвигаем элементы массива, чтобы удалить min2 и min1
        for (int i = min2; i < count - 1; i++) nodes[i] = nodes[i + 1];
        count--;
        for (int i = min1; i < count - 1; i++) nodes[i] = nodes[i + 1];
        count--;

        // Добавляем нового родителя в конец
        nodes[count++] = parent;
    }

    if (count == 1) {
        root = nodes[0];
    }
    
    delete[] nodes;
}

void Huffman::buildCodes(HuffNode* node, string currentCode, MyArray& codes) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        // Формат строки: "символ:код"
        string entry = "";
        entry += node->ch;
        entry += ":";
        entry += currentCode;
        codes.push_back(entry);
        return;
    }
    
    buildCodes(node->left, currentCode + "0", codes);
    buildCodes(node->right, currentCode + "1", codes);
}

string Huffman::encode(const string& text, MyArray& codes) {
    buildCodes(root, "", codes);
    
    string result = "";
    for (size_t i = 0; i < text.size(); i++) {
        char c = text[i];
        for (int j = 0; j < codes.length(); j++) {
            string entry = codes.get(j);
            if (entry[0] == c) {
                result += entry.substr(2); // Отрезаем "c:"
                break;
            }
        }
    }
    return result;
}

string Huffman::decode(const string& encoded) {
    if (!root) return "";
    if (!root->left && !root->right) return string(encoded.length(), root->ch); // На случай одного символа
    
    string result = "";
    HuffNode* current = root;
    
    for (size_t i = 0; i < encoded.size(); i++) {
        if (encoded[i] == '0') current = current->left;
        else current = current->right;
        
        if (!current->left && !current->right) {
            result += current->ch;
            current = root;
        }
    }
    return result;
}

void Huffman::printCodes(MyArray& codes) {
    cout << "\nCode Table:" << endl;
    for (int i = 0; i < codes.length(); i++) {
        string entry = codes.get(i);
        char ch = entry[0];
        string code = entry.substr(2);
        cout << "'" << ch << "' : " << code << endl;
    }
}
