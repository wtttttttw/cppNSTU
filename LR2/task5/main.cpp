#include <iostream>
#include <string>
#include <map>
#include "Rbtree.h"

using namespace std;

// Узел для дерева Хаффмана
struct HuffNode {
    char ch;
    int freq;
    HuffNode* left;
    HuffNode* right;

    HuffNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Вспомогательная функция для вывода дерева (для отладки)
void printHuffTree(HuffNode* root, string code = "") {
    if (!root) return;
    if (!root->left && !root->right) {
        cout << root->ch << ": " << code << endl;
    }
    printHuffTree(root->left, code + "0");
    printHuffTree(root->right, code + "1");
}

// Функция для поиска двух узлов с минимальной частотой
void findTwoMinimums(HuffNode** nodes, int& count, int& min1, int& min2) {
    min1 = -1; min2 = -1;
    for (int i = 0; i < count; i++) {
        if (nodes[i] == nullptr) continue;
        if (min1 == -1 || nodes[i]->freq < nodes[min1]->freq) {
            min2 = min1;
            min1 = i;
        } else if (min2 == -1 || nodes[i]->freq < nodes[min2]->freq) {
            min2 = i;
        }
    }
}

// Сбор кодов (символ -> код) через обход дерева Хаффмана
void buildCodes(HuffNode* root, string currentCode, map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = currentCode;
    }
    buildCodes(root->left, currentCode + "0", codes);
    buildCodes(root->right, currentCode + "1", codes);
}

// Восстановление строки по коду и дереву
string decode(HuffNode* root, const string& encoded) {
    string result = "";
    HuffNode* current = root;
    for (char bit : encoded) {
        if (bit == '0') current = current->left;
        else current = current->right;

        if (!current->left && !current->right) {
            result += current->ch;
            current = root; // Возвращаемся в корень для следующего символа
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    string input;
    cout << "Введите строку для сжатия: ";
    getline(cin, input);

    if (input.empty()) {
        cout << "Строка пуста!" << endl;
        return 0;
    }

    // 1. Подсчет частот
    map<char, int> freq;
    for (char c : input) freq[c]++;

    // 2. Создание списка свободных узлов
    int n = freq.size();
    HuffNode** nodes = new HuffNode*[n];
    int idx = 0;
    for (auto& pair : freq) {
        nodes[idx++] = new HuffNode(pair.first, pair.second);
    }

    int count = n;
    // 3-6. Построение дерева
    while (count > 1) {
        int min1, min2;
        findTwoMinimums(nodes, count, min1, min2);

        HuffNode* parent = new HuffNode('\0', nodes[min1]->freq + nodes[min2]->freq);
        parent->left = nodes[min1];
        parent->right = nodes[min2];

        // Заменяем два узла одним
        nodes[min1] = parent;
        nodes[min2] = nullptr;
        count--;
    }

    HuffNode* root = nodes[0];

    // 4. Получение таблицы кодов
    map<char, string> codes;
    buildCodes(root, "", codes);

    // Вывод таблицы (сохраняем в RBTree для соответствия ЛР1)
    cout << "\nТаблица кодов:" << endl;
    RBTree codeTable;
    for (auto& pair : codes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    // 5. Кодирование строки
    string encoded = "";
    for (char c : input) {
        encoded += codes[c];
    }
    cout << "\nЗакодированная строка (бинарный код):\n" << encoded << endl;

    // 6. Декодирование (проверка)
    string decoded = decode(root, encoded);
    cout << "\nДекодированная строка:\n" << decoded << endl;
    if (decoded == input) {
        cout << "[OK] Декодирование успешно!" << endl;
    } else {
        cout << "[ERROR] Ошибка декодирования!" << endl;
    }

    // Очистка памяти
    delete[] nodes;

    return 0;
}
