// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>

using namespace std;

int tukarNilai(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return 1;
}

int main() {
    int x, y;

    cout << "Masukkan nilai pertama : ";
    cin >> x;
    cout << "Masukkan nilai kedua   : ";
    cin >> y;

    cout << "\nSebelum pertukaran:" << endl;
    cout << "Nilai x : " << x << endl;
    cout << "Nilai y : " << y << endl;

    tukarNilai(&x, &y);

    cout << "\nSesudah pertukaran:" << endl;
    cout << "Nilai x : " << x << endl;
    cout << "Nilai y : " << y << endl;

    return 0;
}