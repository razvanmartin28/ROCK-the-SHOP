#include "Operator_comenzi.h"

Operator_comenzi::Operator_comenzi(string nume, string prenume, string CNP, int zi, int luna, int an):Angajat(nume, prenume, CNP, zi, luna, an)
{
    nr_tip_ang[1]++;
}

double Operator_comenzi::get_salariu() const
{
    double salariu = salariu_baza + 100 * get_ani_vechime_ang(data_angajare);
    if(verificare_adaug_bonus(CNP))
        salariu += 100;
    return salariu + 0.005 * val_tot_comenzi_procesate;
}

bool Operator_comenzi::verifica_capacitate_op_comenzi(int nr) const
{
    return static_cast<int>(com_procesate.size()) <= nr;
}

void Operator_comenzi::set_val_tot_comenzi_procesate(double val)
{
    val_tot_comenzi_procesate = val;
}

double Operator_comenzi::get_val_tot_comenzi_procesate() const
{
    return val_tot_comenzi_procesate;
}

void Operator_comenzi::incrementeaza_nr_comenzi()
{
    nr_comenzi++;
}

int Operator_comenzi::get_nr_comenzi() const
{
    return nr_comenzi;
}

void Operator_comenzi::set_nr_comenzi()
{
    nr_comenzi = 0;
}
