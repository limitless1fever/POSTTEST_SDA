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

struct NodeTransaksi {
    Transaksi data;
    NodeTransaksi* next;
};

// Fungsi Bantuan
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

// Fungsi SOrting dan Searching
void tukarData(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tukarDataTransaksi(Transaksi* a, Transaksi* b) {
    Transaksi temp = *a;
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
        string line;
        while (true) {
            cout << "Nomor Kereta: ";
            getline(cin, line);
            if (line.empty()) { cout << "Input tidak boleh kosong." << endl; continue; }
            bool hanyaAngka = true;
            for (char c : line) if (!isdigit(c)) { hanyaAngka = false; break; }
            if (!hanyaAngka) { cout << "Input harus angka." << endl; continue; }
            newData->noKereta = stoi(line);
            break;
        }

        for(int i=0; i<count; i++) {
            if((arr+i)->noKereta == newData->noKereta) {
                duplikat = true;
                cout << "Nomor sudah terdaftar, gunakan nomor lain." << endl;
                break;
            }
        }
    } while(duplikat);

    cout << "Nama Kereta: "; getline(cin, newData->namaKereta);
    while(newData->namaKereta.empty()) { cout << "Input tidak boleh kosong. Nama Kereta: "; getline(cin, newData->namaKereta); }

    cout << "Asal: "; getline(cin, newData->asal);
    while(newData->asal.empty()) { cout << "Input tidak boleh kosong. Asal: "; getline(cin, newData->asal); }

    cout << "Tujuan: "; getline(cin, newData->tujuan);
    while(newData->tujuan.empty()) { cout << "Input tidak boleh kosong. Tujuan: "; getline(cin, newData->tujuan); }

    cout << "Harga Tiket: ";
    while (true) {
        string line;
        getline(cin, line);
        if (line.empty()) { cout << "Input tidak boleh kosong. Masukkan harga angka positif: "; continue; }
        bool hanyaAngka = true;
        for (char c : line) if (!isdigit(c)) { hanyaAngka = false; break; }
        if (!hanyaAngka || stoi(line) < 0) { cout << "Input tidak valid. Masukkan harga angka positif: "; continue; }
        newData->harga = stoi(line);
        break;
    }

    count++;
}

