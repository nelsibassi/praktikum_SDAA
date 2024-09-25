#include <iostream>
#include <string>

using namespace std;

// Struct untuk menyimpan informasi barang
struct Barang {
    string nama;
    string kategori;
    int stok;
    double harga;
};

// Deklarasi fungsi
void tambahBarang(Barang *inventaris, int *jumlah);
void tampilkanBarang(const Barang *inventaris, int jumlah);
void ubahBarang(Barang *inventaris, int jumlah);
void hapusBarang(Barang *inventaris, int *jumlah);
int cariBarang(const Barang *inventaris, int jumlah, const string &nama);

int main() {
    const int MAX_BARANG = 100;  // Batas maksimal barang yang dapat disimpan
    Barang inventaris[MAX_BARANG];  // Array untuk menyimpan barang
    int jumlahBarang = 0;  // Jumlah barang yang ada saat ini
    int pilihan;  // Variabel untuk menyimpan pilihan menu

    do {
        // Menampilkan menu utama
        cout << "\n=== Pengelolaan Inventaris Toko Elektronik ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Tampilkan Barang\n";
        cout << "3. Ubah Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        while (!(cin >> pilihan)) {
            cin.clear();  // Membersihkan flag kesalahan
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Input tidak valid. Silakan masukkan angka: ";
        }
        cin.ignore();  // Mengabaikan karakter newline setelah input angka

        // Switch case untuk memilih fungsi sesuai input
        switch (pilihan) {
            case 1:
                tambahBarang(inventaris, &jumlahBarang);
                break;
            case 2:
                tampilkanBarang(inventaris, jumlahBarang);
                break;
            case 3:
                ubahBarang(inventaris, jumlahBarang);
                break;
            case 4:
                hapusBarang(inventaris, &jumlahBarang);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan program ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}

// Fungsi untuk menambah barang ke dalam inventaris
void tambahBarang(Barang *inventaris, int *jumlah) {
    if (*jumlah >= 100) {
        cout << "Inventaris penuh. Tidak dapat menambah barang baru.\n";
        return;
    }

    cout << "\n=== Tambah Barang ===\n";
    cout << "Nama Barang: ";
    getline(cin, inventaris[*jumlah].nama);
    cout << "Kategori Barang: ";
    getline(cin, inventaris[*jumlah].kategori);
    cout << "Stok Barang: ";
    while (!(cin >> inventaris[*jumlah].stok) || inventaris[*jumlah].stok < 0) {
        cin.clear();  // Membersihkan flag kesalahan
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan stok yang benar: ";
    }
    cout << "Harga Barang: ";
    while (!(cin >> inventaris[*jumlah].harga) || inventaris[*jumlah].harga < 0) {
        cin.clear();  // Membersihkan flag kesalahan
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid. Masukkan harga yang benar: ";
    }
    cin.ignore();  // Mengabaikan karakter newline setelah input

    (*jumlah)++;  // Menambah jumlah barang setelah berhasil ditambahkan
    cout << "Barang berhasil ditambahkan!\n";
}

// Prosedur untuk menampilkan semua barang yang ada di inventaris
void tampilkanBarang(const Barang *inventaris, int jumlah) {
    cout << "\n=== Daftar Barang ===\n";
    if (jumlah == 0) {
        cout << "Tidak ada barang dalam inventaris.\n";
    } else {
        for (int i = 0; i < jumlah; i++) {
            cout << "Barang ke-" << (i + 1) << ":\n";
            cout << "Nama: " << inventaris[i].nama << endl;
            cout << "Kategori: " << inventaris[i].kategori << endl;
            cout << "Stok: " << inventaris[i].stok << endl;
            cout << "Harga: " << inventaris[i].harga << endl;
            cout << "------------------------\n";
        }
    }
}

// Prosedur untuk mengubah data barang tertentu
void ubahBarang(Barang *inventaris, int jumlah) {
    string nama;
    cout << "\n=== Ubah Barang ===\n";
    cout << "Masukkan nama barang yang ingin diubah: ";
    getline(cin, nama);
    int index = cariBarang(inventaris, jumlah, nama);

    if (index != -1) {
        cout << "Masukkan data baru untuk barang ini:\n";
        cout << "Stok Barang: ";
        while (!(cin >> inventaris[index].stok) || inventaris[index].stok < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan stok yang benar: ";
        }
        cout << "Harga Barang: ";
        while (!(cin >> inventaris[index].harga) || inventaris[index].harga < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid. Masukkan harga yang benar: ";
        }
        cin.ignore();  // Mengabaikan karakter newline
        cout << "Data barang berhasil diubah!\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

// Prosedur untuk menghapus barang berdasarkan nama
void hapusBarang(Barang *inventaris, int *jumlah) {
    string nama;
    cout << "\n=== Hapus Barang ===\n";
    cout << "Masukkan nama barang yang ingin dihapus: ";
    getline(cin, nama);
    int index = cariBarang(inventaris, *jumlah, nama);

    if (index != -1) {
        for (int i = index; i < *jumlah - 1; i++) {
            inventaris[i] = inventaris[i + 1];
        }
        (*jumlah)--;  // Mengurangi jumlah barang setelah berhasil dihapus
        cout << "Barang berhasil dihapus!\n";
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}

// Fungsi untuk mencari barang berdasarkan nama dan mengembalikan indeksnya
int cariBarang(const Barang *inventaris, int jumlah, const string &nama) {
    for (int i = 0; i < jumlah; i++) {
        if (inventaris[i].nama == nama) {
            return i;  // Mengembalikan indeks barang jika ditemukan
        }
    }
    return -1;  // Mengembalikan -1 jika barang tidak ditemukan
}

