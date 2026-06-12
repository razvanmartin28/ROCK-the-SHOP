#include "gestiune_angajati.h"

void creeaza_evid_angajati(list<Angajat*> &ang, int n)
{
    vector<vector<string>> ang_nume_prenume_CNP = {
    {"Popescu", "Ionescu", "Dumitrescu", "Marinescu", "Radu", "Vasile", "Tudor", "Barbu", "Gheorghe", "Ciobanu", "Albu", "Iliescu", "Petrescu", "Dima", "Stanciu", "Voicu", "Eusebiu", "Petre", "An", "Ion"},
    {"Andrei", "Maria", "Ioana", "Mihai", "Ana", "Alexandru", "Elena", "Cristian", "Daniela", "Gabriel", "Laura", "George", "Bianca", "Nicolae", "Alexandra", "Andrei", "Daniel", "Stefania", "David", "Bl"},
    {"1860109175195", "1710529499201", "2890328468316", "2891120266761", "1880509281254", "1910507181288", "4051125223041", "1800114071831", "2950407199213", "2721221101003", "1870101520354",
     "3051012141768", "1990829044901", "5050028410046", "2730609143893", "5000111523151", "2990703089644", "2870703467828", "5030912359098", "1970201098381"}
    };//ar trebuii sa intru pe exceptiile: cnp invalid, candidat minor la ang, an gresit, luna gresita, zi gresita, nume gresit, prenume gresit
    vector<vector<int>> ang_date_nastere = {
    {23, 15, 25, 21, 16, 05, 12, 04, 11, 24, 13, 16, 13, 24, 17, 12, 27, 33, 25, 13},
    {1, 3, 9, 11, 9, 7, 3, 8, 7, 12, 1, 7, 10, 4, 8, 9, 23, 2, 9, 7},
    {2021, 1991, 2007, 2015, 2015, 2014, 2024, 2017, 2013, 2006, 2019, 2024, 2018, 2024, 1990, 2026, 2013, 2020, 2023, 2017}
    };
    for(int i=0; i<n; i++)
    {
        try
        {
            if(i % 3 == 0)
                ang.push_back(new Manager(ang_nume_prenume_CNP[0][i], ang_nume_prenume_CNP[1][i], ang_nume_prenume_CNP[2][i], ang_date_nastere[0][i], ang_date_nastere[1][i], ang_date_nastere[2][i]));
            else if(i % 3 == 1)
                ang.push_back(new Asistent(ang_nume_prenume_CNP[0][i], ang_nume_prenume_CNP[1][i], ang_nume_prenume_CNP[2][i], ang_date_nastere[0][i], ang_date_nastere[1][i], ang_date_nastere[2][i]));
            else
                ang.push_back(new Operator_comenzi(ang_nume_prenume_CNP[0][i], ang_nume_prenume_CNP[1][i], ang_nume_prenume_CNP[2][i], ang_date_nastere[0][i], ang_date_nastere[1][i], ang_date_nastere[2][i]));
        }
        catch(const invalid_argument &e)
        {
            cout<<e.what()<<endl;
        }
        catch(const Exceptie_Custom &e)
        {
            cout<<e.what()<<endl;
        }
    }
}

