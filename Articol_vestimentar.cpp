#include "Articol_vestimentar.h"

Articol_vestimentar::Articol_vestimentar(string den, int stoc, double pret, string culoare, string marca):Produs(den, stoc, pret), culoare(culoare), marca(marca)
{
    nr_tip_prod[0]++;
}

void Articol_vestimentar::afisare(ostream &dev) const
{
    Produs::afisare();
    dev<<culoare<<" "<<marca<<" "<<get_pret_final()<<endl;
}

double Articol_vestimentar::get_pret_final() const
{
    return Produs::get_pret_final() + 20;
}

void Articol_vestimentar::citire(istream &dev)
{
    Produs::citire(dev);
    if(&dev == &cin)
    {
        cin.ignore(256, '\n');
        cout<<"Introduceti culoarea articolului vestimentar: ";
        getline(dev, culoare);
        cout<<"Introduceti marca articolului vestimentar: ";
        getline(dev, marca);
    }
    else
    {
        dev.get();
        getline(dev, culoare, ',');
        dev.get();
        getline(dev, marca, ',');
    }
}

bool Articol_vestimentar::operator==(const Produs &p) const
{
    const Articol_vestimentar& aux = static_cast<const Articol_vestimentar&>(p);
    return (Produs::operator==(p) && culoare == aux.culoare && marca == aux.marca);
}

Produs* Articol_vestimentar::clone() const
{
    return new Articol_vestimentar(*this);
}
