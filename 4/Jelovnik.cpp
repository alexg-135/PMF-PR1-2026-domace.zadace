#include "Jelovnik.h"

/**
 * @brief Konstruktor klase Sastojak.
 */
Sastojak::Sastojak()
    : naziv("nepoznat"), kolicina(0), mjerna_jedinica("nepoznat")
{}

/**
 * @brief Konstruktor klase Sastojak.
 * @param naziv Naziv sastojka.
 * @param kolicina Količina sastojka.
 * @param mjerna_jedinica Mjerna jedinica sastojka.
 */
Sastojak::Sastojak(const std::string& naziv, const unsigned int& kolicina, const std::string& mjerna_jedinica)
    : naziv(naziv), kolicina(kolicina), mjerna_jedinica(mjerna_jedinica)
{}

/**
 * @brief Provjerava da li su dva sastojka ista.
 * @param sastojak1 Prvi sastojak.
 * @param sastojak2 Drugi sastojak.
 * @return true ako su sastojci isti, false ako su različiti.
 */
bool operator==(const Sastojak& sastojak1, const Sastojak& sastojak2)
{
    if(sastojak1.naziv != sastojak2.naziv) return false;

    if(sastojak1.mjerna_jedinica != sastojak2.mjerna_jedinica) return false;

    return true;
}

/**
 * @brief Provjerava da li su dva sastojka različita.
 * @param sastojak1 Prvi sastojak.
 * @param sastojak2 Drugi sastojak.
 * @return true ako su sastojci različiti, false ako su isti.
 */
bool operator!=(const Sastojak& sastojak1, const Sastojak& sastojak2)
{
    return !(sastojak1 == sastojak2);
}

/**
 * @brief Ispisuje sastojak u formatu "naziv (kolicina mjerna_jedinica)".
 * @param os Izlazni stream.
 * @param sastojak Sastojak koji se ispisuje.
 * @return Referenca na izlazni stream.
 */
std::ostream& operator<<(std::ostream& os, const Sastojak& sastojak)
{
    os << sastojak.naziv << " (" << sastojak.kolicina << " " << sastojak.mjerna_jedinica << ")";
    return os;
}

/**
 * @brief Množi količinu sastojka sa zadanim brojem.
 * @param sastojak Sastojak čija se količina množi.
 * @param broj Broj sa kojim se množi količina sastojka.
 * @return Novi sastojak sa pomnoženom količinom sastojka.
 */
Sastojak operator*(const Sastojak& sastojak, unsigned int broj)
{
    return Sastojak(sastojak.naziv, sastojak.kolicina * broj, sastojak.mjerna_jedinica);
}

/**
 * @brief Kombinira dva sastojka u jedno jelo.
 * @param sastojak1 Prvi sastojak.
 * @param sastojak2 Drugi sastojak.
 * @return Jelo koje sadrži oba sastojka s nazivom prvog sastojka.
 */
Jelo operator+(const Sastojak& sastojak1, const Sastojak& sastojak2)
{
    return (Jelo(sastojak1.naziv) += sastojak1) += sastojak2;
}

/**
 * @brief Množi količinu sastojka sa zadanim brojem.
 * @param broj Broj sa kojim se množi količina sastojka.
 * @return Sastojak sa pomnoženom količinom sastojka.
 */
Sastojak& Sastojak::operator*=(const unsigned int& broj)
{
    kolicina *= broj;

    return *this;
}

/************************************************************ */

/**
 * @brief Konstruktor klase Jelo.
 * @param naziv Naziv jela.
 */
Jelo::Jelo(const std::string& naziv)
    : naziv(naziv), sastojci()
{}

/**
 * @brief Vraća broj sastojaka u jelu.
 * @return Broj sastojaka u jelu.
 */
unsigned int Jelo::broj_sastojaka()
{
    return sastojci.size();
}

/**
 * @brief Vraća referencu na sastojak na poziciji i u jelu.
 * @param i Indeks sastojka u jelu.
 * @return Referenca na sastojak na poziciji i u jelu.
 * @throws vraća referencu na poslednji sastojak ako je indeks i van opsega vektora sastojaka.
 */
Sastojak& Jelo::operator[](const unsigned int& i)
{
    if (i >= sastojci.size())
        return sastojci.back();
    return sastojci[i];
}

/**
 * @brief Vraća referencu na sastojak na poziciji i u jelu.
 * @param i Indeks sastojka u jelu.
 * @return Referenca na sastojak na poziciji i u jelu.
 * @throws vraća referencu na poslednji sastojak ako je indeks i van opsega vektora sastojaka.
 */
