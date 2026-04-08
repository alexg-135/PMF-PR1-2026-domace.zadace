#include <string>
#include "Kosarica.h"

Artikl::Artikl()
{
    cijena = 0;
    naziv = "nepoznat";
    barkod = "nepoznat";
}

Artikl::Artikl(std::string naziv, std::string barkod, double cijena)
{
    Artikl::naziv = naziv;
    Artikl::barkod = barkod;
    Artikl::cijena = cijena;
}

Kosarica::Kosarica()
{
    artikli = new Artikl[4];
    kolicine = new int[4];
    ukupno = 0;
    Kosarica::kapacitet = 4;
}

Kosarica::Kosarica(int kapacitet)
{
    artikli = new Artikl[kapacitet];
    kolicine = new int[kapacitet];
    ukupno = 0;
    Kosarica::kapacitet = kapacitet;
}

Kosarica::Kosarica(const Kosarica &k)
{
    int kapacitet_k = k.kapacitet;

    artikli = new Artikl[kapacitet_k];
    kolicine = new int[kapacitet_k];


    for (int i = 0; i < k.ukupno; i++)
    {
        artikli[i] = k.artikli[i];
        kolicine[i] = k.kolicine[i];
    }
    
    kapacitet = k.kapacitet;
    ukupno = k.ukupno;
    
}

Kosarica::~Kosarica()
{
    delete[] artikli;
    delete[] kolicine;
}

double Kosarica::Iznos()
{
    double iznos = 0;
    for (int i = 0; i < ukupno; i++)
    {
        double iznos_i = artikli[i].cijena;
        iznos += iznos_i * kolicine[i];
    }
    
    return iznos;
}

int Kosarica::Dodaj(Artikl novi_artikl, int komada)
{
    for (int i = 0; i < ukupno; i++)
    {
        if(artikli[i].barkod != novi_artikl.barkod) continue;

        kolicine[i] += komada;

        return 0;
    }
    
    if(ukupno < kapacitet)
    {
        artikli[ukupno] = novi_artikl;
        kolicine[ukupno] = komada;

        ukupno++;

        return 1;
    }

    Artikl* new_artikli = new Artikl[kapacitet * 2];
    int* new_kolicine = new int[kapacitet * 2];

    for (int i = 0; i < ukupno; i++)
    {
        new_artikli[i] = artikli[i];
        new_kolicine[i] = kolicine[i];
    }

    kapacitet *= 2;
    delete[] artikli;
    delete[] kolicine;

    artikli = new_artikli;
    kolicine = new_kolicine;
    
    artikli[ukupno] = novi_artikl;
    kolicine[ukupno] = komada;

    ukupno++;

    return 1;
}

int Kosarica::Ukloni(std::string barkod)
{
    int index = -1;
    for (int i = 0; i < ukupno; i++)
    {
        if(artikli[i].barkod != barkod) continue;

        index = i;
        break;
    }

    if(index == -1) return 0;
    
    for (int i = index; i < ukupno - 1; i++)
    {
        artikli[i] = artikli[i + 1];
        kolicine[i] = kolicine[i + 1];
    }
    
    ukupno--;

    return 1;
}