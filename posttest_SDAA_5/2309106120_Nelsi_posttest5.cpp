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
void cariItemBerdasarkanKategori(NodeInventaris* headInventaris);
void hapusSemuaItem(NodeInventaris** headInventaris);

// Stack functions
void pushStack(NodeInventaris** headInventaris, const ItemToko& produk);
void popStack(NodeInventaris** headInventaris);

// Queue functions
void enqueueQueue(NodeInventaris** headInventaris, const ItemToko& produk);
void dequeueQueue(NodeInventaris** headInventaris);

// Sorting functions
void mergeSort(NodeInventaris** headRef);  // Ascending (Merge Sort)
void quickSort(NodeInventaris** headRef);  // Descending (Quick Sort)

// Merge Sort Helper Functions
NodeInventaris* mergeSortedLists(NodeInventaris* a, NodeInventaris* b);
void splitList(NodeInventaris* source, NodeInventaris** frontRef, NodeInventaris** backRef);

// Quick Sort Helper Functions
NodeInventaris* partition(NodeInventaris* head, NodeInventaris* end, NodeInventaris** newHead, NodeInventaris** newEnd);
NodeInventaris* quickSortRecur(NodeInventaris* head, NodeInventaris* end);
NodeInventaris* getTail(NodeInventaris* cur);

