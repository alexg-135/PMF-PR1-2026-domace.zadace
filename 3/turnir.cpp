#include "turnir.h"
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include <utility>

std::list<igrac> turnir::igraci;
int turnir::broj_igraca = 0;

/**
 * @brief Konstruktor prazne karijere
 */
igrac::karijera::karijera() 
    : ranking() {}

/**
 * @brief Konstruktor karijere s danim rankingom
 * @param ranking1 Lista parova (konkurencija, rank) za karijeru
 */
igrac::karijera::karijera(const std::list<std::pair<std::string,int>>& ranking1)
    : ranking(ranking1) {}

/**
 * @brief Konstruktor praznog igrača
 */
igrac::igrac() 
    : prezime("Nepoznato ime igraca"), spol('M') {}

/**
 * @brief Konstruktor igrača s danim prezimenom, spolom i karijerom
 * @param prez Prezime igrača
 * @param sp Spol igrača ('M' ili 'Z')
 * @param ranking1 Lista parova (konkurencija, rank) za karijeru
 */
igrac::igrac(std::string prez, char sp, const std::list<std::pair<std::string,int>>& ranking1)
    : prezime(prez), spol(sp), kar(ranking1) {}

/**
 * @brief Konstruktor turnira s danim nazivom
 * @param naz Naziv turnira
 */
turnir::turnir(std::string naz) 
    : naziv(naz) {}

    
/**
 * @brief Pomoćna funkcija za umetanje igrača u listu sortiranu po prezimenu
 * @param lista Lista igrača u koju se umeće
 * @param ig Igrač koji se umeće
 */
static void umetni_sortiran(std::list<igrac>& lista, const igrac& ig) 
{
    std::list<igrac>::iterator it = lista.begin();
    while (it != lista.end() && it->prezime < ig.prezime) 
    {
        ++it;
    }
    lista.insert(it, ig);
}

/**
 * @brief Konstruktor pojedinačnog turnira s danim nazivom i listom igrača
 * @param naziv Naziv turnira
 * @param single1 Lista igrača koji sudjeluju u pojedinačnom turniru
 */
pojedinacni::pojedinacni(std::string naziv, const std::list<igrac>& single1)
    : turnir(naziv)
{
    for (std::list<igrac>::const_iterator it = single1.begin(); it != single1.end(); ++it) 
    {
        umetni_sortiran(single, *it);
    }

    for (std::list<igrac>::const_iterator it = single1.begin(); it != single1.end(); ++it) 
    {
        bool pronadjen = false;
        for (std::list<igrac>::const_iterator jt = igraci.begin(); jt != igraci.end(); ++jt) 
        {
            if (jt->prezime == it->prezime) {
                pronadjen = true;
                break;
            }
        }
        if (!pronadjen) {
            umetni_sortiran(igraci, *it);
            ++broj_igraca;
        }
    }
}

/**
 * @brief Destruktor pojedinačnog turnira - briše igrače iz statičke liste igraci
 */
pojedinacni::~pojedinacni() 
{
    for (std::list<igrac>::const_iterator it = single.begin(); it != single.end(); ++it) 
    {
        for (std::list<igrac>::iterator jt = igraci.begin(); jt != igraci.end(); ++jt) 
        {
            if (jt->prezime == it->prezime) 
            {
                igraci.erase(jt);
                --broj_igraca;
                break;
            }
        }
    }
}

/**
 * @brief Odigravanje meča između dva igrača i ažuriranje liste "single" nakon meča
 * @param i1 Prvi igrač
 * @param i2 Drugi igrač
 * @param s1 Broj osvojenih setova prvog igrača
 * @param s2 Broj osvojenih setova drugog igrača
 * @param i3 Ne koristi se u pojedinačnom turniru
 * @param i4 Ne koristi se u pojedinačnom turniru
 * @return Referenca na trenutni turnir nakon ažuriranja
 */
turnir& pojedinacni::match(igrac* i1, igrac* i2, int s1, int s2, igrac* i3, igrac* i4)
{
    igrac* gubitnik = (s1 > s2) ? i2 : i1;

    for (std::list<igrac>::iterator it = single.begin(); it != single.end(); ++it)
    {
        if (it->prezime == gubitnik->prezime)
        {
            single.erase(it);
            break;
        }
    }

    return *this;
}

/**
 * @brief Procjena pobjednika pojedinačnog turnira
 * @return Vektor imena pobjednika
 */
std::vector<std::string> pojedinacni::procjena_pobjednika() const 
{
    int best = 1001;

    for (std::list<igrac>::const_iterator it = single.begin(); it != single.end(); ++it) 
    {
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->kar.ranking.begin(); kt != it->kar.ranking.end(); ++kt)
        {
            if (kt->first == "single" && kt->second < best) 
            {
                best = kt->second;
            }
        }
    }

    if (best == 1001) best = 1000;

    std::vector<std::string> rezultat;
    for (std::list<igrac>::const_iterator it = single.begin(); it != single.end(); ++it) 
    {
        int rank = 1000;
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->kar.ranking.begin(); kt != it->kar.ranking.end(); ++kt)
        {
            if (kt->first == "single") 
            {
                rank = kt->second;
                break;
            }
        }
        if (rank == best) 
        {
            rezultat.push_back(it->prezime);
        }
    }

    return rezultat;
}

/**
 * @brief Konstruktor parskog turnira s danim nazivom i listom parova igrača
 * @param naziv Naziv turnira
 * @param doubles1 Lista parova igrača koji sudjeluju u parskom turniru
 */
