#include "Manager.h"

Manager::Manager(string nume, string prenume, string CNP, int zi, int luna, int an):Angajat(nume, prenume, CNP, zi, luna, an)
{
    nr_tip_ang[0]++;
}

double Manager::get_salariu() const
{
    double salariu = salariu_baza + 100 * get_ani_vechime_ang(data_angajare);
    return salariu * coef;
}