void cariBerdasarkanRute(Kereta* arr, int count, string cariAsal, string cariTujuan) {
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

void urutkanBerdasarkanID(Kereta* arr, int count) {
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

void cariBerdasarkanNomor(Kereta* arr, int count, int targetID) {
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

void urutkanBerdasarkanNama(Kereta* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        urutkanBerdasarkanNama(arr, l, m);
        urutkanBerdasarkanNama(arr, m + 1, r);
        gabungData(arr, l, m, r);
    }
}

void urutkanBerdasarkanHarga(Kereta* arr, int count) {
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

// Fungsi Queue dan Stack
void enqueue(NodeTransaksi*& front, NodeTransaksi*& rear, Transaksi data) {
    NodeTransaksi* newNode = new NodeTransaksi;
    newNode->data = data;
    newNode->next = nullptr;
    
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Berhasil masuk antrian!" << endl;
}

Transaksi dequeue(NodeTransaksi*& front, NodeTransaksi*& rear) {
    Transaksi kosong; 
    kosong.namaPenumpang = "-";
    kosong.noKereta = 0;
    kosong.harga = 0;
    
    if (front == nullptr) {
        cout << "Queue underflow" << endl;
        return kosong;
    }
    
    NodeTransaksi* temp = front;
    Transaksi data = temp->data;
    
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    delete temp;
    return data;
}

void pushStack(NodeTransaksi*& top, Transaksi data) {
    NodeTransaksi* newNode = new NodeTransaksi;
    newNode->data = data;
    newNode->next = top;
    top = newNode;
}

Transaksi popStack(NodeTransaksi*& top) {
    Transaksi kosong; 
    kosong.namaPenumpang = "-";
    kosong.noKereta = 0;
    kosong.harga = 0;
    
    if (top == nullptr) {
        cout << "Stack underflow" << endl;
        return kosong;
    }
    
    NodeTransaksi* temp = top;
    Transaksi data = temp->data;
    
    top = top->next;
    delete temp;
    
    return data;
}

void peekQueue(NodeTransaksi* front) {
    if (front == nullptr) { cout << "Antrian kosong." << endl; return; }
    cout << "Depan Antrian: " << front->data.namaPenumpang 
        << " | Kereta: " << front->data.namaKereta << endl;
}

void peekStack(NodeTransaksi* top) {
    if (top == nullptr) { cout << "Riwayat kosong." << endl; return; }
    cout << "Transaksi Terakhir: " << top->data.namaPenumpang 
        << " | Kereta: " << top->data.namaKereta << endl;
}

void tampilAntrian(NodeTransaksi* front) {
    cout << "\n=== ANTRIAN PEMBELIAN TIKET ===" << endl;
    if (front == nullptr) { cout << "Antrian kosong." << endl; return; }
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "Kereta" << setw(15) << "Rute" << endl;
    cout << "-----------------------------------------------" << endl;
    int no = 1;
    NodeTransaksi* current = front;
    while (current != nullptr) {
        cout << left << setw(5) << no++
            << setw(20) << current->data.namaPenumpang
            << setw(15) << current->data.namaKereta
            << setw(15) << current->data.asal + "-" + current->data.tujuan << endl;
        current = current->next;
    }
}

void tampilRiwayat(NodeTransaksi* top) {
    cout << "\n=== RIWAYAT TRANSAKSI ===" << endl;
    if (top == nullptr) { cout << "Riwayat kosong." << endl; return; }
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "Kereta" << setw(12) << "Harga" << endl;
    cout << "-----------------------------------------------" << endl;
    int no = 1;
    NodeTransaksi* current = top;
    while (current != nullptr) {
        cout << left << setw(5) << no++
        << setw(20) << current->data.namaPenumpang
        << setw(15) << current->data.namaKereta
        << setw(12) << formatHarga(current->data.harga) << endl;
        current = current->next;
    }
}

void hapusSemuaNode(NodeTransaksi*& head) {
    while (head != nullptr) {
        NodeTransaksi* temp = head;
        head = head->next;
        delete temp;
    }
}

// Fungsi Main
int main() {
    const int MAX_DATA = 100;
    Kereta* dataKereta = new Kereta[MAX_DATA]; 
    int jumlahData = 0;
    int pilihan;

    NodeTransaksi* frontQ = nullptr;
    NodeTransaksi* rearQ = nullptr;
    NodeTransaksi* topS = nullptr;

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
        cout << "7. Tambah ke Antrian" << endl;
        cout << "8. Proses Antrian" << endl;
        cout << "9. Tampil Semua Antrian" << endl;
        cout << "10. Tampil Semua Riwayat" << endl;
        cout << "11. Cek Depan & Terakhir" << endl;
        cout << "12. Hapus Transaksi Terakhir" << endl;
        cout << "0. Keluar" << endl;
        
        string line;
        while (true) {
            cout << "Pilih Menu: ";
            getline(cin, line);
            if (line.empty()) { cout << "Pilihan tidak valid. Masukkan angka: "; continue; }
            bool hanyaAngka = true;
            for (char c : line) if (!isdigit(c)) { hanyaAngka = false; break; }
            if (!hanyaAngka) { cout << "Pilihan tidak valid. Masukkan angka: "; continue; }
            pilihan = stoi(line);
            if (pilihan >= 0 && pilihan <= 12) break;
            cout << "Pilihan tidak valid. Masukkan angka: ";
        }

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
                while(asal.empty()) { cout << "Asal tidak boleh kosong. Masukkan Asal: "; getline(cin, asal); }
                cout << "Masukkan Tujuan: "; getline(cin, tujuan);
                while(tujuan.empty()) { cout << "Tujuan tidak boleh kosong. Masukkan Tujuan: "; getline(cin, tujuan); }
                
                cariBerdasarkanRute(dataKereta, jumlahData, asal, tujuan);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 4: {
                int id;
                while (true) {
                    cout << "Masukkan Nomor Kereta: ";
                    getline(cin, line);
                    if (line.empty()) { cout << "Input tidak boleh kosong." << endl; continue; }
                    bool hanyaAngka = true;
                    for (char c : line) if (!isdigit(c)) { hanyaAngka = false; break; }
                    if (!hanyaAngka) { cout << "Input harus angka." << endl; continue; }
                    id = stoi(line);
                    break;
                }
                urutkanBerdasarkanID(dataKereta, jumlahData);
                cariBerdasarkanNomor(dataKereta, jumlahData, id);
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
                cout << "\n--- Tambah ke Antrian ---" << endl;
                cout << "Nama Penumpang: "; 
                getline(cin, tiketBaru.namaPenumpang);
                if (tiketBaru.namaPenumpang.empty()) {
                    cout << "Nama penumpang tidak boleh kosong!" << endl;
                    cout << "\nTekan Enter untuk kembali..."; cin.get();
                    break;
                }
                
                int idKereta;
                while (true) {
                    cout << "Nomor Kereta: ";
                    getline(cin, line);
                    if (line.empty()) { cout << "Input tidak boleh kosong." << endl; continue; }
                    bool hanyaAngka = true;
                    for (char c : line) if (!isdigit(c)) { hanyaAngka = false; break; }
                    if (!hanyaAngka) { cout << "Input harus angka." << endl; continue; }
                    idKereta = stoi(line);
                    break;
                }

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
                else { enqueue(frontQ, rearQ, tiketBaru); }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 8: {
                cout << "\n--- Proses Antrian ---" << endl;
                Transaksi data = dequeue(frontQ, rearQ);
                if(data.namaPenumpang != "-") {
                    cout << "Memproses: " << data.namaPenumpang << " | Rute: " << data.asal << " - " << data.tujuan << endl;
                    pushStack(topS, data);
                    cout << "Tiket berhasil diproses & dicatat ke riwayat." << endl;
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 9:
                tampilAntrian(frontQ);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 10:
                tampilRiwayat(topS);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 11:
                cout << "\n--- Cek Depan & Terakhir ---" << endl;
                peekQueue(frontQ);
                peekStack(topS);
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            case 12: {
                cout << "\n--- Hapus Transaksi Terakhir ---" << endl;
                Transaksi data = popStack(topS);
                if(data.namaPenumpang != "-") {
                    cout << "Transaksi " << data.namaPenumpang << " (" << data.namaKereta << ") dibatalkan." << endl;
                }
                cout << "\nTekan Enter untuk kembali..."; cin.get();
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                cout << "\nTekan Enter untuk kembali..."; cin.get();
        }
    } while (pilihan != 0);

    delete[] dataKereta;
    hapusSemuaNode(frontQ);
    hapusSemuaNode(topS);
    return 0;
}