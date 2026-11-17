#include <iostream>
#include <string>
#include "Huffman.h"

using namespace std;

int main() {
    string input;
    cout << "Enter string to compress: ";
    getline(cin, input);

    if (input.empty()) {
        cout << "Error: string is empty!" << endl;
        return 0;
    }

    Huffman huffman;
    huffman.build(input);

    MyArray codes;
    string encoded = huffman.encode(input, codes);
    
    huffman.printCodes(codes);

    cout << "\nEncoded binary string:\n" << encoded << endl;

    string decoded = huffman.decode(encoded);
    cout << "\nDecoded string:\n" << decoded << endl;

    if (decoded == input) {
        cout << "[OK] Decoding successful!" << endl;
    } else {
        cout << "[ERROR] Decoding failed!" << endl;
    }

    return 0;
}
