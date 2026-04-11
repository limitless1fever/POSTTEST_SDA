// Nama : Pirlo Syabila Hafuza
// NIM : 2509106008
// Kelas : A1

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cctype>

using namespace std;

struct Kereta {
    int noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int harga;
};

struct Transaksi {
    string namaPenumpang;
    int noKereta;
    string namaKereta;
    string asal;
    string tujuan;
    int harga;
};

// ========== FUNGSI BANTUAN ==========
string toLower(string str) {
    for (char &c : str) c = tolower(c);
    return str;
}

string formatHarga(int angka) {
    string s = to_string(angka), res;
    int count = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        if (count++ % 3 == 0 && i != s.length() - 1) res = "." + res;
        res = s[i] + res;
    }
    return res;
}

// ========== FUNGSI UTAMA (KERETA) ==========
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
        << setw(12) << "Harga" << endl;
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
            << setw(12) << formatHarga((arr + i)->harga) << endl;
    }
}

void inputKeretaBaru(Kereta*& arr, int& count, int maxData) {
    if (count >= maxData) {
        cout << "Penyimpanan penuh!" << endl;
        return;
    }

    cout << "\n--- Tambah Data Kereta Baru ---" << endl;
    Kereta* newData = arr + count; 

    bool duplikat;
    do {
        duplikat = false;
        cout << "Nomor Kereta: ";
        while (!(cin >> newData->noKereta)) {
            cout << "Input harus angka. Ulangi: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        for(int i=0; i<count; i++) {
            if((arr+i)->noKereta == newData->noKereta) {
                duplikat = true;
                cout << "Nomor sudah terdaftar, gunakan nomor lain.\n";
                break;
            }
        }
    } while(duplikat);
    cin.ignore(1000, '\n');

    cout << "Nama Kereta: "; getline(cin, newData->namaKereta);
    cout << "Asal: "; getline(cin, newData->asal);
    cout << "Tujuan: "; getline(cin, newData->tujuan);

    cout << "Harga Tiket: ";
    while (!(cin >> newData->harga) || newData->harga < 0) {
        cout << "Input tidak valid. Masukkan harga angka positif: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(1000, '\n');

    count++;
}

void cariBerdasarkanRute(Kereta* arr, int count, string cariAsal, string cariTujuan) { // Algoritma: Linear Search
    if (count == 0) {
        cout << "\n--- Pencarian Rute: " << cariAsal << " - " << cariTujuan << " ---" << endl;
        cout << "Belum ada data kereta untuk dicari." << endl;
        return;
    }
    if(cariAsal.empty() || cariTujuan.empty()) {
        cout << "Asal dan tujuan tidak boleh kosong." << endl;
        return;
    }

    cout << "\n--- Pencarian Rute: " << cariAsal << " - " << cariTujuan << " ---" << endl;
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (toLower((arr + i)->asal) == toLower(cariAsal) && 
            toLower((arr + i)->tujuan) == toLower(cariTujuan)) {
            cout << ">> DITEMUKAN pada indeks " << i << "!" << endl;
            cout << "   Detail: " << (arr + i)->namaKereta 
                << " | Harga: " << formatHarga((arr + i)->harga) << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Rute tidak ditemukan." << endl;
    }
}

void urutkanBerdasarkanID(Kereta* arr, int count) { // Algoritma: Selection Sort
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

void cariBerdasarkanNomor(Kereta* arr, int count, int targetID) { // Algoritma: Jump Search
    if (count == 0) {
        cout << "\n--- Pencarian Nomor Kereta: " << targetID << " ---" << endl;
        cout << "Belum ada data kereta untuk dicari." << endl;
        return;
    }
    if (targetID <= 0) {
        cout << "Nomor kereta tidak valid." << endl;
        return;
    }

    cout << "\n--- Pencarian Nomor Kereta: " << targetID << " ---" << endl;
    
    int step = static_cast<int>(sqrt(count));
    int prev = 0;
    int batas = (step < count ? step : count);

    while (prev < count && (arr + batas - 1)->noKereta < targetID) {
        prev = step;
        step += static_cast<int>(sqrt(count));
        batas = (step < count ? step : count);
        if (prev >= count) break;
    }

    while (prev < batas) {
        if ((arr + prev)->noKereta == targetID) {
            cout << ">> DITEMUKAN! " << (arr + prev)->namaKereta 
                << " | Harga: " << formatHarga((arr + prev)->harga) << endl;
            return;
        }
        prev++;
    }

    cout << "Nomor kereta tidak ditemukan." << endl;
}

void gabungData(Kereta* arr, int l, int m, int r) { // Algoritma: Merge Sort (Fungsi Penggabungan)
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

void urutkanBerdasarkanNama(Kereta* arr, int l, int r) { // Algoritma: Merge Sort
    if (l < r) {
        int m = l + (r - l) / 2;
        urutkanBerdasarkanNama(arr, l, m);
        urutkanBerdasarkanNama(arr, m + 1, r);
        gabungData(arr, l, m, r);
    }
}

void urutkanBerdasarkanHarga(Kereta* arr, int count) { // Algoritma: Selection Sort
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

// ========== FUNGSI QUEUE & STACK ==========
void enqueue(Transaksi* q, int& front, int& rear, int max, Transaksi data) {
    if (rear == max - 1) {
        cout << "Antrian penuh (Overflow)!" << endl;
        return;
    }
    if (front == -1) front = 0;
    rear++;
    *(q + rear) = data;
    cout << "Berhasil masuk antrian!" << endl;
}

Transaksi dequeue(Transaksi* q, int& front, int& rear) {
    Transaksi kosong; kosong.namaPenumpang = "-";
    if (front == -1 || front > rear) {
        cout << "Antrian kosong (Underflow)!" << endl;
        return kosong;
    }
    Transaksi data = *(q + front);
    // Pergeseran elemen menggunakan dereferensi pointer
    for (int i = front; i < rear; i++) {
        *(q + i) = *(q + i + 1);
    }
    rear--;
    if (rear < front) front = -1;
    return data;
}

void pushStack(Transaksi* s, int& top, int max, Transaksi data) {
    if (top == max - 1) {
        cout << "Riwayat penuh (Overflow)!" << endl;
        return;
    }
    top++;
    *(s + top) = data;
}

Transaksi popStack(Transaksi* s, int& top) {
    Transaksi kosong; kosong.namaPenumpang = "-";
    if (top == -1) {
        cout << "Riwayat kosong (Underflow)!" << endl;
        return kosong;
    }
    return *(s + top--);
}

void peekQueue(Transaksi* q, int front) {
    if (front == -1) { cout << "Antrian kosong." << endl; return; }
    cout << "Depan Antrian: " << (q + front)->namaPenumpang 
         << " | Kereta: " << (q + front)->namaKereta << endl;
}

void peekStack(Transaksi* s, int top) {
    if (top == -1) { cout << "Riwayat kosong." << endl; return; }
    cout << "Transaksi Terakhir: " << (s + top)->namaPenumpang 
         << " | Kereta: " << (s + top)->namaKereta << endl;
}

void tampilAntrian(Transaksi* q, int front, int rear) {
    cout << "\n=== ANTRIAN PEMBELIAN TIKET ===" << endl;
    if (front == -1 || front > rear) { cout << "Antrian kosong." << endl; return; }
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "Kereta" << setw(15) << "Rute" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = front; i <= rear; i++) {
        cout << left << setw(5) << i - front + 1
             << setw(20) << (q + i)->namaPenumpang
             << setw(15) << (q + i)->namaKereta
             << setw(15) << (q + i)->asal + "-" + (q + i)->tujuan << endl;
    }
}

void tampilRiwayat(Transaksi* s, int top) {
    cout << "\n=== RIWAYAT TRANSAKSI ===" << endl;
    if (top == -1) { cout << "Riwayat kosong." << endl; return; }
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "Kereta" << setw(12) << "Harga" << endl;
    cout << "-----------------------------------------------" << endl;
    for (int i = 0; i <= top; i++) {
        cout << left << setw(5) << i + 1
             << setw(20) << (s + i)->namaPenumpang
             << setw(15) << (s + i)->namaKereta
             << setw(12) << formatHarga((s + i)->harga) << endl;
    }
}

// ========== MAIN ==========
int main() {
    const int MAX_DATA = 100;
    Kereta* dataKereta = new Kereta[MAX_DATA]; 
    int jumlahData = 0;
    int pilihan;

    Transaksi antrian[MAX_DATA];
    int frontQ = -1, rearQ = -1;
    Transaksi riwayat[MAX_DATA];
    int topS = -1;

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
        cout << "7. Tambah ke Antrian (Enqueue)" << endl;
        cout << "8. Proses Antrian (Dequeue)" << endl;
        cout << "9. Tampil Semua Antrian" << endl;
        cout << "10. Tampil Semua Riwayat" << endl;
        cout << "11. Cek Depan & Terakhir (Peek)" << endl;
        cout << "12. Hapus Transaksi Terakhir (Pop)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih Menu: ";
        while (!(cin >> pilihan)) {
            cout << "Pilihan tidak valid. Masukkan angka: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(1000, '\n');

        switch (pilihan) {
            case 1:
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 2:
                inputKeretaBaru(dataKereta, jumlahData, MAX_DATA);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 3: {
                string asal, tujuan;
                cout << "Masukkan Asal: "; getline(cin, asal);
                cout << "Masukkan Tujuan: "; getline(cin, tujuan);
                cariBerdasarkanRute(dataKereta, jumlahData, asal, tujuan);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 4: {
                int id;
                cout << "Masukkan Nomor Kereta: "; 
                if (cin >> id) {
                    cin.ignore(1000, '\n');
                    urutkanBerdasarkanID(dataKereta, jumlahData);
                    cariBerdasarkanNomor(dataKereta, jumlahData, id);
                } else {
                    cin.clear(); cin.ignore(1000, '\n');
                    cout << "Input tidak valid." << endl;
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 5:
                urutkanBerdasarkanNama(dataKereta, 0, jumlahData - 1);
                cout << "Data berhasil diurutkan berdasarkan Nama (A-Z)." << endl;
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 6:
                urutkanBerdasarkanHarga(dataKereta, jumlahData);
                tampilkanSemuaJadwal(dataKereta, jumlahData);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 7: {
                Transaksi tiketBaru;
                cout << "\n--- Tambah ke Antrian (Enqueue) ---" << endl;
                cout << "Nama Penumpang: "; getline(cin, tiketBaru.namaPenumpang);
                int idKereta;
                cout << "Nomor Kereta: "; cin >> idKereta; cin.ignore();
                bool found = false;
                for(int i=0; i<jumlahData; i++) {
                    if(dataKereta[i].noKereta == idKereta) {
                        tiketBaru.noKereta = dataKereta[i].noKereta;
                        tiketBaru.namaKereta = dataKereta[i].namaKereta;
                        tiketBaru.asal = dataKereta[i].asal;
                        tiketBaru.tujuan = dataKereta[i].tujuan;
                        tiketBaru.harga = dataKereta[i].harga;
                        found = true; break;
                    }
                }
                if(!found) { cout << "Kereta tidak ditemukan!" << endl; }
                else { enqueue(antrian, frontQ, rearQ, MAX_DATA, tiketBaru); }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 8: {
                cout << "\n--- Proses Antrian (Dequeue) ---" << endl;
                if(frontQ == -1) { cout << "Antrian kosong (Underflow)!" << endl; }
                else {
                    Transaksi data = dequeue(antrian, frontQ, rearQ);
                    if(data.namaPenumpang != "-") {
                        cout << "Memproses: " << data.namaPenumpang << " | Rute: " << data.asal << " - " << data.tujuan << endl;
                        pushStack(riwayat, topS, MAX_DATA, data);
                        cout << "Tiket berhasil diproses & dicatat ke riwayat." << endl;
                    }
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 9:
                tampilAntrian(antrian, frontQ, rearQ);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 10:
                tampilRiwayat(riwayat, topS);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 11:
                cout << "\n--- Cek Depan & Terakhir (Peek) ---" << endl;
                peekQueue(antrian, frontQ);
                peekStack(riwayat, topS);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 12:
                cout << "\n--- Hapus Transaksi Terakhir (Pop) ---" << endl;
                if(topS == -1) { cout << "Riwayat kosong (Underflow)!" << endl; }
                else {
                    Transaksi data = popStack(riwayat, topS);
                    cout << "Transaksi " << data.namaPenumpang << " (" << data.namaKereta << ") dibatalkan." << endl;
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                cout << "\nTekan Enter untuk kembali..."; cin.get();
        }
    } while (pilihan != 0);

    delete[] dataKereta;
    return 0;
}