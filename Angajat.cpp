#include "Angajat.h"

int Angajat::nr_obj {};
int Angajat::nr_tip_ang[]{};

bool Angajat::verificare_major_la_angajare(string CNP, tm data_angajare)
{
    tm data_nastere = {};
    if(CNP[0] == '5' || CNP[0] == '4') //persoane nascute in secolul 21
    {
        string an = "20" + CNP.substr(1,2);
        data_nastere.tm_year = stoi(an) - 1900;
    }
    else if(CNP[0] == '1' || CNP[0] == '2') //persoane nascute in secolul 20
    {
        string an = "19" + CNP.substr(1,2);
        data_nastere.tm_year = stoi(an) - 1900;
    }
    data_nastere.tm_mon = stoi(CNP.substr(3,2)) - 1;
    data_nastere.tm_mday = stoi(CNP.substr(5,2));

    time_t timp_nastere = mktime(&data_nastere);
    time_t timp_angajare = mktime(&data_angajare);

    double diferenta_sec = difftime(timp_angajare, timp_nastere);
    const int sec_an = 60 * 60 * 24 * 365;
    double varsta = diferenta_sec / sec_an;
    return (varsta >= 18);
}

bool Angajat::validare_CNP(string CNP)
{
    const int v[13]{2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9, 0};
    int CNP_nr[13], S = 0, C;
    for(int i=0; i<13; i++)
    {
        if(!isdigit(CNP[i]))
            return false;
        CNP_nr[i] = CNP[i] - '0';
        S += CNP_nr[i] * v[i];
    }
    if(S % 11 < 10)
        C = S % 11;
    else
        C = 1;

    return C == CNP_nr[12];
}

Angajat::Angajat(string nume, string prenume, string CNP, int zi, int luna, int an)
{
    if(nume.size() < 3 || nume.size() > 30)
        throw Exceptie_Custom("Numele trebuie sa aiba minim 3 caractere si maxim 30! Numele introdus", nume);
    this->nume = nume;

    if(prenume.size() < 3 || prenume.size() > 30)
        throw Exceptie_Custom("Preumele trebuie sa aiba minim 3 caractere si maxim 30! Prenumele introdus", prenume);
    this->prenume = prenume;

    if(CNP.size() != 13 || validare_CNP(CNP) == false)
        throw Exceptie_Custom("CNP-ul nu este valid! CNP-ul introdus", CNP);
    this->CNP = CNP;

    if(luna < 1 || luna > 12)
        throw Exceptie_Custom("Luna trebuie sa fie intre 1 si 12! Luna introdusa", to_string(luna));
    if(zi < 1 || zi > 31)
        throw Exceptie_Custom("Ziua trebuie sa fie intre 1 si 31! Ziua introdusa", to_string(zi));
    if(an < 1960 || an > 2025)
        throw Exceptie_Custom("Anul angajarii nu poate fi in viitor sau mai devreme de 1960. Anul introdus", to_string(an));
    data_angajare = {};
    data_angajare.tm_year = an - 1900;
    data_angajare.tm_mon = luna - 1;
    data_angajare.tm_mday = zi;

    if(verificare_major_la_angajare(CNP, data_angajare) == false)
        throw invalid_argument("Eroare!! Candidatul nu este major si nu poate fi angajat!");
    this->ID = "ang" + to_string(++nr_obj);
}

void Angajat::afisare(ostream& dev) const
{
    string tip_ang;
    if(strstr(typeid(*this).name(), "Manager") != nullptr)
        tip_ang = "Manager";
    else if(strstr(typeid(*this).name(), "Asistent") != nullptr)
        tip_ang = "Asistent";
    else
        tip_ang = "Operator de comenzi";
    dev<<nume<<" "<<prenume<<" "<<ID<<" "<<tip_ang<<" "<<CNP<<" ";
    char output[20];
    strftime(output, 20, "%d/%b/%Y", &data_angajare);
    dev<<output<<" "<<get_salariu();
}

const tm get_timp_curent()
{
    time_t timp = time(NULL);
    tm timp_curent = *localtime(&timp);
    return timp_curent;
}

int Angajat::get_ani_vechime_ang(tm data_angajare) const
{
    tm timp_curent = get_timp_curent();
    int vechime = timp_curent.tm_year - data_angajare.tm_year;

    if(timp_curent.tm_mon < data_angajare.tm_mon || (timp_curent.tm_mon == data_angajare.tm_mon && timp_curent.tm_mday < data_angajare.tm_mday))
        vechime--;
    return vechime;
}

bool Angajat::verificare_adaug_bonus(string CNP) const
{
    int luna_nastere = stoi(CNP.substr(3,2));
    tm timp_curent = get_timp_curent();
    return (luna_nastere == (timp_curent.tm_mon + 1));
}

istream& operator>>(istream& dev, Angajat &a)
{
    string nume, prenume, CNP;
    cout<<"Introduceti numele candidatului: ";
    dev>>nume;
    cout<<"Introduceti prenumele candidatului: ";
    dev>>prenume;
    cout<<"Introduceti CNP-ul candidatului: ";
    dev>>CNP;
    tm data = get_timp_curent();
    Angajat aux(nume, prenume, CNP, data.tm_mday, data.tm_mon+1, data.tm_year+1900);
    a = aux;
    return dev;
}

string Angajat::get_nume() const
{
    return nume;
}

string Angajat::get_prenume() const
{
    return prenume;
}

double Angajat::get_salariu() const
{
    return salariu_baza;
}

void Angajat::set_nume(string nume)
{
    this->nume = nume;
}

bool Angajat::verificare_nr_min_angajati()
{
    if(nr_tip_ang[0] < 1 || nr_tip_ang[1] < 3 || nr_tip_ang[2] < 1)
    {
        cout<<"Numarul de angajati minimi nu este indeplinit. Magazinul nu poate functiona.\n";
        cout<<"Pentru a functiona, magazinul mai are nevoie de minim: ";
        if(nr_tip_ang[0] < 1)
            cout<<1 - nr_tip_ang[0]<<" Manager, ";
        if(nr_tip_ang[1] < 2)
            cout<<3 - nr_tip_ang[1]<<" Operatori de comenzi, ";
        else if(nr_tip_ang[1] == 2)
            cout<<3 - nr_tip_ang[1]<<" Operator de comenzi, ";
        if(nr_tip_ang[2] < 1)
            cout<<1 - nr_tip_ang[2]<<" Asistent ";
        cout<<endl<<endl;
        return false;
    }
    return true;
}

void Angajat::modifica_nr_tip_ang(char tip, bool op)
{
    if(op == 1)
    {
        if(tip == '1')
            nr_tip_ang[0]++;
        else if(tip == '2')
            nr_tip_ang[1]++;
        else
            nr_tip_ang[2]++;
    }
    else
    {
        if(tip == '1')
            nr_tip_ang[0]--;
        else if(tip == '2')
            nr_tip_ang[1]--;
        else
            nr_tip_ang[2]--;
    }
}

bool operator>(const Angajat &a1, const Angajat &a2)
{
    return a1.get_salariu() > a2.get_salariu();
}
