#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <string.h>
#include "Exceptie_Custom.h"

using namespace std;

class Produs{
    static int nr_obj;
    string ID;
    double pret_baza;
protected:
    string denumire;
    int stoc;
    static int nr_tip_prod[3];
public:
    Produs()=default;
    Produs(string, int, double);
    virtual void afisare(ostream& = cout) const;
    virtual ~Produs(){};
    virtual double get_pret_final() const;
    virtual void citire(istream&);
    static bool verificare_nr_min_produse();
    static void modifica_nr_tip_prod(char, bool = 1);
    virtual bool operator==(const Produs&) const;
    virtual Produs* clone() const;
    void set_stoc(int);
    int get_stoc() const;
    string get_ID() const;
    void set_ID(string);
    string get_denumire() const;
};
