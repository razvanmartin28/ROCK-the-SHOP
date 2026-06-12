#include "Disc.h"

class Disc_vintage final: public Disc{
    bool mint;
    int coef_raritate;
public:
    Disc_vintage()=default;
    Disc_vintage(string, int, double, bool, string, int, int, int, string, string, bool, int);
    void afisare(ostream& = cout) const override;
    double get_pret_final() const override;
    void citire(istream&) override;
    bool operator==(const Produs&) const override;
    Produs* clone() const override;
};
