#include <iostream>
using namespace std;

double hitungLuasSegitiga(double alas, double tinggi) {
    return 0.5 * alas * tinggi;
}

int main() {
    double alas, tinggi;

    
    cout << "Masukkan alas segitiga: ";
    cin >> alas;
    cout << "Masukkan tinggi segitiga: ";
    cin >> tinggi;

    double luas = hitungLuasSegitiga(alas, tinggi);

    cout << "Luas segitiga adalah: " << luas << endl;

    return 0;
}
