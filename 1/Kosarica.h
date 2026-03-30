#pragma once

#include <string>

struct Artikl {
    std::string naziv, barkod;
    double cijena;
    
    Artikl();
    Artikl(std::string naziv, std::string barkod, double cijena);
};

struct Kosarica {
    Artikl *artikli;
    int *kolicine, ukupno;
    int kapacitet;

    double Iznos();
    int Dodaj(Artikl novi_artikl, int komada);
    int Ukloni(std::string barkod);

    Kosarica();
    Kosarica(int kapacitet);
    Kosarica(const Kosarica &k);
    ~Kosarica();
};