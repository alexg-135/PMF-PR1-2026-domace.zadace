#pragma once

#include <iostream>
#include <string>
#include <vector>

class Jelo;

class Sastojak {

friend class Jelo;

friend bool operator==(const Sastojak& sastojak1, const Sastojak& sastojak2);
friend bool operator!=(const Sastojak& sastojak1, const Sastojak& sastojak2);
friend std::ostream& operator<<(std::ostream& os, const Sastojak& sastojak);
friend Sastojak operator*(const Sastojak& sastojak, unsigned int broj);
friend Jelo operator+(const Sastojak& sastojak1, const Sastojak& sastojak2);
friend Jelo operator+(const Jelo& jelo, const Sastojak& sastojak);

private:
    std::string naziv;
    unsigned int kolicina;
    std::string mjerna_jedinica;
	
public:
	Sastojak& operator*=(const unsigned int& broj);
    Sastojak(const std::string& naziv, 
        const unsigned int& kolicina,
        const std::string& mjerna_jedinica);
    Sastojak();
};

class Jelo {
	
friend Jelo operator+(const Jelo& jelo, const Sastojak& sastojak);
friend Jelo operator*(const Jelo& jelo, const unsigned int& broj);
friend std::ostream& operator<<(std::ostream& os, const Jelo& jelo);

private:
    std::string naziv;
    std::vector<Sastojak> sastojci;
	
public:
	unsigned int broj_sastojaka();
	Sastojak& operator[](const unsigned int& i);
	const Sastojak& operator[](const unsigned int& i) const;
	std::string operator()(std::string naziv);
	std::string operator()(std::string naziv) const;
    Jelo& operator+=(const Sastojak& sastojak);
	Jelo& operator+=(const Jelo& jelo);
	Jelo& operator*=(const unsigned int& broj);
    Jelo(const std::string& naziv);
};

