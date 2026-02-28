// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>

using namespace std;

int FindMin(int A[], int n) {
    int min = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
        }
    }
    return min;
}

int main() {
    int ArrFib[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;

    int nilaiMin = FindMin(ArrFib, n);

    int indeksMin = 0;
    for (int i = 0; i < 8; i++) {
        if (ArrFib[i] == nilaiMin) {
            indeksMin = i;
            break;
        }
    }

    cout << "Nilai Minimum : " << nilaiMin << endl;
    cout << "Indeks Minimum: " << indeksMin << endl;

    return 0;
}

// Analisis Algoritma:
// ---------------------------------------------------------------------------
// Pseudocode              Cost      Tmin               Tmax
// ---------------------------------------------------------------------------
// procedure FindMax       C1        1                  1
// max <- A[0]             C2        1                  1
// for i <- 1 to n-1       C3        n                  n
// if A[i] > max           C4        n-1                n-1
// max <- A[i]             C5        0                  n-1
// end if                  C6        n-1                n-1
// end for                 C7        n                  n
// return max              C8        1                  1
// end procedure           C9        1                  1
// ---------------------------------------------------------------------------
// Total Waktu (Tn)                  O(n)               O(n)
// ---------------------------------------------------------------------------

// Penjelasan Perhitungan Total Waktu T(n):

// 1. Best Case (Tmin)
//    Kondisi: Elemen pertama (A[0]) sudah merupakan nilai minimum 
//    misalnya Array Fibonacci [1, 1, 2, 3, 5, 8, 13, 21]

//    T(n) = C1 + C2 + C3(n) + C4(n-1) + 0 + C6(n-1) + C7(n) + C8 + C9

//    Uraian:
//    - C4(n-1) => C4n - C4
//    - C6(n-1) => C6n - C6

//    T(n) = (C3 + C4 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C6)
//    Jika setiap cost = 1:
//    T(n) = (1 + 1 + 1 + 1)n + (1 + 1 + 1 + 1 - 1 - 1)
//    T(n) = 4n + 2
//    Big-O => O(n)

// 2. Worst Case (Tmax)
//    Kondisi: Array terurut menurun (descending), setiap elemen lebih kecil dari elemen sebelumnya. 
//    Misalnya Array Fibonacci [21, 13, 8, 5, 3, 2, 1, 1] yang terurut secara descending

//    T(n) = C1 + C2 + C3(n) + C4(n-1) + C5(n-1) + C6(n-1) + C7(n) + C8 + C9

//    Uraian:
//    - C4(n-1) => C4n - C4
//    - C5(n-1) => C5n - C5
//    - C6(n-1) => C6n - C6

//    T(n) = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 + C8 + C9 - C4 - C5 - C6)
//    Jika setiap cost = 1:
//    T(n) = (1 + 1 + 1 + 1 + 1)n + (1 + 1 + 1 + 1 - 1 - 1 - 1)
//    T(n) = 5n + 1
//    Big-O => O(n)
