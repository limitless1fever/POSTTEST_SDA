// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>

using namespace std;

int reverseArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    return 0;
}

void printArray(int* arr, int n) {
    int* ptr = arr;
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *ptr << " | Alamat: " << ptr << endl;
        ptr++;
    }
}

int main() {
    int ArrPrima[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "=== Sebelum Dibalik ===" << endl;
    printArray(ArrPrima, n);

    reverseArray(ArrPrima, n);

    cout << endl;
    cout << "=== Sesudah Dibalik ===" << endl;
    printArray(ArrPrima, n);

    return 0;
}