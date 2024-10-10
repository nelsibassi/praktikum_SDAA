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

// Function prototypes
void tampilkanItem(NodeInventaris* headInventaris);
void ubahItem(NodeInventaris* headInventaris);
void hapusItem(NodeInventaris** headInventaris);
void cariItemBerdasarkanKategori(NodeInventaris* headInventaris);
void hapusSemuaItem(NodeInventaris** headInventaris);

// Stack functions
void pushStack(NodeInventaris** headInventaris, const ItemToko& produk);
void popStack(NodeInventaris** headInventaris);

// Queue functions
void enqueueQueue(NodeInventaris** headInventaris, const ItemToko& produk);
void dequeueQueue(NodeInventaris** headInventaris);

int main() {
    NodeInventaris* daftarItem = NULL;
    int pilihan;

    do {
        cout << "\n=== Menu Pengelolaan Inventaris ===\n";
        cout << "1. Tambah Item (Push ke Stack)\n";
        cout << "2. Hapus Item (Pop dari Stack)\n";
        cout << "3. Tambah Item (Enqueue ke Queue)\n";
        cout << "4. Hapus Item (Dequeue dari Queue)\n";
        cout << "5. Tampilkan Semua Item\n";
        cout << "6. Ubah Item\n";
        cout << "7. Cari Item Berdasarkan Kategori\n";
        cout << "8. Keluar\n";
        cout << "Pilihan: ";
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid, silakan masukkan angka: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1: { // Push to Stack
                ItemToko produk;
                cout << "\nNama Item: ";
                getline(cin, produk.namaItem);
                cout << "Kategori Item: ";
                getline(cin, produk.kategoriItem);
                cout << "Jumlah Stok: ";
                while (!(cin >> produk.stokItem) || produk.stokItem < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid, masukkan stok yang benar: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Harga Item: ";
                while (!(cin >> produk.hargaItem) || produk.hargaItem < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid, masukkan harga yang benar: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pushStack(&daftarItem, produk);
                break;
            }
            case 2: // Pop from Stack
                popStack(&daftarItem);
                break;
            case 3: { // Enqueue to Queue
                ItemToko produk;
                cout << "\nNama Item: ";
                getline(cin, produk.namaItem);
                cout << "Kategori Item: ";
                getline(cin, produk.kategoriItem);
                cout << "Jumlah Stok: ";
                while (!(cin >> produk.stokItem) || produk.stokItem < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid, masukkan stok yang benar: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Harga Item: ";
                while (!(cin >> produk.hargaItem) || produk.hargaItem < 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Input tidak valid, masukkan harga yang benar: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                enqueueQueue(&daftarItem, produk);
                break;
            }
            case 4: // Dequeue from Queue
                dequeueQueue(&daftarItem);
                break;
            case 5: // Show all items
                tampilkanItem(daftarItem);
                break;
            case 6: // Update item
                ubahItem(daftarItem);
                break;
            case 7: // Search items by category
                cariItemBerdasarkanKategori(daftarItem);
                break;
            case 8: // Exit
                hapusSemuaItem(&daftarItem);
                cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    return 0;
}

// Implementasi Stack (Push dan Pop)
void pushStack(NodeInventaris** headInventaris, const ItemToko& produk) {
    NodeInventaris* newNode = new NodeInventaris;
    newNode->produk = produk;
    newNode->nextNode = *headInventaris;
    *headInventaris = newNode;
    cout << "Item berhasil ditambahkan ke Stack!\n";
}

void popStack(NodeInventaris** headInventaris) {
    if (*headInventaris == NULL) {
        cout << "Stack kosong!\n";
        return;
    }
    NodeInventaris* temp = *headInventaris;
    *headInventaris = (*headInventaris)->nextNode;
    cout << "Item '" << temp->produk.namaItem << "' berhasil dihapus dari Stack.\n";
    delete temp;
}

// Implementasi Queue (Enqueue dan Dequeue)
void enqueueQueue(NodeInventaris** headInventaris, const ItemToko& produk) {
    NodeInventaris* newNode = new NodeInventaris;
    newNode->produk = produk;
    newNode->nextNode = NULL;

    if (*headInventaris == NULL) {
        *headInventaris = newNode;
    } else {
        NodeInventaris* temp = *headInventaris;
        while (temp->nextNode != NULL) {
            temp = temp->nextNode;
        }
        temp->nextNode = newNode;
    }
    cout << "Item berhasil ditambahkan ke Queue!\n";
}

void dequeueQueue(NodeInventaris** headInventaris) {
    if (*headInventaris == NULL) {
        cout << "Queue kosong!\n";
        return;
    }
    NodeInventaris* temp = *headInventaris;
    *headInventaris = (*headInventaris)->nextNode;
    cout << "Item '" << temp->produk.namaItem << "' berhasil dihapus dari Queue.\n";
    delete temp;
}

// Implementasi fungsi lainnya
void tampilkanItem(NodeInventaris* headInventaris) {
    if (headInventaris == NULL) {
        cout << "Tidak ada item dalam inventaris.\n";
        return;
    }
    cout << "\n=== Daftar Item ===\n";
    while (headInventaris != NULL) {
        cout << "Nama Item: " << headInventaris->produk.namaItem << "\n";
        cout << "Kategori Item: " << headInventaris->produk.kategoriItem << "\n";
        cout << "Jumlah Stok: " << headInventaris->produk.stokItem << "\n";
        cout << "Harga Item: " << headInventaris->produk.hargaItem << "\n";
        headInventaris = headInventaris->nextNode;
        cout << "---------------------\n";
    }
}

void ubahItem(NodeInventaris* headInventaris) {
    string nama;
    cout << "Masukkan nama item yang ingin diubah: ";
    getline(cin, nama);
    
    NodeInventaris* temp = headInventaris;
    while (temp != NULL) {
        if (temp->produk.namaItem == nama) {
            cout << "Ubah Nama Item: ";
            getline(cin, temp->produk.namaItem);
            cout << "Ubah Kategori Item: ";
            getline(cin, temp->produk.kategoriItem);
            cout << "Ubah Jumlah Stok: ";
            cin >> temp->produk.stokItem;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ubah Harga Item: ";
            cin >> temp->produk.hargaItem;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Item berhasil diubah.\n";
            return;
        }
        temp = temp->nextNode;
    }
    cout << "Item tidak ditemukan.\n";
}

void cariItemBerdasarkanKategori(NodeInventaris* headInventaris) {
    string kategori;
    cout << "Masukkan kategori yang ingin dicari: ";
    getline(cin, kategori);
    
    NodeInventaris* temp = headInventaris;
    bool found = false;
    cout << "\n=== Daftar Item Berdasarkan Kategori: " << kategori << " ===\n";
    while (temp != NULL) {
        if (temp->produk.kategoriItem == kategori) {
            cout << "Nama Item: " << temp->produk.namaItem << "\n";
            cout << "Jumlah Stok: " << temp->produk.stokItem << "\n";
            cout << "Harga Item: " << temp->produk.hargaItem << "\n";
            found = true;
        }
        temp = temp->nextNode;
    }
    if (!found) {
        cout << "Tidak ada item ditemukan dalam kategori '" << kategori << "'.\n";
    }
}

void hapusSemuaItem(NodeInventaris** headInventaris) {
    NodeInventaris* current = *headInventaris;
    NodeInventaris* nextNode;
    while (current != NULL) {
        nextNode = current->nextNode;
        delete current;
        current = nextNode;
    }
    *headInventaris = NULL;
    cout << "Semua item berhasil dihapus dari inventaris.\n";
}

