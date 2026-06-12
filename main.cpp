#include "Meniu_magazin.h"

void testare_nr_min_angajati(list<Angajat*> &ang, list<Operator_comenzi> &op)
{
    char raspuns = 'n';
    while(!Angajat::verificare_nr_min_angajati())
    {
        cout<<"Doriti sa mai adaugati un angajat?\nTastati d pentru da sau n pentru incheierea programului: ";
        cin>>raspuns;
        if(raspuns == 'd' || raspuns == 'D')
            adauga_angajat(ang, op);
        else
            exit(0);
    }
}

void testare_nr_min_produse(list<Produs*> &prod)
{
    char raspuns = 'n';
    while(!Produs::verificare_nr_min_produse())
    {
        cout<<"Doriti sa mai adaugati un tip de produs?\nTastati d pentru da sau n pentru incheierea programului: ";
        cin>>raspuns;
        if(raspuns == 'd' || raspuns == 'D')
            adauga_produs(prod);
        else
            exit(0);
    }
}

int main()
{
    int nr_ang_tot = 20;
    //int nr_ang_bun = 13;
    list<Angajat*> evid_ang;
    creeaza_evid_angajati(evid_ang, nr_ang_tot);
    cout<<endl;

    //int nr_prod_bun = 13;
    int nr_prod_tot = 16;
    list<Produs*> stoc_prod;
    creeaza_stoc_produse(stoc_prod, nr_prod_tot);

    list<Operator_comenzi> op_com;
    creeaza_lista_op_comenzi(op_com, evid_ang);
    queue<Comanda> comenzi;
    queue<int> stoc_curent;
    bool intrat = 1;
    cin.get();
    do{
        testare_nr_min_angajati(evid_ang, op_com);
        testare_nr_min_produse(stoc_prod);

        system("cls");
        char alege_actiune;
        char fin = '5';
        cout<<"Bine ati venit la sistemul de administrare al magazinului ROCK the SHOP!"<<endl<<endl;
        cout<<"Ce operatie doriti sa efectuati? Alegeti din lista de mai jos.\n";
        cout<<"1 - Gestionare Angajati\n";
        cout<<"2 - Gestionare Stoc Produse\n";
        cout<<"3 - Procesare Comenzi\n";
        if(intrat == 1)
        {
            cout<<"4";
            fin = '4';
        }
        else
            cout<<"4 - Obtinere Raportari\n5";
        cout<<" - Inchidere aplicatie\n";
        verifica_alegere(fin, alege_actiune);
        system("cls");

        if(alege_actiune == '1')
            meniu_gestiune_angajati(evid_ang, op_com);
        else if(alege_actiune == '2')
            meniu_gestiune_produse(stoc_prod);
        else if(alege_actiune == '3')
        {
            intrat = 0;
            meniu_procesare_comenzi(evid_ang, stoc_prod, op_com, comenzi, stoc_curent);
        }
        else if(alege_actiune == '4' && intrat == 0)
        {
            meniu_raportari(evid_ang, op_com);
        }
        else if(alege_actiune == '5' || (alege_actiune == '4' && intrat == 1))
        {
            eliberare_evidenta_angajati(evid_ang);
            eliberare_stoc_produse(stoc_prod);
            return 0;
        }

        system("cls");

    }while(true);
}
