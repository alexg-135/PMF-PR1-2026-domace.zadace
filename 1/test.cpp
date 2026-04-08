#include <iostream>
#include "Kosarica.h"

using namespace std;

void Ispisi(Kosarica k, string ime) {
    cout << "---- " << ime << " ----" << endl;
    for(int i = 0; i < k.ukupno; i++) {
        cout << k.artikli[i].naziv
             << " | barkod: " << k.artikli[i].barkod
             << " | kom: " << k.kolicine[i]
             << " | cijena: " << k.artikli[i].cijena
             << endl;
    }
    cout << "Ukupno artikala: " << k.ukupno << endl;
    double iznos = k.Iznos();
    cout << "Iznos: " << iznos << endl;
    cout << "----------------------" << endl;
}

int main() {

    // 🔹 1. Test default konstruktor
    Kosarica k1;
    
    cout << "Kapacitet (default): " << k1.kapacitet << endl;

    // 🔹 2. Dodavanje artikala
    k1.Dodaj(Artikl("Mlijeko", "111", 1.5), 2);
    k1.Dodaj(Artikl("Kruh", "222", 2.0), 3);

    // 🔹 3. Dodavanje ISTOG barkoda (treba povećati količinu)
    k1.Dodaj(Artikl("Mlijeko drugo ime", "111", 9.9), 5);

    Ispisi(k1, "k1 nakon dodavanja");

    // 🔹 4. Test realokacije (kapacitet se mora povećati)
    k1.Dodaj(Artikl("Jabuka", "333", 1.0), 1);
    k1.Dodaj(Artikl("Banana", "444", 1.2), 1);
    k1.Dodaj(Artikl("Sok", "555", 2.5), 1);

    Ispisi(k1, "k1 nakon realokacije");

    // 🔹 5. Copy konstruktor
    Kosarica k2(k1);
    Ispisi(k2, "k2 (kopija)");

    // 🔹 6. DEEP COPY test
    k1.Dodaj(Artikl("Cokolada", "666", 3.0), 2);

    cout << "Nakon promjene k1:" << endl;
    cout << "k1.ukupno = " << k1.ukupno << endl;
    cout << "k2.ukupno = " << k2.ukupno << endl;

    // 🔹 7. Uklanjanje postojećeg
    int rez1 = k1.Ukloni("111");
    cout << "Ukloni 111 (ocekuje 1): " << rez1 << endl;

    // 🔹 8. Uklanjanje nepostojećeg (edge case)
    int rez2 = k1.Ukloni("999");
    cout << "Ukloni 999 (ocekuje 0): " << rez2 << endl;

    Ispisi(k1, "k1 nakon uklanjanja");

    // 🔹 9. Test prazne košarice (edge case)
    Kosarica k3;
    cout << "Iznos prazne kosarice (0): " << k3.Iznos() << endl;

    // 🔹 10. Copy prazne košarice
    Kosarica k4(k3);
    cout << "k4.ukupno (0): " << k4.ukupno << endl;

    // 🔹 11. Dodavanje 0 komada (edge case)
    k1.Dodaj(Artikl("Test", "777", 5.0), 0);
    cout << "Dodano 0 komada (provjeri da se nista ne pokvari)" << endl;

    Ispisi(k1, "k1 final");

    return 0;
}