void adauga_angajat(list<Angajat*> &ang, list<Operator_comenzi> &op)
{
    char raspuns = 'n';
    do{
        system("cls");
        char tip;
        cout<<"Pentru ce pozitie doriti sa angajati?\n1 - Manager\n2 - Operator de comenzi\n3 - Asistent\nTastati cifra corespunzatoare postului dorit: ";
        cin>>tip;
        while(tip != '1' && tip != '2' && tip != '3')
        {
            cin.ignore(256, '\n');
            cout<<"Nu ati introdus un tip de angajat corect!\nIntroduceti din nou: ";
            cin>>tip;
        }
        try
        {
            if(tip == '1')
            {
                Manager aux;
                cin>>aux;
                ang.push_back(new Manager(aux));
                Angajat::modifica_nr_tip_ang(tip);
            }
            else if(tip == '2')
            {
                Operator_comenzi aux;
                cin>>aux;
                ang.push_back(new Operator_comenzi(aux));
                op.push_back(aux);
                Angajat::modifica_nr_tip_ang(tip);
            }
            else
            {
                Asistent aux;
                cin>>aux;
                ang.push_back(new Asistent(aux));
                Angajat::modifica_nr_tip_ang(tip);
            }
            system("cls");
            cout<<"Operatie reusita! Doriti sa mai adaugati un angajat in evidenta?\n";
        }
        catch(const invalid_argument &e)
        {
            cout<<e.what()<<endl;
            cout<<"Doriti sa incercati din nou?\n";
        }
        catch(const Exceptie_Custom &e)
        {
            cout<<e.what()<<endl;
            cout<<"Doriti sa incercati din nou?\n";
        }
        cout<<"Tastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void afisare_evidenta_angajati(const list<Angajat*> &ang)
{
    system("cls");
    cout<<"Datele fiecarui angajat din firma, afisate in ordinea urmatoare: nume, prenume, ID,\npozitia ocupata, CNP, data angajarii si salariu, sunt: \n\n";
    for(auto i=ang.begin(); i!=ang.end(); i++)
    {
        (*i)->afisare();
        cout<<endl;
    }
    cout<<endl;
}

void stergere_angajat(list<Angajat*> &ang)
{

    char raspuns = 'n';
    do{
        afisare_evidenta_angajati(ang);
        string nume, prenume;
        cout<<"Introduceti numele si prenumele angajatului care a fost dat afara/a demisionat: ";
        cin>>nume>>prenume;
        system("cls");
        list<Angajat*>::iterator iter;
        Angajat* aux = nullptr;
        iter = remove_if(ang.begin(), ang.end(),[nume, prenume, &aux](Angajat* a)
                    {
                        if(a->get_nume() == nume && a->get_prenume() == prenume)
                        {
                            aux = a;
                            return true;
                        }
                        return false;
                    });
        if(iter != ang.end())
        {
            char tip = 'a';
            if(strstr(typeid(*aux).name(), "Manager") != nullptr)
                tip = '1';
            else if(strstr(typeid(*aux).name(), "Asistent") != nullptr)
                tip = '3';
            else if(strstr(typeid(*aux).name(), "Operator_comenzi") != nullptr)
                tip = '2';
            Angajat::modifica_nr_tip_ang(tip, 0);
            ang.erase(iter, ang.end());
            cout<<"Operatie reusita! Doriti sa mai stergeti inca un angajat din evidenta?";
        }
        else
            cout<<"Angajatul cautat nu exista! Doriti sa introduceti din nou numele si prenumele angajatului?";
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void eliberare_evidenta_angajati(list<Angajat*> &ang)
{
    for(auto i=ang.begin(); i!=ang.end(); i++)
        delete *i;
}

void modificare_nume_angajat(list<Angajat*> &ang)
{
    char raspuns = 'n';
    do{
        afisare_evidenta_angajati(ang);
        string nume, prenume, nume_nou;
        cout<<"Introduceti numele si prenumele angajatului al carui nume trebuie modificat: ";
        cin>>nume>>prenume;
        auto iter = find_if(ang.begin(), ang.end(), [nume, prenume](Angajat* a)
                        {
                                return (a->get_nume() == nume) && (a->get_prenume() == prenume);
                        });
        if(iter != ang.end())
        {
            cout<<"Introduceti numele nou al angajatului: ";
            cin>>nume_nou;
            while(nume_nou.size() < 3 || nume_nou.size() > 30)
            {
               cout<<"Eroare!! Numele trebuie sa aiba minim 3 caractere si maxim 30!\nIntroduceti din nou: ";
               cin>>nume_nou;
            }
            (*iter)->set_nume(nume_nou);
            system("cls");
            cout<<"Operatie reusita! Doriti sa mai modificati numele unui angajat?";
        }
        else
        {
            system("cls");
            cout<<"!Angajatul cautat nu exista! Doriti sa introduceti din nou numele si prenumele angajatului?";
        }
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void afisare_angajat(const list<Angajat*>  &ang)
{
    char raspuns = 'n';
    do{
        system("cls");
        string nume, prenume;
        cout<<"Introduceti numele si prenumele angajatului ale carui date le doriti afisate: ";
        cin>>nume>>prenume;
        auto iter = find_if(ang.begin(), ang.end(), [=](auto a)
                            {
                                return (a->get_nume() == nume) && (a->get_prenume() == prenume);
                            });
        system("cls");
        if(iter != ang.end())
        {
            cout<<"Operatie reusita! Datele angajatului dorit, afisate in ordinea urmatoare: nume, prenume, ID,\npozitia ocupata, CNP, data angajarii si salariu, sunt:\n\n";
            (*iter)->afisare();
            cout<<endl<<endl;
        }
        else
            cout<<"!Angajatul cautat nu exista!";
        cout<<"Doriti sa introduceti din nou numele si prenumele angajatului?";
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');

}

void creeare_fisier_Top3_ang_salariu_max(list<Angajat*> ang)
{
    ofstream f("Raportari/Top3_angajati_salariu_maxim.txt");
    if(!f)
        cout<<"Eroare la deschiderea fisierului!";
    tm data = get_timp_curent();
    char output[15];
    strftime(output, 15, "%B", &data);
    ang.sort([](Angajat *a1, Angajat *a2)
             {
                 return *a1 > *a2;
             });
    vector<Angajat*> top3;
    int nr = 0;
    for(auto i=ang.begin(); nr<3 && i!=ang.end(); i++, nr++)
        top3.push_back(*i);
    sort(top3.begin(), top3.end(), [](Angajat *a1, Angajat *a2)
         {
             if(a1->get_nume() == a2->get_nume())
                return a1->get_prenume() < a2->get_prenume();
             return a1->get_nume() < a2->get_nume();
         });
    f<<"Top 3 angajati cu salariul cel mai mare in luna curenta, "<<output<<":\n\n";
    for(auto i=top3.begin(); i!=top3.end(); i++)
    {
        (*i)->afisare(f);
        f<<endl;
    }
    f.close();

}


