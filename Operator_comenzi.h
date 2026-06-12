#pragma once
#include "Angajat.h"
#include "Comanda.h"
#include <queue>

class Operator_comenzi final: public Angajat{
    int val_tot_comenzi_procesate = 0;
    int nr_comenzi = 0;
public:
    queue<Comanda> com_procesate;
    vector<double> val_comenzi_procesate;
    Operator_comenzi()=default;
    Operator_comenzi(string, string, string, int, int, int);
    double get_salariu() const override;
    void set_val_tot_comenzi_procesate(double);
    void incrementeaza_nr_comenzi();
    int get_nr_comenzi() const;
    void set_nr_comenzi();
    double get_val_tot_comenzi_procesate() const;
    bool verifica_capacitate_op_comenzi(int) const;
};
