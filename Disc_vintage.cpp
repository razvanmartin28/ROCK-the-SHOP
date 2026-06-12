#include "Disc_vintage.h"

Disc_vintage::Disc_vintage(string den, int stoc, double pret, bool tip, string casa, int zi, int luna, int an, string trupa, string nume, bool mint, int coef):Disc(den, stoc, pret, tip, casa, zi, luna, an, trupa, nume), mint(mint)
{
    if(coef < 1 || coef > 5)
        throw Exceptie_Custom("Coeficientul de raritate al dicurilor vintage trebuie sa fie intre 1 si 5! coeficientul introdus", to_string(coef));
    this->coef_raritate = coef;
    nr_tip_prod[2]++;
    nr_tip_prod[1]--;
}

void Disc_vintage::afisare(ostream &dev) const
{
    Disc::afisare();
    string stare;
    if(mint == 0)
        stare = "NU";
    else
        stare = "DA";
    dev<<stare<<" "<<coef_raritate<<" "<<get_pret_final()<<endl;
}

double Disc_vintage::get_pret_final() const
{
    return Disc::get_pret_final() + 15 * coef_raritate;
}

void Disc_vintage::citire(istream &dev)
{
    Disc::citire(dev);
    if(&dev == &cin)
        cout<<"Introduceti starea discului, tastati 1 daca e in stare buna si 0 in caz contrar: ";
    dev>>mint;
    int coef;
    if(&dev == &cin)
        cout<<"Introdueti coeficientul de raritate al discului (numar intreg intre 1 si 5): ";
    dev>>coef;
    if(&dev == &cin)
        cin.ignore(256, '\n');
    if(coef < 1 || coef > 5)
        throw Exceptie_Custom("Coeficientul de raritate al dicurilor vintage trebuie sa fie intre 1 si 5! Coeficientul introdus", to_string(coef));
    this->coef_raritate = coef;
}

bool Disc_vintage::operator==(const Produs &p) const
{
    const Disc_vintage &aux = static_cast<const Disc_vintage&>(p);
    return (Disc::operator==(p) && mint == aux.mint && coef_raritate == aux.coef_raritate);
}

Produs* Disc_vintage::clone() const
{
    return new Disc_vintage(*this);
}