parski::parski(std::string naziv, const std::list<std::pair<igrac,igrac>>& doubles1)
    : turnir(naziv)
{
    for (std::list<std::pair<igrac,igrac>>::const_iterator it = doubles1.begin(); it != doubles1.end(); ++it)
    {
        std::list<std::pair<igrac,igrac>>::iterator jt = doubles.begin();
        while (jt != doubles.end() && jt->first.prezime < it->first.prezime) 
        {
            ++jt;
        }
        doubles.insert(jt, *it);
    }

    for (std::list<std::pair<igrac,igrac>>::const_iterator it = doubles1.begin(); it != doubles1.end(); ++it)
    {
        bool pronadjen1 = false;
        for (std::list<igrac>::const_iterator jt = igraci.begin(); jt != igraci.end(); ++jt) 
        {
            if (jt->prezime == it->first.prezime)
            {
                pronadjen1 = true;
                break;
            }
        }
        if (!pronadjen1) 
        {
            umetni_sortiran(igraci, it->first);
            ++broj_igraca;
        }

        bool pronadjen2 = false;
        for (std::list<igrac>::const_iterator jt = igraci.begin(); jt != igraci.end(); ++jt)
        {
            if (jt->prezime == it->second.prezime)
            {
                pronadjen2 = true;
                break;
            }
        }
        if (!pronadjen2)
        {
            umetni_sortiran(igraci, it->second);
            ++broj_igraca;
        }
    }
}

/**
 * @brief Destruktor parskog turnira - briše igrače iz statičke liste igraci koji su bili u doubles listi
 */
parski::~parski() 
{
    for (std::list<std::pair<igrac,igrac>>::const_iterator it = doubles.begin(); it != doubles.end(); ++it)
    {
        for (std::list<igrac>::iterator jt = igraci.begin(); jt != igraci.end(); ++jt)
        {
            if (jt->prezime == it->first.prezime)
            {
                igraci.erase(jt);
                --broj_igraca;
                break;
            }
        }

        for (std::list<igrac>::iterator jt = igraci.begin(); jt != igraci.end(); ++jt)
        {
            if (jt->prezime == it->second.prezime)
            {
                igraci.erase(jt);
                --broj_igraca;
                break;
            }
        }
    }
}

/**
 * @brief Odigravanje meča između dva para i ažuriranje liste "doubles" nakon meča
 * @param i1 Prvi igrač prvog para
 * @param i2 Drugi igrač prvog para
 * @param s1 Broj osvojenih setova prvog para
 * @param s2 Broj osvojenih setova drugog para
 * @param i3 Prvi igrač drugog para
 * @param i4 Drugi igrač drugog para
 * @return Referenca na trenutni turnir nakon ažuriranja
 */
turnir& parski::match(igrac* i1, igrac* i2, int s1, int s2, igrac* i3, igrac* i4)
{
    bool par1_pobijedio = (s1 > s2);
    igrac* gub1 = par1_pobijedio ? i3 : i1;
    igrac* gub2 = par1_pobijedio ? i4 : i2;

    for (std::list<std::pair<igrac,igrac>>::iterator it = doubles.begin(); it != doubles.end(); ++it)
    {
        if ((it->first.prezime == gub1->prezime && it->second.prezime == gub2->prezime) ||
            (it->first.prezime == gub2->prezime && it->second.prezime == gub1->prezime))
        {
            doubles.erase(it);
            break;
        }
    }
    return *this;
}

/**
 * @brief Procjena pobjednika parskog turnira na osnovu prosječnog "doubles" rankinga parova
 * @return Vektor imena pobjednika (prezimena igrača iz parova
 */
std::vector<std::string> parski::procjena_pobjednika() const 
{
    int best = 1001;

    for (std::list<std::pair<igrac,igrac>>::const_iterator it = doubles.begin(); it != doubles.end(); ++it)
    {
        int r1 = 1000, r2 = 1000;
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->first.kar.ranking.begin();
             kt != it->first.kar.ranking.end(); ++kt)
        {
            if (kt->first == "doubles") { r1 = kt->second; break; }
        }
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->second.kar.ranking.begin();
             kt != it->second.kar.ranking.end(); ++kt)
        {
            if (kt->first == "doubles") { r2 = kt->second; break; }
        }
        int prosjek = (r1 + r2) / 2;
        if (prosjek < best) best = prosjek;
    }

    if (best == 1001) best = 1000;

    std::vector<std::string> rezultat;
    for (std::list<std::pair<igrac,igrac>>::const_iterator it = doubles.begin(); it != doubles.end(); ++it)
    {
        int r1 = 1000, r2 = 1000;
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->first.kar.ranking.begin(); kt != it->first.kar.ranking.end(); ++kt)
        {
            if (kt->first == "doubles") { r1 = kt->second; break; }
        }
        for (std::list<std::pair<std::string,int>>::const_iterator kt = it->second.kar.ranking.begin(); kt != it->second.kar.ranking.end(); ++kt)
        {
            if (kt->first == "doubles") { r2 = kt->second; break; }
        }

        int prosjek = (r1 + r2) / 2;
        
        if (prosjek == best) 
        {
            rezultat.push_back(it->first.prezime);
            rezultat.push_back(it->second.prezime);
        }
    }

    std::sort(rezultat.begin(), rezultat.end());
    return rezultat;
}