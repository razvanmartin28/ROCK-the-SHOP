#include "Produs.h"

class Articol_vestimentar final: public Produs{
    string culoare;
    string marca;
public:
    Articol_vestimentar()=default;
    Articol_vestimentar(string, int, double, string, string);
    void afisare(ostream& = cout) const override;
    double get_pret_final() const override;
    void citire(istream&) override;
    bool operator==(const Produs&) const override;
    Produs* clone() const override;
};
