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
int costumeCount = 0;     


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

int main() {
    int choice;

    do {
        cout << "Menu Rental Costume:" << endl;
        cout << "1. Tambah Costume" << endl;
        cout << "2. Lihat Costume" << endl;
        cout << "3. Update Costume" << endl;
        cout << "4. Hapus Costume" << endl;
        cout << "5. Keluar" << endl;
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
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 5);

    return 0;
}