const Sastojak& Jelo::operator[](const unsigned int& i) const
{
    if (i >= sastojci.size())
        return sastojci.back();
    return sastojci.at(i);
}

/**
 * @brief Vraća količinu sastojka u jelu.
 * @param naziv Naziv sastojka čija se količina traži.
 * @return Količina sastojka u jelu u formatu "kolicina mjerna_jedinica" ili poruka "Nema tog sastojka!" ako sastojak nije pronađen u jelu.
 */
std::string Jelo::operator()(std::string naziv)
{
    for(const Sastojak& sastojak : sastojci)
    {
        if(sastojak.naziv == naziv)
            return std::to_string(sastojak.kolicina) + " " + sastojak.mjerna_jedinica;
    }
    return "Nema tog sastojka!";
}

/**
 * @brief Vraća količinu sastojka u jelu.
 * @param naziv Naziv sastojka čija se količina traži.
 * @return Količina sastojka u jelu u formatu "kolicina mjerna_jedinica" ili poruka "Nema tog sastojka!" ako sastojak nije pronađen u jelu.
 */
std::string Jelo::operator()(std::string naziv) const
{
    for(const Sastojak& sastojak : sastojci)
    {
        if(sastojak.naziv == naziv)
            return std::to_string(sastojak.kolicina) + " " + sastojak.mjerna_jedinica;
    }
    return "Nema tog sastojka!";
}

/**
 * @brief Dodaje sastojak u jelo.
 * @param sastojak Sastojak koji se dodaje u jelo.
 * @return Referenca na objekat Jelo nakon dodavanja sastojka.
 */
Jelo& Jelo::operator+=(const Sastojak& sastojak)
{
    for (Sastojak& s : sastojci) {
        if (s == sastojak)
        {
            s.kolicina += sastojak.kolicina;
            return *this;
        }
    }
    sastojci.push_back(sastojak);
    return *this;
}

/**
 * @brief Dodaje sastojke iz drugog jela u ovo jelo.
 * @param jelo Drugo jelo čiji se sastojci dodaju u ovo jelo.
 * @return Referenca na objekat Jelo nakon dodavanja sastojaka iz drugog jela.
 */
Jelo& Jelo::operator+=(const Jelo& jelo)
{
    for(const Sastojak& sastojak : jelo.sastojci)
    {
        *this += sastojak;
    }
    return *this;
}

/**
 * @brief Množi količine svih sastojaka u jelu sa zadanim brojem.
 * @param broj Broj sa kojim se množe količine sastojaka.
 * @return Referenca na objekat Jelo nakon množenja količina sastojaka.
 */
Jelo& Jelo::operator*=(const unsigned int& broj)
{
    for(Sastojak& sastojak : sastojci)
    {
        sastojak *= broj;
    }
    return *this;
}

/**
 * @brief Dodaje sastojak u jelo.
 * @param jelo Jelo kojem se dodaje sastojak.
 * @param sastojak Sastojak koji se dodaje u jelo.
 * @return Novo jelo koje sadrži sve sastojke iz originalnog jela i dodatni sastojak.
 */
Jelo operator+(const Jelo& jelo, const Sastojak& sastojak)
{
    Jelo novo_jelo(jelo.naziv);
    for(const Sastojak& s : jelo.sastojci)
    {
        novo_jelo += s;
    }
    novo_jelo += sastojak;
    return novo_jelo;
}

/**
 * @brief Množi količine svih sastojaka u jelu sa zadanim brojem.
 * @param jelo Jelo čiji se sastojci množe.
 * @param broj Broj sa kojim se množe količine sastojaka.
 * @return Novo jelo sa momnoženim količinama sastojaka.
 */
Jelo operator*(const Jelo& jelo, const unsigned int& broj)
{
    Jelo novo_jelo(jelo.naziv);
    for(const Sastojak& sastojak : jelo.sastojci)
    {
        novo_jelo += sastojak * broj;
    }
    return novo_jelo;
}

/**
 * @brief Ispisuje jelo u zadatom formatu.
 * @param os Izlazni stream.
 * @param jelo Jelo koje se ispisuje.
 * @return Referenca na izlazni stream.
 */
std::ostream& operator<<(std::ostream& os, const Jelo& jelo)
{
    os << jelo.naziv << ":" << std::endl;
    for(const Sastojak& sastojak : jelo.sastojci)
    {
        os << sastojak << std::endl;
    }
    return os;
}
