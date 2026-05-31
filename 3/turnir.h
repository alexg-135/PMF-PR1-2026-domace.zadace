#pragma once

#include <string>
#include<list>
#include<vector>
#include <utility>

class igrac {
    public:

    class karijera {
        public:
        std::list<std::pair<std::string,int>> ranking;
        karijera();
        karijera(const std::list<std::pair<std::string,int>>& ranking1);
    };

    karijera kar;
    std::string prezime;
    char spol;

    igrac();
    igrac(std::string prezime, char spol, const std::list<std::pair<std::string,int>>& ranking1);
};

class turnir{
    std::string naziv;

    public:
    static std::list<igrac> igraci;
    static int broj_igraca;

    turnir(std::string naz);

    virtual turnir& match(igrac* i1, igrac* i2, int s1=0, int s2=0, igrac* i3=nullptr, igrac* i4=nullptr) =0;
    virtual std::vector<std::string> procjena_pobjednika() const =0;
};

class pojedinacni: public turnir{
    public:
    std::list<igrac> single;

    pojedinacni(std::string naziv, const std::list<igrac>& single1);
    ~pojedinacni();
    turnir& match(igrac* i1, igrac* i2, int s1=0, int s2=0, igrac* i3=nullptr, igrac* i4=nullptr);
    std::vector<std::string> procjena_pobjednika() const;
};

class parski: public turnir{
    public:
    std::list<std::pair<igrac,igrac>> doubles;

    parski(std::string naziv, const std::list<std::pair<igrac,igrac>>& doubles1);
    ~parski();
    turnir& match(igrac* i1, igrac* i2, int s1=0, int s2=0, igrac* i3=nullptr, igrac* i4=nullptr);
    std::vector<std::string> procjena_pobjednika() const;
};