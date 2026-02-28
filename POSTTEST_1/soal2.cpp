// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    Mahasiswa mhs[5];

    cout << "=== Input Data Mahasiswa ===" << endl;
    for (int i = 0; i < 5; i++) {
        cout << "Mahasiswa ke-" << (i + 1) << ":" << endl;
        
        cout << "Nama : ";
        getline(cin, mhs[i].nama);
        
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        
        cin.ignore();
        cout << endl;
    }

    int indeksTertinggi = 0;
    for (int i = 1; i < 5; i++) {
        if (mhs[i].ipk > mhs[indeksTertinggi].ipk) {
            indeksTertinggi = i;
        }
    }

    cout << "=== Mahasiswa dengan IPK Tertinggi ===" << endl;
    cout << "Nama : " << mhs[indeksTertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeksTertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeksTertinggi].ipk << endl;

    return 0;
}