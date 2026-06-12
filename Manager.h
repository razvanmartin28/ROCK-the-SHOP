#include "Angajat.h"

class Manager final: public Angajat{
    constexpr static double coef = 1.25;
public:
    Manager()=default;
    Manager(string, string, string, int, int, int);
    double get_salariu() const override;
};
