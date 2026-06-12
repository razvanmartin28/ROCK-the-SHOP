#include "Comanda.h"

int Comanda::nr_obj = 0;

Comanda::Comanda(int zi, int luna, int an, int dur, const list<Produs*> &prod):durata(dur), produse(prod), timp_ramas(durata)
{
    if(luna < 1 || luna > 12)
        throw Exceptie_Custom("Luna trebuie sa fie intre 1 si 12! Luna introdusa", to_string(luna));
    if(zi < 1 || zi > 31)
        throw Exceptie_Custom("Ziua trebuie sa fie intre 1 si 31! Ziua introdusa", to_string(zi));
    if(an < 1960 || an > 2025)
        throw Exceptie_Custom("Data punerii in vanzare nu poate fi in viitor sau mai devreme de 1960. Anul introdus", to_string(an));
    data_primire = {};
    data_primire.tm_year = an - 1900;
    data_primire.tm_mon = luna - 1;
    data_primire.tm_mday = zi;
    this->ID = "com" + to_string(++nr_obj);
}

Comanda::Comanda(const Comanda &c):durata(c.durata), timp_ramas(c.durata)
{
    this->data_primire = c.data_primire;
    this->ID = c.ID;
    for(auto i=c.produse.begin(); i!=c.produse.end(); i++)
        this->produse.push_back((*i)->clone());
}

Comanda& Comanda::operator=(const Comanda &c)
{
    if(&c != this)
    {
        this->ID = c.ID;
        this->data_primire = c.data_primire;
        this->durata = c.durata;
        this->timp_ramas = c.timp_ramas;
        for(auto i=c.produse.begin(); i!=c.produse.end(); i++)
            this->produse.push_back((*i)->clone());
    }
    return *this;
}

Comanda::~Comanda()
{
    eliberare_stoc_produse(produse);
}

ostream& operator<<(ostream& dev, const Comanda &c)
{
    char output[20];
    strftime(output, 20, "%d/%b/%Y", &c.data_primire);
    dev<<c.ID<<" "<<output<<" "<<c.durata<<"s "<<c.get_valoare_comanda();
    dev<<", ce contine urmatoarele produse: \n";
    afisare_stoc_produse(c.produse, dev);
    return dev;
}

istream& operator>>(istream& dev, Comanda &c)
{
    int zi, luna, an, durata, nr_tip_prod;
    dev>>zi>>luna>>an>>durata>>nr_tip_prod;
    list<Produs*> prod;
    for(int i=0; i<nr_tip_prod; i++)
    {
        try{
            char tip;
            dev>>tip;
            dev.get();
            if(tip == '1')
            {
                Articol_vestimentar aux;
                aux.citire(dev);
                prod.push_back(new Articol_vestimentar(aux));
            }
            else if(tip == '2')
            {
                Disc aux;
                aux.citire(dev);
                prod.push_back(new Disc(aux));
            }
            else if(tip == '3')
            {
                Disc_vintage aux;
                aux.citire(dev);
                prod.push_back(new Disc_vintage(aux));
            }
            else    nr_tip_prod--;
        }
        catch(const invalid_argument &e)
        {
            cout<<e.what()<<endl;
        }
        catch(const Exceptie_Custom &e)
        {
            cout<<e.what()<<endl;
        }
    }
    dev.get();
    Comanda aux(zi, luna, an, durata, prod);
    c = aux;
    return dev;
}

double Comanda::get_valoare_comanda(bool tip) const
{
    double S = 0;
    for(auto i=produse.begin(); i!=produse.end(); i++)
    {
        if(tip == false)
            S += (*i)->get_stoc() * (*i)->Produs::get_pret_final();
        else
            S += (*i)->get_stoc() * (*i)->get_pret_final();
    }
    return S;
}

bool Comanda::verifica_max_produse_comanda() const
{
    int nr_art_vest_com = 0;
    int nr_disc_com = 0;
    for(auto i=produse.begin(); i!=produse.end(); i++)
    {
        if(dynamic_cast<Articol_vestimentar*>(*i) != nullptr)
            nr_art_vest_com += (*i)->get_stoc();
        else
            nr_disc_com += (*i)->get_stoc();
    }
    if(nr_art_vest_com > 3 || nr_disc_com > 5)
        throw invalid_argument("Comanda poate contine maxim 3 articole vestimentare si maxim 5 discuri!\nComanda contine " + to_string(nr_art_vest_com) + " Articole vestimentare si " + to_string(nr_disc_com) + " Discuri");
    return true;
}

void Comanda::verifcare_conditii_procesare(list<Produs*> &prod) const
{
    bool t = all_of(produse.begin(), produse.end(), [&prod](Produs* com_prod)
                {
                    auto iter =  find_if(prod.begin(), prod.end(), [=](Produs* stoc_prod)
                                    {
                                        return *com_prod == *stoc_prod; //folosesc op== din produs
                                    });
                    //daca produsul exista si daca are stoc suficient
                    if(iter != prod.end() && com_prod->get_stoc() <= (*iter)->get_stoc())
                    {
                        (*iter)->set_stoc((*iter)->get_stoc() - com_prod->get_stoc());
                        return true;
                    }
                    return false;
                });
    if(t == 0)
        throw invalid_argument("Unul din produsele din comanda nu exista in magazin/nu mai este in stoc momentan!");
    double val = get_valoare_comanda(0);
    if(val < 100)//vreau valoarea comenzii fara impachetare si livrare
        throw Exceptie_Custom("Valoarea comenzii trebuie sa fie de minim 100 de lei! Valoarea comenzii", to_string(val));
    verifica_max_produse_comanda();
}

void Comanda::set_ID_corect_produse_comanda(const list<Produs*> &prod)
{
    for(auto i=produse.begin(); i!=produse.end(); i++)
    {
        auto iter = find_if(prod.begin(), prod.end(), [=](Produs* p)
                            {
                                return *(*i) == *p;
                            });
        if(iter != prod.end())
            (*i)->set_ID((*iter)->get_ID());
    }
}

string Comanda::get_ID() const
{
    return ID;
}

void Comanda::actualizeaza_timp()
{
    if(timp_ramas > 0)
        timp_ramas--;
}

int Comanda::get_timp_ramas() const
{
    return timp_ramas;
}

int Comanda::get_durata() const
{
    return durata;
}
