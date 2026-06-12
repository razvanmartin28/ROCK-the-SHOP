#include "procesare_comenzi.h"

void reseteaza_atribute(list<Operator_comenzi>&);
void get_stoc_curent(const list<Produs*>&, queue<int>&);
void resteaza_stoc(list<Produs*>&, queue<int>&);
void verifica_alegere(char, char&);
void meniu_gestiune_angajati(list<Angajat*>&, list<Operator_comenzi>&);
void meniu_gestiune_produse(list<Produs*>&);
void meniu_procesare_comenzi(list<Angajat*> &, list<Produs*>&, list<Operator_comenzi>&, queue<Comanda>&, queue<int>&);
void meniu_raportari(const list<Angajat*>&, const list<Operator_comenzi>&);

