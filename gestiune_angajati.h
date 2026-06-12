#include "Manager.h"
#include "Operator_comenzi.h"
#include "Asistent.h"
#include <stdlib.h>
#include <vector>
#include <algorithm>

void creeaza_evid_angajati(list<Angajat*>&, int);
void adauga_angajat(list<Angajat*>&, list<Operator_comenzi>&);
void afisare_evidenta_angajati(const list<Angajat*>&);
void stergere_angajat(list<Angajat*>&);
void modificare_nume_angajat(list<Angajat*>&);
void afisare_angajat(const list<Angajat*>&);
void eliberare_evidenta_angajati(list<Angajat*>&);

void creeare_fisier_Top3_ang_salariu_max(list<Angajat*>);

