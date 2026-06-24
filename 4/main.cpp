#include <iostream>

#include "Jelovnik.h"

using namespace std;

int main(void) {
    Sastojak brasno("brasno", 500, "g"),
        voda("mlaka voda", 3, "dl"),
        ulje("ulje", 3, "zlica"),
        sol("sol", 2, "zlicica"),
        ocat("ocat", 1, "zlicica"),
        sir("svjezi kravlji sir", 500, "g"),
        vrhnje("kiselo vrhnje", 3, "zlica"),
        jaja("kokosja jaja", 3, "komad"),
        sol5("sol", 5, "g");

    Jelo strukli("Zapeceni strukli sa sirom");
	
	strukli += brasno + sol + voda + ulje + ocat + sir + vrhnje
		+ jaja + sol5;
	
	strukli *= 5;
	
	cout << "Za 5 osoba " << strukli << endl;
	
	cout << "Ispis sastojaka:" << endl;
	for(int i = 0; i < strukli.broj_sastojaka(); ++i)
		cout << '\t' << strukli[i] << endl;
	
	cout << "Provjera sastojaka:" << endl;
	cout << strukli("sol") << endl
		<< strukli("slanutak") << endl;

    return 0;
}