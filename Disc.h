#include "Produs.h"
#include <string.h>

class Disc: public Produs{
    bool tip;
    string casa_discuri;
    tm data_vanzare;
    string trupa;
    string nume_album;

    void set_data_punere_vanzare(int, int, int);
public:
    Disc()=default;
    Disc(string, int, double, bool, string, int, int, int, string, string);
    void afisare(ostream& = cout) const override;
    double get_pret_final() const override;
    void citire(istream&) override;
    bool operator==(const Produs&) const override;
    Produs* clone() const override;
};
