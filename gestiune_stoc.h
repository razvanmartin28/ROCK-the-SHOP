#include "Articol_vestimentar.h"
#include "Disc_vintage.h"
#include <vector>
#include <list>
#include <algorithm>

void creeaza_stoc_produse(list<Produs*>&, int);
void modificare_stoc_produs(list<Produs*>&);
void afisare_stoc_produse(const list<Produs*>&, ostream& = cout);
void adauga_produs(list<Produs*> &);
void stergere_produs(list<Produs*>&);
void afisare_produs(const list<Produs*>&);
void afisare_informatii_afisare_stoc_produse();
void eliberare_stoc_produse(list<Produs*> &);

template<typename T>
void adaugare_daca_nu_exista_schimba_stoc_altfel(list<Produs*> &prod, T p, bool &t)
{
    p.citire(cin);
    list<Produs*>::iterator iter;
    iter = find_if(prod.begin(), prod.end(), [=](Produs* i)
               {
                    return *i == p;
               }); //foloseste operatorul== in functie de ce tip de produs e p
    if(iter != prod.end()) //am gasit produs
    {
        (*iter)->set_stoc((*iter)->get_stoc() + p.get_stoc());
        t = 0;
    }
    else
        prod.push_back(new T(p));
}
