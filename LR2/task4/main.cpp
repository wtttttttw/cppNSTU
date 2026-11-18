#include <iostream>
#include <string>
#include "array.h"
using namespace std;

static long long str_to_ll(const string& s, bool& ok) {
    if (s.empty()) { ok = false; return 0; }
    size_t b = 0, e = s.size();
    while (b < e && (s[b] == ' ' || s[b] == '\t' || s[b] == '\r')) b++;
    while (e > b && (s[e-1] == ' ' || s[e-1] == '\t' || s[e-1] == '\r')) e--;
    if (b == e) { ok = false; return 0; }

    bool neg = false;
    size_t i = b;
    if (s[i] == '+' || s[i] == '-') { neg = (s[i] == '-'); i++; }
    if (i == e) { ok = false; return 0; }

    long long v = 0;
    for (; i < e; i++) {
        if (s[i] < '0' || s[i] > '9') { ok = false; return 0; }
        v = v * 10 + (s[i] - '0');
    }
    ok = true;
    return neg ? -v : v;
}

static int split_tokens(const string& line, string* tokens, int max_tokens) {
    int count = 0;
    size_t i = 0, n = line.size();
    while (i < n && count < max_tokens) {
        while (i < n && (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')) i++;
        if (i >= n) break;
        size_t start = i;
        while (i < n && line[i] != ' ' && line[i] != '\t' && line[i] != '\r') i++;
        tokens[count++] = line.substr(start, i - start);
    }
    return count;
}

int main() {
    MyArray arr;
    arr.create();

    cout << "Введите элементы массива через пробел:\n> ";
    string line;
    getline(cin, line);

    static string tokens[10000];
    int n = split_tokens(line, tokens, 10000);
    
    for (int i = 0; i < n; i++) {
        arr.push_back(tokens[i]);
    }

    cout << "Введите целевую сумму:\n> ";
    string target_str;
    getline(cin, target_str);
    bool ok;
    long long target = str_to_ll(target_str, ok);

    cout << "\nМассив: [";
    for (int i = 0; i < arr.length(); i++) {
        cout << arr.get(i) << (i + 1 < arr.length() ? ", " : "");
    }
    cout << "], цель: " << target << "\n\n";
    cout << "Найденные подмассивы:\n";

    int found = 0;
    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l; r < n; r++) {
            bool is_ok;
            long long v = str_to_ll(arr.get(r), is_ok);
            if (!is_ok) break;
            sum += v;

            if (sum == target) {
                found++;
                cout << "  [" << l << ".." << r << "] : [";
                for (int k = l; k <= r; k++) {
                    cout << arr.get(k);
                    if (k < r) cout << ", ";
                }
                cout << "]\n";
            }
        }
    }

    if (found == 0) {
        cout << "  Не найдено.\n";
    } else {
        cout << "\nВсего найдено: " << found << "\n";
    }

    return 0;
}
