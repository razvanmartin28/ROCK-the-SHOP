#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include "gestiune_stoc.h"

using namespace std;

class Comanda{
    static int nr_obj;
    string ID;
    tm data_primire;
    int durata;
    list<Produs*> produse;
    int timp_ramas;
public:
    Comanda()=default;
    Comanda(int, int, int, int, const list<Produs*>&);
    Comanda(const Comanda&);
    Comanda& operator=(const Comanda&);
    ~Comanda();
    friend istream& operator>>(istream&, Comanda&);
    friend ostream& operator<<(ostream&, const Comanda&);
    double get_valoare_comanda(bool = 1) const;
    bool verifica_max_produse_comanda() const;
    void verifcare_conditii_procesare(list<Produs*>&) const;
    void set_ID_corect_produse_comanda(const list<Produs*>&);
    string get_ID() const;
    void actualizeaza_timp();
    int get_timp_ramas() const;
    int get_durata() const;
};
