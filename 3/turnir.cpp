#include "turnir.h"

igrac::karijera::karijera()
{
    return; // TODO: implement
}

igrac::karijera::karijera(const std::list<std::pair<std::string,int>>& ranking1)
{
    return; // TODO: implement
}

igrac::igrac()
{
    return; // TODO: implement
}

igrac::igrac(std::string prezime, char spol, const std::list<std::pair<std::string,int>>& ranking1)
{
    return; // TODO: implement
}

turnir::turnir(std::string naz)
{
    return; // TODO: implement
}

pojedinacni::pojedinacni(std::string naziv, const std::list<igrac>& single1)
{
    return; // TODO: implement
}

pojedinacni::~pojedinacni()
{
    return; // TODO: implement
}

turnir& pojedinacni::match(igrac* i1, igrac* i2, int s1, int s2, igrac* i3, igrac* i4)
{
    return *this; // TODO: implement
}

std::vector<std::string> pojedinacni::procjena_pobjednika() const
{
    return std::vector<std::string>(); // TODO: implement
}

parski::parski(std::string naziv, const std::list<std::pair<igrac,igrac>>& doubles1)
{
    return; // TODO: implement
}

parski::~parski()
{
    return; // TODO: implement
}