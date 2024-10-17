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


Costume* merge(Costume* left, Costume* right, bool ascending) {
    if (!left) return right;
    if (!right) return left;

    if ((ascending && left->price < right->price) || (!ascending && left->price > right->price)) {
        left->next = merge(left->next, right, ascending);
        return left;
    } else {
        right->next = merge(left, right->next, ascending);
        return right;
    }
}

void split(Costume* source, Costume** front, Costume** back) {
    Costume* fast = source->next;
    Costume* slow = source;
    
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}


void mergeSort(Costume** headRef, bool ascending) {
    if (!*headRef || !(*headRef)->next) return;

    Costume* head = *headRef;
    Costume *left, *right;

    split(head, &left, &right);
    mergeSort(&left, ascending);
    mergeSort(&right, ascending);

    *headRef = merge(left, right, ascending);
}


Costume* partition(Costume* low, Costume* high, bool ascending) {
    float pivot = high->price;
    Costume* i = low->next;
    Costume* j = low;
    
    for (; j != high; j = j->next) {
        if ((ascending && j->price < pivot) || (!ascending && j->price > pivot)) {
            swap(i->price, j->price);
            swap(i->name, j->name);
            swap(i->size, j->size);
            swap(i->stock, j->stock);
            i = i->next;
        }
    }
    swap(i->price, high->price);
    return i;
}


void quickSort(Costume* low, Costume* high, bool ascending) {
    if (!high || low == high || low == high->next) return;

    Costume* pi = partition(low, high, ascending);
    quickSort(low, pi->next, ascending);
    quickSort(pi->next, high, ascending);
}

int main() {
    int choice;

    do {
        cout << "Menu Rental Costume:" << endl;
        cout << "1. Tambah Costume" << endl;
        cout << "2. Lihat Costume" << endl;
        cout << "3. Sorting Harga Ascending (Merge Sort)" << endl;
        cout << "4. Sorting Harga Descending (Quick Sort)" << endl;
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
                mergeSort(&head, true);
                cout << "Costume berhasil diurutkan secara ascending!" << endl;
                break;
            case 4:
                quickSort(head, nullptr, false); 
                cout << "Costume berhasil diurutkan secara descending!" << endl;
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
