#include "gestiune_angajati.h"
#include "Comanda.h"
#include <fstream>
#include <chrono>
#include <thread>

void creeaza_lista_op_comenzi(list<Operator_comenzi>&, const list<Angajat*>&);
void creeaza_coada_comenzi(queue<Comanda>&, const list<Produs*>&);
void afisare_op_comenzi_inceput(const list<Operator_comenzi>&);
void procesare_comenzi(list<Operator_comenzi>&, queue<Comanda>&, list<Produs*>&);
void updateaza_salariu_op_comenzi(list<Angajat*>&, const list<Operator_comenzi>&);
void creeare_fisier_ang_max_comenzi_procesate(const list<Operator_comenzi>&);
void creeare_fisier_Top3_ang_max_val_comenzi(list<Operator_comenzi>);


