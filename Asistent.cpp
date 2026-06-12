#include "Asistent.h"

Asistent::Asistent(string nume, string prenume, string CNP, int zi, int luna, int an):Angajat(nume, prenume, CNP, zi, luna, an)
{
    nr_tip_ang[2]++;
}

double Asistent::get_salariu() const
{
    double salariu = salariu_baza + 100 * get_ani_vechime_ang(data_angajare);
    salariu *= coef;
    if(verificare_adaug_bonus(CNP))
        salariu += 100;
    return salariu;
}
