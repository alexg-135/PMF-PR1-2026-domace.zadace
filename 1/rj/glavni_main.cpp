#include <typeinfo>
#include <iostream>
#include <fstream>
#include "Kosarica.h"

using namespace std;

// pomocna funkcija za ispis podataka o kosarici:
// kapacitet, ukupno, svi artikli iz kosarice
void ispis_info(Kosarica &k, ofstream& out) {
	out << "Kapacitet: " << k.kapacitet << endl
		<< "Ukupno: " << k.ukupno << endl
		<< "Svi artikli u kosarici:" << endl;
	for(int i = 0; i < k.ukupno; ++i) {
		out << '\t' << k.artikli[i].naziv
			<< ", " << k.artikli[i].barkod
			<< ", " << k.artikli[i].cijena 
			<< " EUR (" << k.kolicine[i]
			<< " kom)" << endl;
	}
}

void main0(string in_file_name) //iz zadace
{   
	ofstream fout (in_file_name);

	Kosarica nova(10);
    
    nova.Dodaj(Artikl("Keksi Original", "012345", 2.15), 1);
    nova.Dodaj(Artikl("Keksi Original", "121111", 2.99), 2);
    nova.Dodaj(Artikl("Keksi Original", "012345", 2.15), 5);

    for(int i = 0; i < nova.ukupno; ++i) {
        fout << nova.artikli[i].naziv 
            << ", komada: "
            << nova.kolicine[i] << endl;
        fout << "\t cijena po komadu: "
            << nova.artikli[i].cijena
            << " EUR"
            << endl;
    }

    fout << string(20,'-')
        << endl 
        << "Ukupna cijena: "
        << nova.Iznos()
        << " EUR"
        << endl;

	fout.close();
}

// sljedeci main provjerava ispravnu alokaciju i 
// realokaciju niza artikala u kosarici pri dodavanju
// novih artikala u kosaricu
void main1(string in_file_name)
{
	ofstream fout (in_file_name);

    Kosarica nova(3);
	fout << "---Kosarica prije dodavanja elemenata---" 
		<< endl;
	ispis_info(nova, fout);

	nova.Dodaj(Artikl("prvi","123",2),2);
	nova.Dodaj(Artikl("drugi","234",3.1),1);
	nova.Dodaj(Artikl("prvi","125",4.2),2);
	nova.Dodaj(Artikl("prvi","125",4.2),3);

	fout << "---Nakon dodavanja 3 razlicita artikla---" 
		<< endl;
	ispis_info(nova, fout);

	nova.Dodaj(Artikl("drugi","235",3.1),1);

	fout << "---Nakon dodavanja jos jednog---" 
		<< endl;
	ispis_info(nova, fout);

	fout.close();
}

// sljedeci main provjerava uklanjanje artikala iz kosarice
void main2(string in_file_name)
{
    ofstream fout (in_file_name);

	Artikl a("kruh", "132", 2.4),
		b("salata", "abc", 0.99),
		c;
	Kosarica k;

	k.Dodaj(a,3);
	k.Dodaj(b,4);
	k.Dodaj(c,2);

	fout << "---Nakon dodavanja 3 razlicita artikla---" 
		<< endl;
	ispis_info(k, fout);

	k.Ukloni("def"); // nema takvog artikla u kosarici

	fout << "---Nakon uklanjanja nepostojeceg artikla---" 
		<< endl;
	ispis_info(k, fout);

	k.Ukloni("132");

	fout << "---Nakon uklanjanja postojeceg artikla---" 
		<< endl;
	ispis_info(k, fout);

	fout.close();
}

// sljedeci main provjerava kontrolu kopiranja:
// pomocna funkcija za provjeru kopiranja kosarice
// u funkciji main3
void funkcija(Kosarica kopija, ofstream& out) {
	kopija.Dodaj(Artikl("treci","12",1.123),3);
	out << "---Podaci o kopiji nakon dodavanja artikla---" 
		<< endl;
	ispis_info(kopija, out);
	out << "Ukupna cijena kopije: "
		<< kopija.Iznos() << " EUR" << endl;
}

void main3(string in_file_name)
{
    ofstream fout (in_file_name);

	Kosarica original(10);
	original.Dodaj(Artikl("jedan","123",2.05),5);
	original.Dodaj(Artikl("drugi","1234",100),6);
	
	fout << "---Podaci o originalnoj kosarici---" 
		<< endl;
	ispis_info(original, fout);

	funkcija(original, fout);

	fout << "---Originalna kosarica nakon poziva funkcije---" 
		<< endl;
	ispis_info(original, fout);

	fout.close();
}


// sljedeci main provjerava povratne vrijednosti
// Dodaj i Ukloni funkcija
void main4(string in_file_name)
{
    ofstream fout (in_file_name);

	Kosarica k(5);
	fout << k.Dodaj(Artikl("banana", "1", 1.49), 2) << endl
		<< k.Dodaj(Artikl("neki", "1", 1.4), 3) << endl
		<< k.Dodaj(Artikl(), 1000) << endl
		<< k.Ukloni("312") << endl
		<< k.Ukloni("1") << endl 
		<< k.Ukloni("1") << endl;

	fout.close();
}

// sljedeci main provjerava jednostavno uklanjanje i dodavanje
// artikala (bez kopija, povratnih vrijednosti, mijenjanja
// kapaciteta i sl.)
void main5(string in_file_name)
{
    ofstream fout (in_file_name);

	Kosarica k(5);
	k.Dodaj(Artikl("prvi","1",2.3), 2);
	k.Dodaj(Artikl("treci","2",1.5), 1);
	k.Dodaj(Artikl("drugi","3",2.05), 5);
	k.Ukloni("3");

	fout << "---Ispis podataka o kosarici---" 
		<< endl;
	ispis_info(k, fout);
	fout << "Ukupna cijena kosarice: "
		<< k.Iznos() << " EUR" << endl;

	fout.close();
}

int main(int argc, char **argv) {
	int i;
	if (argc != 2) {
		printf("Pogrešan broj argumenata\n");
		return 0;
	}	
	i = atoi(argv[1]);
	switch (i) {
		case 1:
			main0("izlaz1.out");
			break;
		case 2:
			main1("izlaz2.out");
			break;
		case 3:
			main2("izlaz3.out");
			break;
		case 4:
			main3("izlaz4.out");
			break;
		case 5:
			main4("izlaz5.out");
			break;
		case 6:
			main5("izlaz6.out");
			break;
	}
	return 0;
}