#include <iostream>
#include <cstdlib>
#include <string>
#include "array.h"
using namespace std;

// Парсинг строки в long long.
// ok = true, если строка целиком является целым числом.
static long long parse_ll(const string& s, bool& ok) {
    if (s.empty()) { ok = false; return 0; }
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    ok = (end != nullptr && *end == '\0');
    return ok ? v : 0;
}

// Находит и выводит все подмассивы arr с суммой target.
// O(n^2) по времени, O(1) дополнительной памяти.
static void find_subarrays_with_sum(MyArray& arr, long long target) {
    int n = arr.length();
    int found = 0;

    for (int l = 0; l < n; l++) {
        long long sum = 0;

        for (int r = l; r < n; r++) {
            bool ok;
            long long v = parse_ll(arr.get(r), ok);
            if (!ok) break;   // нечисло — прерываем этот подмассив

            sum += v;

            if (sum == target) {
                found++;
                cout << "Подмассив [" << l << ".." << r << "]: [";
                for (int k = l; k <= r; k++) {
                    cout << arr.get(k);
                    if (k < r) cout << ", ";
                }
                cout << "]\n";
            }
        }
    }

    if (found == 0)
        cout << "Подмассивов с суммой " << target << " не найдено.\n";
    else
        cout << "Всего найдено: " << found << "\n";
}

// Заполнение MyArray целыми числами из C-массива
static void fill_array(MyArray& arr, const int* nums, int count) {
    arr.create();
    for (int i = 0; i < count; i++) {
        arr.push_back(to_string(nums[i]));
    }
}

static void print_array(MyArray& arr) {
    cout << "[";
    for (int i = 0; i < arr.length(); i++) {
        cout << arr.get(i);
        if (i + 1 < arr.length()) cout << ", ";
    }
    cout << "]";
}

int main() {
    MyArray arr;

    // Пример из задания
    int nums[] = {4, -7, 1, 5, -4, 0, -3, 2, 4, 1};
    int count = sizeof(nums) / sizeof(nums[0]);
    long long target = 5;

    fill_array(arr, nums, count);

    cout << "Массив: ";
    print_array(arr);
    cout << "\nЦель: " << target << "\n\n";

    find_subarrays_with_sum(arr, target);

    return 0;
}
