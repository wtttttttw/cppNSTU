#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "array.h"
using namespace std;

// ---------- Утилиты ----------

// Перевод long long в string вручную (без to_string)
static string ll_to_str(long long v) {
    if (v == 0) return "0";
    bool neg = (v < 0);
    unsigned long long u = neg ? (unsigned long long)(-(v + 1)) + 1ULL
                               : (unsigned long long)v;
    char buf[32];
    int pos = 31;
    buf[pos] = '\0';
    while (u > 0) {
        buf[--pos] = (char)('0' + (u % 10));
        u /= 10;
    }
    if (neg) buf[--pos] = '-';
    return string(buf + pos);
}

// Парсинг строки в long long. ok = true, если строка целиком — целое.
static long long str_to_ll(const string& s, bool& ok) {
    if (s.empty()) { ok = false; return 0; }
    // убираем пробелы по краям
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

// Разбиение строки на токены по пробелам (ручное, без istringstream)
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

// ---------- Вывод ----------

static void print_array(MyArray& arr) {
    cout << "  Индексы: ";
    for (int i = 0; i < arr.length(); i++) {
        cout << i;
        if (i + 1 < arr.length()) cout << "  ";
    }
    cout << "\n  Значения: [";
    for (int i = 0; i < arr.length(); i++) {
        cout << arr.get(i);
        if (i + 1 < arr.length()) cout << ", ";
    }
    cout << "]\n";
}

// ---------- Основной алгоритм ----------

static int find_subarrays_with_sum(MyArray& arr, long long target, bool print) {
    int n = arr.length();
    int found = 0;

    for (int l = 0; l < n; l++) {
        long long sum = 0;
        for (int r = l; r < n; r++) {
            bool ok;
            long long v = str_to_ll(arr.get(r), ok);
            if (!ok) break;
            sum += v;
            if (sum == target) {
                found++;
                if (print) {
                    cout << "  [" << l << ".." << r << "] : [";
                    for (int k = l; k <= r; k++) {
                        cout << arr.get(k);
                        if (k < r) cout << ", ";
                    }
                    cout << "]\n";
                }
            }
        }
    }
    return found;
}

// ---------- Ввод ----------

static long long prompt_ll(const string& prompt) {
    while (true) {
        cout << prompt;
        cout.flush();
        string line;
        if (!getline(cin, line)) {
            cout << "\n(EOF — выход)\n";
            exit(0);
        }
        bool ok;
        long long v = str_to_ll(line, ok);
        if (ok) return v;
        cout << "  ! Ожидалось целое число.\n";
    }
}

static void input_array(MyArray& arr) {
    arr.create();
    while (true) {
        cout << "\nВведите элементы массива через пробел (Enter — закончить):\n> ";
        cout.flush();
        string line;
        if (!getline(cin, line)) {
            cout << "\n(EOF — выход)\n";
            exit(0);
        }

        // Разбиваем на токены (не больше 10000)
        static string tokens[10000];
        int n = split_tokens(line, tokens, 10000);
        if (n == 0) {
            cout << "  ! Введите хотя бы одно число.\n";
            continue;
        }

        // Проверяем все
        bool bad = false;
        for (int i = 0; i < n; i++) {
            bool ok;
            str_to_ll(tokens[i], ok);
            if (!ok) {
                cout << "  ! \"" << tokens[i] << "\" не является целым числом.\n";
                bad = true;
                break;
            }
        }
        if (bad) continue;

        // Заполняем
        for (int i = 0; i < n; i++) arr.push_back(tokens[i]);
        cout << "  Загружено " << n << " элемент(ов).\n";
        return;
    }
}

// ---------- Меню ----------

static void print_menu() {
    cout << "\n===== МЕНЮ =====\n"
         << "  1 — Показать массив\n"
         << "  2 — Найти подмассивы с заданной суммой\n"
         << "  3 — Ввести массив заново\n"
         << "  4 — Изменить элемент по индексу\n"
         << "  5 — Добавить элемент в конец\n"
         << "  6 — Удалить элемент по индексу\n"
         << "  0 — Выход\n"
         << "Выбор: ";
    cout.flush();
}

int main() {
    MyArray arr;
    arr.create();

    cout << "Лабораторная работа №2 — Задание 4, Вариант 2\n"
         << "«Поиск подмассива с заданной суммой»\n";

    input_array(arr);

    while (true) {
        print_menu();
        string choice_str;
        if (!getline(cin, choice_str)) {
            cout << "\n(EOF — выход)\n";
            return 0;
        }
        bool ok;
        long long choice = str_to_ll(choice_str, ok);
        if (!ok) { cout << "  ! Введите число от 0 до 6.\n"; continue; }

        switch (choice) {
            case 0:
                cout << "Выход.\n";
                return 0;

            case 1:
                cout << "\nТекущий массив:\n";
                print_array(arr);
                break;

            case 2: {
                if (arr.length() == 0) { cout << "  ! Массив пуст.\n"; break; }
                long long target = prompt_ll("\nВведите целевую сумму: ");
                cout << "\nМассив:\n";
                print_array(arr);
                cout << "Цель: " << target << "\n\n";
                int found = find_subarrays_with_sum(arr, target, true);
                cout << "\nИтого: ";
                if (found == 0)
                    cout << "подмассивов с суммой " << target << " не найдено.\n";
                else
                    cout << "найдено " << found << " подмассив(ов).\n";
                break;
            }

            case 3:
                arr.create();
                input_array(arr);
                break;

            case 4: {
                if (arr.length() == 0) { cout << "  ! Массив пуст.\n"; break; }
                print_array(arr);
                long long idx = prompt_ll("Индекс для изменения: ");
                if (idx < 0 || idx >= arr.length()) {
                    cout << "  ! Индекс вне [0.." << arr.length() - 1 << "].\n";
                    break;
                }
                long long val = prompt_ll("Новое значение: ");
                arr.set((int)idx, ll_to_str(val));
                cout << "  Готово.\n";
                break;
            }

            case 5: {
                long long val = prompt_ll("Значение для добавления: ");
                arr.push_back(ll_to_str(val));
                cout << "  Готово. Длина: " << arr.length() << "\n";
                break;
            }

            case 6: {
                if (arr.length() == 0) { cout << "  ! Массив пуст.\n"; break; }
                print_array(arr);
                long long idx = prompt_ll("Индекс для удаления: ");
                if (idx < 0 || idx >= arr.length()) {
                    cout << "  ! Индекс вне [0.." << arr.length() - 1 << "].\n";
                    break;
                }
                arr.remove_at((int)idx);
                cout << "  Готово. Длина: " << arr.length() << "\n";
                break;
            }

            default:
                cout << "  ! Нет такого пункта.\n";
        }
    }
}
