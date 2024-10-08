#include <iostream>
#include <string>

using namespace std;

struct Costume {
    int id;
    string name;
    string size;
    float price;
    int stock;
    Costume* next; 
};

Costume* head = nullptr;  
Costume* stackTop = nullptr;  
Costume* queueFront = nullptr;  
Costume* queueRear = nullptr;  
int costumeCount = 0;     

// Fungsi untuk membuat Costume baru (node linked list)
void createCostume() {
    Costume* newCostume = new Costume;
    newCostume->id = costumeCount + 1;

    cout << "Masukkan nama costume: ";
    getline(cin >> ws, newCostume->name);

    cout << "Masukkan ukuran costume (S/M/L): ";
    cin >> newCostume->size;

    cout << "Masukkan harga sewa per hari: ";
    cin >> newCostume->price;

    cout << "Masukkan jumlah stock costume: ";
    cin >> newCostume->stock;

    newCostume->next = nullptr;

    if (head == nullptr) {
        head = newCostume;  
    } else {
        Costume* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next; 
        }
        temp->next = newCostume;  
    }

    costumeCount++;
    cout << "Costume berhasil ditambahkan!" << endl;
}

// Fungsi untuk membaca semua Costume yang ada
void readCostume() {
    if (head == nullptr) {
        cout << "Belum ada kostum yang tersedia." << endl;
        return;
    }

    Costume* temp = head;
    cout << "Daftar Costume:" << endl;
    while (temp != nullptr) {
        cout << "ID: " << temp->id << endl;
        cout << "Nama: " << temp->name << endl;
        cout << "Ukuran: " << temp->size << endl;
        cout << "Harga: " << temp->price << endl;
        cout << "Stock: " << temp->stock << endl << endl;
        temp = temp->next;
    }
}

// Fungsi untuk update data Costume
void updateCostume() {
    if (head == nullptr) {
        cout << "Belum ada kostum yang tersedia." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID costume yang ingin diupdate: ";
    cin >> id;

    Costume* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            cout << "Masukkan nama costume baru: ";
            getline(cin >> ws, temp->name);

            cout << "Masukkan ukuran costume baru (S/M/L): ";
            cin >> temp->size;

            cout << "Masukkan harga sewa baru: ";
            cin >> temp->price;

            cout << "Masukkan stock costume baru: ";
            cin >> temp->stock;

            cout << "Costume berhasil diupdate!" << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
}

// Fungsi untuk menghapus Costume
void deleteCostume() {
    if (head == nullptr) {
        cout << "Belum ada kostum yang tersedia." << endl;
        return;
    }

    int id;
    cout << "Masukkan ID costume yang ingin dihapus: ";
    cin >> id;

    Costume* temp = head;
    Costume* prev = nullptr;

    if (temp != nullptr && temp->id == id) {
        head = temp->next; 
        delete temp;
        costumeCount--;
        cout << "Costume berhasil dihapus!" << endl;
        return;
    }

    while (temp != nullptr && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    prev->next = temp->next;
    delete temp;
    costumeCount--;

    cout << "Costume berhasil dihapus!" << endl;
}

// Fungsi untuk mencari Costume berdasarkan ID
Costume* findCostumeById(int id) {
    Costume* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// === Stack Implementation (LIFO) ===

// Fungsi push ke stack
void pushStack(int id) {
    Costume* costume = findCostumeById(id);
    if (costume == nullptr) {
        cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    Costume* newCostume = new Costume(*costume); // Salin data costume
    newCostume->next = stackTop;
    stackTop = newCostume;
    cout << "Costume berhasil ditambahkan ke Stack!" << endl;
}

// Fungsi pop dari stack
void popStack() {
    if (stackTop == nullptr) {
        cout << "Stack kosong." << endl;
        return;
    }

    Costume* temp = stackTop;
    stackTop = stackTop->next;
    cout << "Costume dengan ID " << temp->id << " berhasil diambil dari Stack!" << endl;
    delete temp;
}

// === Queue Implementation (FIFO) ===

// Fungsi enqueue ke Queue
void enqueueQueue(int id) {
    Costume* costume = findCostumeById(id);
    if (costume == nullptr) {
        cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
        return;
    }

    Costume* newCostume = new Costume(*costume); // Salin data costume
    newCostume->next = nullptr;
    if (queueRear == nullptr) {
        queueFront = queueRear = newCostume;
    } else {
        queueRear->next = newCostume;
        queueRear = newCostume;
    }
    cout << "Costume berhasil ditambahkan ke Queue!" << endl;
}

// Fungsi dequeue dari Queue
void dequeueQueue() {
    if (queueFront == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }

    Costume* temp = queueFront;
    queueFront = queueFront->next;

    if (queueFront == nullptr) {
        queueRear = nullptr;
    }

    cout << "Costume dengan ID " << temp->id << " berhasil diambil dari Queue!" << endl;
    delete temp;
}

int main() {
    int choice;

    do {
        cout << "Menu Rental Costume:" << endl;
        cout << "1. Tambah Costume" << endl;
        cout << "2. Lihat Costume" << endl;
        cout << "3. Update Costume" << endl;
        cout << "4. Hapus Costume" << endl;
        cout << "5. Push Costume ke Stack" << endl;
        cout << "6. Pop Costume dari Stack" << endl;
        cout << "7. Enqueue Costume ke Queue" << endl;
        cout << "8. Dequeue Costume dari Queue" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createCostume();
                break;
            case 2:
                readCostume();
                break;
            case 3:
                updateCostume();
                break;
            case 4:
                deleteCostume();
                break;
            case 5: {
                int id;
                cout << "Masukkan ID costume yang ingin di-push ke Stack: ";
                cin >> id;
                pushStack(id);
                break;
            }
            case 6:
                popStack();
                break;
            case 7: {
                int id;
                cout << "Masukkan ID costume yang ingin di-enqueue ke Queue: ";
                cin >> id;
                enqueueQueue(id);
                break;
            }
            case 8:
                dequeueQueue();
                break;
            case 9:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 9);

    return 0;
}
