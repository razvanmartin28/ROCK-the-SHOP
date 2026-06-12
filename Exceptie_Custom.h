#pragma once
#include <string>

using namespace std;

class Exceptie_Custom: public exception{
    string mesaj;
public:

    Exceptie_Custom(string text, string greseala)
    {
        mesaj = "Eroare!! " + text + " este: " + greseala;
    }

    const char* what() const noexcept
    {
        return mesaj.c_str();
    }
};
