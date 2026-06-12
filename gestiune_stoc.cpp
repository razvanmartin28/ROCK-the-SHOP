#include "gestiune_stoc.h"

void creeaza_stoc_produse(list<Produs*> &prod, int n)
{
    vector<string> prod_denumire = {"Tricou", "Stairway to Heaven", "Sympathy for the Devil", "Blugi", "Bohemian Rhapsody", "Born to Run", "Rochie", "Hotel California", "Paint It Black", "Jacheta", "Smoke on the Water", "Hey Jude", "Hanorac", "sdadadsa", "dsadsd", "hthththr"};
    vector<double> prod_pret_baza = {180, 85, 300, 290, 90, 250, 350, 100, 400, 800, 95, 200, 250, 0, 230, 180};
    vector<vector<int>> prod_stoc_coef = {{9, 10, 5, 7, 5, 2, 6, 8, 5, 3, 11, 4, 5, 10, 3, -7}, {2, 3, 5, 1, 7}};
    vector<vector<string>> art_vest_culoare_marca = { {"Alb", "Albastru", "Rosu", "Negru", "Negru", "Rosu"}, {"Nike", "Levi's", "Zara", "Hugo Boss", "Adidas", "Reebok"}};
    vector<vector<bool>> disc_tip_mint = {{0, 1, 1, 1, 0, 0, 1, 1, 1, 0}, {1, 0, 1, 0, 1}};
    vector<vector<string>> disc_casa_trupa_nume = {
    {"Atlantic Records", "EMI Records", "Asylum Records", "Warner Bros. Records", "Decca Records", "Columbia Records", "Decca Records", "Apple Records", "sasdas", "dsadad"},
    {"Led Zeppelin", "Queen", "Eagles", "Deep Purple", "The Rolling Stones", "Bruce Springsteen", "The Rolling Stones", "The Beatles", "dsdasd", "htrtrhr"},
    {"Led Zeppelin IV", "A Night at the Opera", "Hotel California", "Machine Head", "Beggars Banquet", "Born to Run", "Aftermath", "Hey Jude", "dasdasda", "terreg"}};
    vector<vector<int>> disc_data = {{25, 29, 8, 10, 12, 18, 4, 3, 6, 13}, {11, 10, 12, 3, 5, 9, 6, 7, 2, 5}, {1971, 1975, 1976, 1972, 1968, 1975, 1966, 1970, 1982, 1991}};

    for(int i=0, k=0, k_v=0; i<n; i++)
    {
        try
        {

            if(i % 3 == 0)
                prod.push_back(new Articol_vestimentar(prod_denumire[i], prod_stoc_coef[0][i], prod_pret_baza[i], art_vest_culoare_marca[0][k_v], art_vest_culoare_marca[1][k_v]));
            else if(i % 3 == 1)
                prod.push_back(new Disc(prod_denumire[i], prod_stoc_coef[0][i], prod_pret_baza[i], disc_tip_mint[0][k], disc_casa_trupa_nume[0][k], disc_data[0][k], disc_data[1][k], disc_data[2][k], disc_casa_trupa_nume[1][k], disc_casa_trupa_nume[2][k++]));
            else
                prod.push_back(new Disc_vintage(prod_denumire[i], prod_stoc_coef[0][i], prod_pret_baza[i], disc_tip_mint[0][k], disc_casa_trupa_nume[0][k], disc_data[0][k], disc_data[1][k], disc_data[2][k], disc_casa_trupa_nume[1][k], disc_casa_trupa_nume[2][k++], disc_tip_mint[1][k_v], prod_stoc_coef[1][k_v++]));
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

void adauga_produs(list<Produs*> &prod)
{
    char raspuns = 'n';
    do{
        system("cls");
        char tip;
        cout<<"Ce tip de produs doriti sa adaugati in stoc?\n1 - Articol Vestimentar\n2 - Disc\n3 - Disc Vintage\nTastati cifra corespunzatoare tipului de produs dorit: ";
        cin>>tip;
        while(tip != '1' && tip != '2' && tip != '3')
        {
            cin.ignore(256, '\n');
            cout<<"Nu ati introdus un tip de produs corect!\nIntroduceti din nou: ";
            cin>>tip;
        }
        bool t = 1;
        cin.ignore(256, '\n');
        try
        {
            if(tip == '1')
            {
                Articol_vestimentar aux;
                adaugare_daca_nu_exista_schimba_stoc_altfel(prod, aux, t);
            }
            else if(tip == '2')
            {
                Disc aux;
                adaugare_daca_nu_exista_schimba_stoc_altfel(prod, aux, t);
            }
            else
            {
                Disc_vintage aux;
                adaugare_daca_nu_exista_schimba_stoc_altfel(prod, aux, t);
            }
            if(t == 1)
                Produs::modifica_nr_tip_prod(tip);
            system("cls");
            cout<<"Operatie reusita! Doriti sa mai adaugati un tip de produs in stoc?";
        }
        catch(const invalid_argument &e)
        {
            cout<<e.what()<<endl;
            cout<<"Doriti sa incercati din nou?";
        }
        catch(const Exceptie_Custom &e)
        {
            cout<<e.what()<<endl;
            cout<<"Doriti sa incercati din nou?";
        }
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void afisare_informatii_afisare_stoc_produse()
{
    cout<<"Datele despre fiecare produs din stoc sunt afisate in functie de tip astfel:\n";
    cout<<"Pentru toate produsele, in aceasta ordine: denumire, numar de produse din stoc, pret de baza.\n";
    cout<<"Pentru articole vestimentare mai apare culoarea, marca.\n";
    cout<<"Pentru discuri urmeaza tipul de disc, casa de discuri, data punerii in vanzare, trupa, numele albumului.\n";
    cout<<"Pentru discuri vintage se afiseaza datele ca pentru un disc, la care se adauga daca este mint sau nu si raritatea.\n";
    cout<<"De asemenea, la finalul tuturor datelor produselor se afiseaza pretul cu tot cu procesarea si livrarea.\n";
    cout<<endl;
}

void afisare_stoc_produse(const list<Produs*> &prod, ostream& dev)
{
    for(auto i=prod.begin(); i!=prod.end(); i++)
        (*i)->afisare(dev);
    cout<<endl;
}

void modificare_stoc_produs(list<Produs*> &prod)
{
    char raspuns = 'n';
    do{
        system("cls");
        afisare_stoc_produse(prod);
        string ID;
        cout<<"Introduceti ID-ul produsului al carui stoc trebuie modificat: ";
        cin>>ID;
        auto iter = find_if(prod.begin(), prod.end(), [=](auto p)
                            {
                                return p->get_ID() == ID;
                            });
        if(iter != prod.end())
        {
            int stoc_nou;
            cout<<"Introduceti stocul nou al produsului: ";
            cin>>stoc_nou;
            while(stoc_nou < 1)
            {
               cout<<"Eroare!! Trebuie sa existe cel putin un produs din fiecare tip in stoc!\nIntroduceti din nou: ";
               cin>>stoc_nou;
            }
            (*iter)->set_stoc(stoc_nou);
            system("cls");
            cout<<"Operatie reusita! Doriti sa mai modificati stocul unui produs?";
        }
        else
        {
            system("cls");
            cout<<"\n!Produsul cautat nu exista! Doriti sa introduceti din nou ID-ul produsului?";
        }
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void stergere_produs(list<Produs*> &prod)
{
    char raspuns = 'n';
    do{
        system("cls");
        afisare_stoc_produse(prod);
        string ID;
        cout<<"Introduceti ID-ul produsului pe care doriti sa il eliminati din stoc: ";
        cin>>ID;
        system("cls");
        Produs* aux = nullptr;
        auto iter = remove_if(prod.begin(), prod.end(), [ID, &aux](auto p)
                            {
                                if(p->get_ID() == ID)
                                {
                                    aux = p;
                                    return true;
                                }
                                return false;
                            });
        if(iter != prod.end())
        {
            if(strstr(typeid(*aux).name(), "Disc_vintage") != nullptr)
                Produs::modifica_nr_tip_prod('3', 0);
            else if(strstr(typeid(*aux).name(), "Articol_vestimentar") != nullptr)
                Produs::modifica_nr_tip_prod('1', 0);
            else
                Produs::modifica_nr_tip_prod('2', 0);
            prod.erase(iter, prod.end());
            cout<<"Operatie reusita! Doriti sa mai stergeti inca un produs din stoc?";
        }
        else
            cout<<"Produsul cautat nu exista! Doriti sa introduceti din nou ID-ul produsului?";
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void afisare_produs(const list<Produs*> &prod)
{
    char raspuns = 'n';
    do{
        system("cls");
        string nume;
        cout<<"Introduceti denumirea produsului al carui date le doriti afisate: ";
        getline(cin, nume);
        system("cls");
        auto iter = find_if(prod.begin(), prod.end(), [=](auto p)
                            {
                                return p->get_denumire() == nume;
                            });
        if(iter != prod.end())
        {
            cout<<"\nOperatie reusita! Datele produsului dorit sunt:\n";
            (*iter)->afisare();
        }
        else
            cout<<"\n!Produsul cautat nu exista! Doriti sa introduceti din nou denumire produsului?";
        cout<<"\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;
        cin.ignore(256, '\n');
        system("cls");
    }while(raspuns == 'd' || raspuns == 'D');
}

void eliberare_stoc_produse(list<Produs*> &prod)
{
    for(auto i=prod.begin(); i!=prod.end(); i++)
        delete *i;
}


