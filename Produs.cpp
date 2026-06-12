#include "Produs.h"

int Produs::nr_obj {};
int Produs::nr_tip_prod[]{};

Produs::Produs(string denumire, int stoc, double pret):denumire(denumire)
{
    if(stoc < 1)
        throw Exceptie_Custom("Trebuie sa existe cel putin un produs din fiecare tip in stoc! Stocul introdus", to_string(stoc));
    this->stoc = stoc;
    if(pret <= 0)
        throw Exceptie_Custom("Pretul de baza al unui produs trebuie sa fie strict pozitiv! Pretul introdus", to_string(pret_baza));
    this->pret_baza = pret;
    this->ID = "prod" + to_string(++nr_obj);
}

void Produs::afisare(ostream& dev) const
{
    dev<<denumire<<" "<<ID<<" "<<stoc<<" "<<pret_baza<<" ";
}

double Produs::get_pret_final() const
{
    return pret_baza;
}

void Produs::citire(istream& dev)
{
    string den;
    int stoc;
    double pret;
    if(&dev == &cin)
    {
        cout<<"Introduceti denumirea produsului: ";
        getline(dev, den);
    }
    else
        getline(dev, den, ',');
    if(&dev == &cin)
        cout<<"Introduceti stocul produsului: ";
    dev>>stoc;
    if(&dev == &cin)
        cout<<"Introduceti pretul de baza al produsului: ";
    dev>>pret;
    Produs aux(den, stoc, pret);
    *this = aux;
}

bool Produs::verificare_nr_min_produse()
{
    int t = 1;
    for(int i=0; i<3; i++)
        if(nr_tip_prod[i] < 2)
        {
            cout<<"Numarul de produse minime nu este indeplinit. Magazinul nu poate functiona.\n";
            t = 0;
            break;
        }
    if(t == 0)
    {
        cout<<"Pentru a functiona, magazinul mai are nevoie de minim: ";
        if(nr_tip_prod[0] == 1)
            cout<<"1 Articol vestimentar, ";
        else if(nr_tip_prod[0] == 0)
            cout<<"2 Articole vestimentare, ";
        if(nr_tip_prod[1] == 1)
            cout<<"1 Disc, ";
        else if(nr_tip_prod[1] == 0)
            cout<<"2 Discuri, ";
        if(nr_tip_prod[2] == 1)
            cout<<"1 Disc vintage ";
        else if(nr_tip_prod[2] == 0)
            cout<<"2 Discuri vintage ";
        cout<<endl<<endl;
        return false;
    }
    return true;
}

void Produs::modifica_nr_tip_prod(char tip, bool op)
{
    if(op == 1)
    {
        if(tip == '1')
            nr_tip_prod[0]++;
        else if(tip == '2')
            nr_tip_prod[1]++;
        else
            nr_tip_prod[2]++;
    }
    else
    {
        if(tip == '1')
            nr_tip_prod[0]--;
        else if(tip == '2')
            nr_tip_prod[1]--;
        else
            nr_tip_prod[2]--;
    }
}

bool Produs::operator==(const Produs &p) const
{
    return (denumire == p.denumire && pret_baza == p.pret_baza);
}

void Produs::set_stoc(int stoc)
{
    this->stoc = stoc;
}

string Produs::get_ID() const
{
    return this->ID;
}

string Produs::get_denumire() const
{
    return this->denumire;
}

int Produs::get_stoc() const
{
    return this->stoc;
}

Produs* Produs::clone() const
{
    return 0;
}

void Produs::set_ID(string ID_nou)
{
    this->ID = ID_nou;
}
