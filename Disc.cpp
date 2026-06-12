#include "Disc.h"

void Disc::set_data_punere_vanzare(int zi, int luna, int an)
{
    if(luna < 1 || luna > 12)
        throw Exceptie_Custom("Luna trebuie sa fie intre 1 si 12! Luna introdusa", to_string(luna));
    if(zi < 1 || zi > 31)
        throw Exceptie_Custom("Ziua trebuie sa fie intre 1 si 31! Ziua introdusa", to_string(zi));
    if(an < 1960 || an > 2025)
        throw Exceptie_Custom("Data punerii in vanzare nu poate fi in viitor sau mai devreme de 1960. Anul introdus", to_string(an));
    data_vanzare = {};
    data_vanzare.tm_year = an - 1900;
    data_vanzare.tm_mon = luna - 1;
    data_vanzare.tm_mday = zi;
}

Disc::Disc(string den, int stoc, double pret, bool tip, string casa, int zi, int luna, int an, string trupa, string nume):Produs(den, stoc, pret), tip(tip), casa_discuri(casa), trupa(trupa), nume_album(nume)
{
    nr_tip_prod[1]++;
    set_data_punere_vanzare(zi, luna, an);
}

void Disc::afisare(ostream &dev) const
{
    Produs::afisare();
    string tip;
    if(this->tip == 1)
        tip = "CD";
    else
        tip = "vinil";
    char output[20];
    strftime(output, 20, "%d/%b/%Y", &data_vanzare);
    dev<<tip<<" "<<casa_discuri<<" "<<output<<" "<<trupa<<" "<<nume_album<<" ";
    if(strstr(typeid(*this).name(), "Disc_vintage") == nullptr)
        dev<<get_pret_final()<<endl;
}

double Disc::get_pret_final() const
{
    return Produs::get_pret_final() + 5;
}

void Disc::citire(istream& dev)
{
    Produs::citire(dev);
    if(&dev == &cin)
    {
        cin.ignore(256, '\n');
        cout<<"Introduceti tipul de disc, tastati 0 pentru CD sau 1 pentru vinil: ";
    }
    dev>>tip;
    if(&dev == &cin)
    {
        cin.ignore(256, '\n');
        cout<<"Introduceti casa de discuri: ";
        getline(dev, casa_discuri);
    }
    else
    {
        dev.get();
        getline(dev, casa_discuri, ',');
    }
    int zi, luna, an;
    if(&dev == &cin)
        cout<<"Introduceti data punerii in vanzare: ";
    dev>>zi>>luna>>an;
    set_data_punere_vanzare(zi, luna, an);
    if(&dev == &cin)
    {
        cin.ignore(256, '\n');
        cout<<"Introduceti trupa care canta: ";
        getline(dev, trupa);
        cout<<"Introduceti numele albumului din care face parte discul: ";
        getline(dev, nume_album);
    }
    else
    {
        dev.get();
        getline(dev, trupa, ',');
        dev.get();
        getline(dev, nume_album, ',');
    }
}


bool Disc::operator==(const Produs &p) const
{
    const Disc &aux = static_cast<const Disc&>(p);
    return (Produs::operator==(p) && casa_discuri == aux.casa_discuri &&
            tip == aux.tip && trupa == aux.trupa && nume_album == aux.nume_album &&
            data_vanzare.tm_year == aux.data_vanzare.tm_year && data_vanzare.tm_mon == aux.data_vanzare.tm_mon && data_vanzare.tm_mday == aux.data_vanzare.tm_mday);
}

Produs* Disc::clone() const
{
   return new Disc(*this);
}