int main() {
    NodeInventaris* daftarItem = NULL;
    int pilihan;

    do {
        cout << "\n=== Menu Pengelolaan Inventaris ===\n";
        cout << "1. Tambah Item (Push ke Stack)\n";
        cout << "2. Hapus Item (Pop dari Stack)\n";
        cout << "3. Tambah Item (Enqueue ke Queue)\n";
        cout << "4. Hapus Item (Dequeue dari Queue)\n";
        cout << "5. Tampilkan Semua Item (Urutkan Ascending dengan Merge Sort)\n";
        cout << "6. Tampilkan Semua Item (Urutkan Descending dengan Quick Sort)\n";
        cout << "7. Ubah Item\n";
        cout << "8. Cari Item Berdasarkan Kategori\n";
        cout << "9. Keluar\n";
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
            case 5: // Show all items (Ascending - Merge Sort)
                mergeSort(&daftarItem);
                tampilkanItem(daftarItem);
                break;
            case 6: // Show all items (Descending - Quick Sort)
                quickSort(&daftarItem);
                tampilkanItem(daftarItem);
                break;
            case 7: // Update item
                ubahItem(daftarItem);
                break;
            case 8: // Search items by category
                cariItemBerdasarkanKategori(daftarItem);
                break;
            case 9: // Exit
                hapusSemuaItem(&daftarItem);
                cout << "Terima kasih telah menggunakan aplikasi ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 9);

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

// Merge Sort Implementation (Ascending)
NodeInventaris* mergeSortedLists(NodeInventaris* a, NodeInventaris* b) {
    if (!a) return b;
    if (!b) return a;
    
    NodeInventaris* result = NULL;
    if (a->produk.namaItem < b->produk.namaItem) {
        result = a;
        result->nextNode = mergeSortedLists(a->nextNode, b);
    } else {
        result = b;
        result->nextNode = mergeSortedLists(a, b->nextNode);
    }
    return result;
}

void splitList(NodeInventaris* source, NodeInventaris** frontRef, NodeInventaris** backRef) {
    NodeInventaris* fast = source->nextNode;
    NodeInventaris* slow = source;
    
    while (fast) {
        fast = fast->nextNode;
        if (fast) {
            slow = slow->nextNode;
            fast = fast->nextNode;
        }
    }
    
    *frontRef = source;
    *backRef = slow->nextNode;
    slow->nextNode = NULL;
}

void mergeSort(NodeInventaris** headRef) {
    NodeInventaris* head = *headRef;
    if (!head || !head->nextNode) return;
    
    NodeInventaris* a;
    NodeInventaris* b;
    
    splitList(head, &a, &b);
    
    mergeSort(&a);
    mergeSort(&b);
    
    *headRef = mergeSortedLists(a, b);
}

// Quick Sort Implementation (Descending)
NodeInventaris* getTail(NodeInventaris* cur) {
    while (cur && cur->nextNode)
        cur = cur->nextNode;
    return cur;
}

NodeInventaris* partition(NodeInventaris* head, NodeInventaris* end, NodeInventaris** newHead, NodeInventaris** newEnd) {
    NodeInventaris* pivot = end;
    NodeInventaris* prev = NULL;
    NodeInventaris* cur = head;
    NodeInventaris* tail = pivot;
    
    while (cur != pivot) {
        if (cur->produk.namaItem > pivot->produk.namaItem) {
            if (!(*newHead)) *newHead = cur;
            
            prev = cur;
            cur = cur->nextNode;
        } else {
            if (prev) prev->nextNode = cur->nextNode;
            
            NodeInventaris* temp = cur->nextNode;
            cur->nextNode = NULL;
            tail->nextNode = cur;
            tail = cur;
            cur = temp;
        }
    }
    
    if (!(*newHead)) *newHead = pivot;
    *newEnd = tail;
    
    return pivot;
}

NodeInventaris* quickSortRecur(NodeInventaris* head, NodeInventaris* end) {
    if (!head || head == end) return head;
    
    NodeInventaris* newHead = NULL;
    NodeInventaris* newEnd = NULL;
    
    NodeInventaris* pivot = partition(head, end, &newHead, &newEnd);
    
    if (newHead != pivot) {
        NodeInventaris* temp = newHead;
        while (temp->nextNode != pivot) temp = temp->nextNode;
        temp->nextNode = NULL;
        
        newHead = quickSortRecur(newHead, temp);
        
        temp = getTail(newHead);
        temp->nextNode = pivot;
    }
    
    pivot->nextNode = quickSortRecur(pivot->nextNode, newEnd);
    
    return newHead;
}

void quickSort(NodeInventaris** headRef) {
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
}

// Tampilkan Semua Item di Inventaris
void tampilkanItem(NodeInventaris* headInventaris) {
    if (headInventaris == NULL) {
        cout << "Tidak ada item di dalam inventaris.\n";
        return;
    }
    cout << "\nDaftar Item dalam Inventaris:\n";
    while (headInventaris != NULL) {
        cout << "Nama: " << headInventaris->produk.namaItem
             << ", Kategori: " << headInventaris->produk.kategoriItem
             << ", Stok: " << headInventaris->produk.stokItem
             << ", Harga: " << headInventaris->produk.hargaItem << "\n";
        headInventaris = headInventaris->nextNode;
    }
}

// Ubah Item di Inventaris
void ubahItem(NodeInventaris* headInventaris) {
    string nama;
    cout << "Masukkan nama item yang ingin diubah: ";
    getline(cin, nama);
    
    while (headInventaris != NULL) {
        if (headInventaris->produk.namaItem == nama) {
            cout << "Item ditemukan. Masukkan data baru.\n";
            cout << "Nama Item: ";
            getline(cin, headInventaris->produk.namaItem);
            cout << "Kategori Item: ";
            getline(cin, headInventaris->produk.kategoriItem);
            cout << "Jumlah Stok: ";
            while (!(cin >> headInventaris->produk.stokItem) || headInventaris->produk.stokItem < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid, masukkan stok yang benar: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harga Item: ";
            while (!(cin >> headInventaris->produk.hargaItem) || headInventaris->produk.hargaItem < 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Input tidak valid, masukkan harga yang benar: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Item berhasil diubah!\n";
            return;
        }
        headInventaris = headInventaris->nextNode;
    }
    cout << "Item tidak ditemukan.\n";
}

// Cari Item Berdasarkan Kategori
void cariItemBerdasarkanKategori(NodeInventaris* headInventaris) {
    string kategori;
    cout << "Masukkan kategori item yang ingin dicari: ";
    getline(cin, kategori);
    
    bool ditemukan = false;
    while (headInventaris != NULL) {
        if (headInventaris->produk.kategoriItem == kategori) {
            cout << "Nama: " << headInventaris->produk.namaItem
                 << ", Stok: " << headInventaris->produk.stokItem
                 << ", Harga: " << headInventaris->produk.hargaItem << "\n";
            ditemukan = true;
        }
        headInventaris = headInventaris->nextNode;
    }
    if (!ditemukan) {
        cout << "Tidak ada item dengan kategori tersebut.\n";
    }
}

// Hapus Semua Item di Inventaris
void hapusSemuaItem(NodeInventaris** headInventaris) {
    NodeInventaris* current = *headInventaris;
    NodeInventaris* next;
    
    while (current != NULL) {
        next = current->nextNode;
        delete current;
        current = next;
    }
    
    *headInventaris = NULL;
    cout << "Semua item telah dihapus dari inventaris.\n";
}

