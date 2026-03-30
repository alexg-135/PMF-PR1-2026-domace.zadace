#include <iostream>
#include <string>

#include "Kosarica.h"

using namespace std;

int main(void) {
    Kosarica nova(10);
    
    nova.Dodaj(Artikl("Keksi Original", "012345", 2.15), 1);
    nova.Dodaj(Artikl("Keksi Original", "121111", 2.99), 2);
    nova.Dodaj(Artikl("Keksi Original", "012345", 2.15), 5);

    for(int i = 0; i < nova.ukupno; ++i) {
        cout << nova.artikli[i].naziv 
            << ", komada: "
            << nova.kolicine[i] << endl;
        cout << "\t cijena po komadu: "
            << nova.artikli[i].cijena
            << " EUR"
            << endl;
    }

    cout << string(20,'-')
        << endl 
        << "Ukupna cijena: "
        << nova.Iznos()
        << " EUR"
        << endl;

    return 0;
}