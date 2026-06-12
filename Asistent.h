#include "Angajat.h"

class Asistent final: public Angajat{
    constexpr static double coef = 0.75;
public:
    Asistent()=default;
    Asistent(string, string, string, int, int, int);
    double get_salariu() const override;
};
