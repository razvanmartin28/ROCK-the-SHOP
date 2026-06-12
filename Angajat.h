#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include "Exceptie_Custom.h"

using namespace std;

class Angajat{
    static int nr_obj;
    string ID;
    string nume;
    string prenume;

    bool validare_CNP(string);
    bool verificare_major_la_angajare(string, tm);
protected:
    string CNP;
    tm data_angajare;
    const static int salariu_baza = 3500;
    static int nr_tip_ang[3];

    int get_ani_vechime_ang(tm) const;
    bool verificare_adaug_bonus(string) const;
    virtual double get_salariu() const;
public:
    Angajat()=default;
    Angajat(string, string, string, int, int, int);
    friend istream& operator>>(istream&, Angajat&);
    virtual ~Angajat(){}
    void afisare(ostream& = cout) const;
    string get_nume() const;
    string get_prenume() const;
    void set_nume(string);
    static bool verificare_nr_min_angajati();
    static void modifica_nr_tip_ang(char, bool = 1);
    friend bool operator>(const Angajat&, const Angajat&);
};

const tm get_timp_curent();

