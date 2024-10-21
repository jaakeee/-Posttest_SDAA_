#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

#define NO_OF_CHARS 256

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


int fibonacciSearch(int arr[], int x, int n) {
    int fibM2 = 0;  
    int fibM1 = 1;   
    int fibM = fibM2 + fibM1;  

    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);

        if (arr[i] < x) {
            fibM = fibM1;
            fibM1 = fibM2;
            fibM2 = fibM - fibM1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibM2;
            fibM1 = fibM1 - fibM2;
            fibM2 = fibM - fibM1;
        } else {
            return i;
        }
    }

    if (fibM1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}


int jumpSearch(int arr[], int x, int n) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            return -1;
        }
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) {
            return -1;
        }
    }

    if (arr[prev] == x) {
        return prev;
    }

    return -1;
}


void badCharHeuristic(string str, int size, int badchar[NO_OF_CHARS]) {
    for (int i = 0; i < NO_OF_CHARS; i++) {
        badchar[i] = -1;
    }
    for (int i = 0; i < size; i++) {
        badchar[(int) str[i]] = i;
    }
}

int boyerMooreSearch(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();
    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;  
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j]) {
            j--;
        }

        if (j < 0) {
            return s;
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else {
            s += max(1, j - badchar[txt[s + j]]);
        }
    }

    return -1;
}


void searchCostumeByPrice(int price) {
    int* prices = new int[costumeCount];
    Costume* temp = head;
    for (int i = 0; i < costumeCount; i++) {
        prices[i] = temp->price;
        temp = temp->next;
    }

    int index = fibonacciSearch(prices, price, costumeCount);  
    if (index != -1) {
        cout << "Costume ditemukan dengan harga: " << price << endl;
    } else {
        cout << "Costume tidak ditemukan." << endl;
    }

    delete[] prices;
}


void searchCostumeByName(string name) {
    Costume* temp = head;
    while (temp != nullptr) {
        if (boyerMooreSearch(temp->name, name) != -1) {
            cout << "Costume ditemukan dengan nama: " << temp->name << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Costume tidak ditemukan." << endl;
}


int main() {
    int choice;

    do {
        cout << "Menu Rental Costume:" << endl;
        cout << "1. Tambah Costume" << endl;
        cout << "2. Lihat Costume" << endl;
        cout << "3. Sorting Harga Ascending (Merge Sort)" << endl;
        cout << "4. Sorting Harga Descending (Quick Sort)" << endl;
        cout << "5. Cari Costume Berdasarkan Harga (Fibonacci/Jump Search)" << endl;
        cout << "6. Cari Costume Berdasarkan Nama (Boyer-Moore Search)" << endl;
        cout << "7. Keluar" << endl;
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
                if (head == nullptr) {
                    cout << "Belum ada costume yang tersedia." << endl;
                } else {
                    Costume* temp = head;
                    while (temp->next != nullptr) {  // Cari costume terakhir untuk quicksort
                        temp = temp->next;
                    }
                    quickSort(head, temp, false);  // Descending
                    cout << "Costume berhasil diurutkan secara descending!" << endl;
                }
                break;
            case 5: {
                int price;
                cout << "Masukkan harga costume yang dicari: ";
                cin >> price;
                searchCostumeByPrice(price);
                break;
            }
            case 6: {
                string name;
                cout << "Masukkan nama costume yang dicari: ";
                getline(cin >> ws, name);
                searchCostumeByName(name);
                break;
            }
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (choice != 7);

    return 0;
}
       
