// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

struct Kereta {
    int noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int harga;
};

void tukarData(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampilkanSemuaJadwal(Kereta* arr, int count) {
    cout << "\n=== JADWAL KERETA API ===" << endl;
    cout << left << setw(10) << "No" 
        << setw(20) << "Nama Kereta" 
        << setw(15) << "Asal" 
        << setw(15) << "Tujuan" 
        << setw(10) << "Harga" << endl;
    cout << "------------------------------------------------------------" << endl;

    if (count == 0) {
        cout << "Belum ada data kereta." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        cout << left << setw(10) << (arr + i)->noKereta
            << setw(20) << (arr + i)->namaKereta
            << setw(15) << (arr + i)->asal
            << setw(15) << (arr + i)->tujuan
            << setw(10) << (arr + i)->harga << endl;
    }
}

void inputKeretaBaru(Kereta*& arr, int& count, int maxData) {
    if (count >= maxData) {
        cout << "Penyimpanan penuh!" << endl;
        return;
    }

    cout << "\n--- Tambah Data Kereta Baru ---" << endl;
    Kereta* newData = arr + count; 

    cout << "Nomor Kereta: ";
    cin >> newData->noKereta;
    cin.ignore();
    cout << "Nama Kereta: ";
    getline(cin, newData->namaKereta);
    cout << "Asal: ";
    getline(cin, newData->asal);
    cout << "Tujuan: ";
    getline(cin, newData->tujuan);
    cout << "Harga Tiket: ";
    cin >> newData->harga;

    count++;
}

void cariBerdasarkanRute(Kereta* arr, int count, string cariAsal, string cariTujuan) { // Menggunakan Linear Search
    cout << "\n--- Pencarian Rute: " << cariAsal << " - " << cariTujuan << " ---" << endl;
    bool found = false;

        // Iterasi ke-i: Loop berjalan pada indeks ke-i
        // Langkah 1: Akses elemen array menggunakan pointer arithmetic (arr + i)
        // Langkah 2: Ambil field 'asal' dari pointer (arr + i)->asal
        // Langkah 3: Ambil field 'tujuan' dari pointer (arr + i)->tujuan
        // Langkah 4: Bandingkan nilai field dengan kata kunci pencarian
    for (int i = 0; i < count; i++) {
        if ((arr + i)->asal == cariAsal && (arr + i)->tujuan == cariTujuan) {
            cout << ">> DITEMUKAN pada indeks " << i << "!" << endl;
            cout << "   Detail: " << (arr + i)->namaKereta 
                << " | Harga: " << (arr + i)->harga << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Rute tidak ditemukan." << endl;
    }
}

void urutkanBerdasarkanID(Kereta* arr, int count) { // Menggunakan Selection Sort
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++) {
            if ((arr + j)->noKereta < (arr + minIdx)->noKereta) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            tukarData(&arr[i], &arr[minIdx]);
        }
    }
}

void cariBerdasarkanNomor(Kereta* arr, int count, int targetID) { // Menggunakan Jump Search
    urutkanBerdasarkanID(arr, count);

    cout << "\n--- Pencarian Nomor Kereta: " << targetID << " ---" << endl;
    
    int step = static_cast<int>(sqrt(count));
    int prev = 0;

    while (prev < count && (arr + min(step, count) - 1)->noKereta < targetID) {
        prev = step;
        step += static_cast<int>(sqrt(count));
        if (prev >= count) break;
    }

    while (prev < min(step, count)) {
        if ((arr + prev)->noKereta == targetID) {
            cout << ">> DITEMUKAN! " << (arr + prev)->namaKereta 
                << " | Harga: " << (arr + prev)->harga << endl;
            return;
        }
        prev++;
    }

    cout << "Nomor kereta tidak ditemukan." << endl;
}

void gabungData(Kereta* arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);
    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].namaKereta <= R[j].namaKereta) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++; k++;
    }
    while (j < n2) {
        *(arr + k) = R[j];
        j++; k++;
    }

    delete[] L;
    delete[] R;
}

void urutkanBerdasarkanNama(Kereta* arr, int l, int r) { // Menggunakan Merge Sort
    if (l < r) {
        int m = l + (r - l) / 2;
        urutkanBerdasarkanNama(arr, l, m);
        urutkanBerdasarkanNama(arr, m + 1, r);
        gabungData(arr, l, m, r);
    }
}

void urutkanBerdasarkanHarga(Kereta* arr, int count) { // Menggunakan Selection Sort
    cout << "\n--- Mengurutkan Data (Harga Termurah) ---" << endl;
    for (int i = 0; i < count - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < count; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            tukarData(&arr[i], &arr[minIdx]);
        }
    }
    cout << "Pengurutan selesai." << endl;
}

int main() {
    const int MAX_DATA = 100;
    Kereta* dataKereta = new Kereta[MAX_DATA]; 
    int jumlahData = 0;
    int pilihan;

    dataKereta[0] = {101, "Argo Bromo", "Surabaya", "Jakarta", 500000};
    dataKereta[1] = {102, "Taksaka", "Yogyakarta", "Jakarta", 450000};
    dataKereta[2] = {103, "Gajayana", "Malang", "Jakarta", 550000};
    jumlahData = 3;

    do {
        system("cls");
        cout << "\n========================================" << endl;
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN KERETA " << endl;
        cout << "========================================" << endl;
        cout << "1. Tampilkan Jadwal Semua Kereta" << endl;
        cout << "2. Tambah Data Kereta Baru" << endl;
        cout << "3. Cari Berdasarkan Rute" << endl;
        cout << "4. Cari Berdasarkan Nomor" << endl;
        cout << "5. Urutkan Nama Kereta" << endl;
        cout << "6. Urutkan Harga Tiket" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            case 2:
                inputKeretaBaru(dataKereta, jumlahData, MAX_DATA);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            case 3: {
                string asal, tujuan;
                cout << "Masukkan Asal: "; getline(cin, asal);
                cout << "Masukkan Tujuan: "; getline(cin, tujuan);
                cariBerdasarkanRute(dataKereta, jumlahData, asal, tujuan);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan Nomor Kereta: "; cin >> id;
                cin.ignore();
                cariBerdasarkanNomor(dataKereta, jumlahData, id);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            }
            case 5:
                urutkanBerdasarkanNama(dataKereta, 0, jumlahData - 1);
                cout << "Data berhasil diurutkan berdasarkan Nama (A-Z)." << endl;
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            case 6:
                urutkanBerdasarkanHarga(dataKereta, jumlahData);
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                cout << "\nTekan Enter untuk kembali...";
                cin.get();
        }
    } while (pilihan != 0);

    delete[] dataKereta;
    return 0;
}