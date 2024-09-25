#include <iostream>
#include <string>

using namespace std;


struct Costume {
    int id;
    string name;
    string size;
    float price;
    int stock;
};


void createCostume(Costume* costumes, int* count) {
    Costume newCostume;
    newCostume.id = *count + 1;

    cout << "Masukkan nama costume: ";
    getline(cin >> ws, newCostume.name);

    cout << "Masukkan ukuran costume (S/M/L): ";
    cin >> newCostume.size;

    cout << "Masukkan harga sewa per hari: ";
    cin >> newCostume.price;

    cout << "Masukkan jumlah stock costume: ";
    cin >> newCostume.stock;

    costumes[*count] = newCostume;
    (*count)++;

    cout << "Costume berhasil ditambahkan!" << endl;
}


void readCostume(Costume* costumes, int count) {
    cout << "Daftar Costume:" << endl;
    for (int i = 0; i < count; i++) {
        cout << "ID: " << costumes[i].id << endl;
        cout << "Nama: " << costumes[i].name << endl;
        cout << "Ukuran: " << costumes[i].size << endl;
        cout << "Harga: " << costumes[i].price << endl;
        cout << "Stock: " << costumes[i].stock << endl << endl;
    }
}


void updateCostume(Costume* costumes, int count) {
    int id;
    cout << "Masukkan ID costume yang ingin diupdate: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (costumes[i].id == id) {
            cout << "Masukkan nama costume baru: ";
            getline(cin >> ws, costumes[i].name);

            cout << "Masukkan ukuran costume baru (S/M/L): ";
            cin >> costumes[i].size;

            cout << "Masukkan harga sewa baru: ";
            cin >> costumes[i].price;

            cout << "Masukkan stock costume baru: ";
            cin >> costumes[i].stock;

            cout << "Costume berhasil diupdate!" << endl;
            return;
        }
    }

    cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
}


void deleteCostume(Costume* costumes, int* count) {
    int id;
    cout << "Masukkan ID costume yang ingin dihapus: ";
    cin >> id;

    for (int i = 0; i < *count; i++) {
        if (costumes[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                costumes[j] = costumes[j + 1];
            }
            (*count)--;
            cout << "Costume berhasil dihapus!" << endl;
            return;
        }
    }

    cout << "Costume dengan ID " << id << " tidak ditemukan!" << endl;
}


int main() {
    int choice;
    Costume costumes[100];  
    int costumeCount = 0;   

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
                createCostume(costumes, &costumeCount);
                break;
            case 2:
                readCostume(costumes, costumeCount);
                break;
            case 3:
                updateCostume(costumes, costumeCount);
                break;
            case 4:
                deleteCostume(costumes, &costumeCount);
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
