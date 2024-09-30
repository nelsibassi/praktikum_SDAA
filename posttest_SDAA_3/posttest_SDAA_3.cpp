#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct ItemToko {
    string namaItem;
    string kategoriItem;
    int stokItem;
    double hargaItem;
};

struct NodeInventaris {
    ItemToko produk;
    NodeInventaris* nextNode;
};

void tambahItem(NodeInventaris** headInventaris);
void tampilkanItem(NodeInventaris* headInventaris);
void ubahItem(NodeInventaris* headInventaris);
void hapusItem(NodeInventaris** headInventaris);
NodeInventaris* cariItem(NodeInventaris* headInventaris, const string& nama);
void hapusSemuaItem(NodeInventaris** headInventaris);
void cariItemBerdasarkanKategori(NodeInventaris* headInventaris);

int main() {
    NodeInventaris* daftarItem = NULL;  
    int pilihan;  

    do {
        cout << "\n=== Menu Pengelolaan Inventaris ===\n";
        cout << "1. Tambah Item\n";
        cout << "2. Tampilkan Item\n";
        cout << "3. Ubah Item\n";
        cout << "4. Hapus Item\n";
        cout << "5. Cari Item Berdasarkan Kategori\n";
        cout << "6. Keluar\n";
        cout << "Pilihan: ";
        while (!(cin >> pilihan)) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "Input tidak valid, silakan masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        switch (pilihan) {
            case 1:
                tambahItem(&daftarItem);
                break;
            case 2:
                tampilkanItem(daftarItem);
                break;
            case 3:
                ubahItem(daftarItem);
                break;
            case 4:
                hapusItem(&daftarItem);
                break;
            case 5:
                cariItemBerdasarkanKategori(daftarItem);
                break;
            case 6:
                hapusSemuaItem(&daftarItem);
                cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);

    return 0;
}

void tambahItem(NodeInventaris** headInventaris) {
    string namaItem;
    cout << "\n=== Tambah Item Baru ===\n";
    cout << "Nama Item: ";
    getline(cin, namaItem);

    NodeInventaris* itemDitemukan = cariItem(*headInventaris, namaItem);
    if (itemDitemukan) {
        cout << "Item dengan nama '" << namaItem << "' sudah ada. Silakan ubah item tersebut jika perlu.\n";
        return;
    }

    NodeInventaris* nodeBaru = new NodeInventaris;
    nodeBaru->produk.namaItem = namaItem; 

    cout << "Kategori Item: ";
    getline(cin, nodeBaru->produk.kategoriItem);  
    cout << "Jumlah Stok: ";
    while (!(cin >> nodeBaru->produk.stokItem) || nodeBaru->produk.stokItem < 0) {  
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
        cout << "Input tidak valid, masukkan stok yang benar: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  

    cout << "Harga Item: ";
    while (!(cin >> nodeBaru->produk.hargaItem) || nodeBaru->produk.hargaItem < 0) { 
        cin.clear();  
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Input tidak valid, masukkan harga yang benar: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  

    nodeBaru->nextNode = *headInventaris;  
    *headInventaris = nodeBaru;

    cout << "Item berhasil ditambahkan!\n";
}

void tampilkanItem(NodeInventaris* headInventaris) {
    cout << "\n=== Daftar Item ===\n";
    if (!headInventaris) {
        cout << "Tidak ada item dalam inventaris.\n";
    } else {
        int nomorItem = 1;
        NodeInventaris* temp = headInventaris;
        while (temp) {
            cout << "Item ke-" << nomorItem << ":\n";
            cout << "Nama: " << temp->produk.namaItem << endl;
            cout << "Kategori: " << temp->produk.kategoriItem << endl;
            cout << "Stok: " << temp->produk.stokItem << endl;
            cout << "Harga: " << temp->produk.hargaItem << endl;
            cout << "------------------------\n";
            temp = temp->nextNode;
            nomorItem++;
        }
    }
}

void ubahItem(NodeInventaris* headInventaris) {
    string namaItem;
    cout << "\n=== Ubah Item ===\n";
    cout << "Masukkan nama item yang ingin diubah: ";
    getline(cin, namaItem);

    NodeInventaris* itemDitemukan = cariItem(headInventaris, namaItem);

    if (itemDitemukan) {
        cout << "Masukkan data baru:\n";
        cout << "Jumlah Stok: ";
        while (!(cin >> itemDitemukan->produk.stokItem) || itemDitemukan->produk.stokItem < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid, masukkan stok yang benar: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Harga Item: ";
        while (!(cin >> itemDitemukan->produk.hargaItem) || itemDitemukan->produk.hargaItem < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid, masukkan harga yang benar: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Item berhasil diubah!\n";
    } else {
        cout << "Item tidak ditemukan.\n";
    }
}

void hapusItem(NodeInventaris** headInventaris) {
    string namaItem;
    cout << "\n=== Hapus Item ===\n";
    cout << "Masukkan nama item yang ingin dihapus: ";
    getline(cin, namaItem);

    NodeInventaris* temp = *headInventaris;
    NodeInventaris* prevNode = NULL;

    while (temp && temp->produk.namaItem != namaItem) {
        prevNode = temp;
        temp = temp->nextNode;
    }

    if (temp) {
        if (prevNode) {
            prevNode->nextNode = temp->nextNode;
        } else {
            *headInventaris = temp->nextNode;
        }
        delete temp;
        cout << "Item berhasil dihapus!\n";
    } else {
        cout << "Item tidak ditemukan.\n";
    }
}

NodeInventaris* cariItem(NodeInventaris* headInventaris, const string& namaItem) {
    while (headInventaris) {
        if (headInventaris->produk.namaItem == namaItem) {
            return headInventaris;
        }
        headInventaris = headInventaris->nextNode;
    }
    return NULL;
}

void cariItemBerdasarkanKategori(NodeInventaris* headInventaris) {
    string kategori;
    cout << "\n=== Cari Item Berdasarkan Kategori ===\n";
    cout << "Masukkan kategori yang dicari: ";
    getline(cin, kategori);

    NodeInventaris* temp = headInventaris;
    bool itemDitemukan = false;

    cout << "\n=== Daftar Item Kategori '" << kategori << "' ===\n";
    while (temp) {
        if (temp->produk.kategoriItem == kategori) {
            cout << "Nama: " << temp->produk.namaItem << endl;
            cout << "Stok: " << temp->produk.stokItem << endl;
            cout << "Harga: " << temp->produk.hargaItem << endl;
            cout << "------------------------\n";
            itemDitemukan = true;
        }
        temp = temp->nextNode;
    }
    
    if (!itemDitemukan) {
        cout << "Tidak ada item dalam kategori '" << kategori << "'.\n";
    }
}

void hapusSemuaItem(NodeInventaris** headInventaris) {
    NodeInventaris* current = *headInventaris;
    NodeInventaris* nextNode;

    while (current) {
        nextNode = current->nextNode;
        delete current;
        current = nextNode;
    }

    *headInventaris = NULL;  
}

