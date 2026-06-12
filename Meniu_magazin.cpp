#include "Meniu_magazin.h"

void get_stoc_curent(const list<Produs*> &prod, queue<int> &stoc_curent)
{
    for(auto i=prod.begin(); i!=prod.end(); i++)
        stoc_curent.push((*i)->get_stoc());

}

void resteaza_stoc(list<Produs*> &prod, queue<int> &stoc_curent)
{
    for(auto i=prod.begin(); i!=prod.end(); i++)
    {
        (*i)->set_stoc(stoc_curent.front());
        stoc_curent.pop();
    }
}

void reseteaza_atribute(list<Operator_comenzi> &op)
{
    for(auto i=op.begin(); i!=op.end(); i++)
    {
        (*i).set_val_tot_comenzi_procesate(0);
        (*i).set_nr_comenzi();
        (*i).val_comenzi_procesate.clear();
    }
}

void verifica_alegere(char fin, char &alegere)
{
    cout<<"Tastati cifra corespunzatoare operatiei dorite: ";
    cin>>alegere;
    while(alegere < '1' || alegere > fin)
    {
        cin.ignore(256, '\n');
        cout<<"Nu ati introdus o cifra corecta!\nIntroduceti din nou: ";
        cin>>alegere;
    }
}

void meniu_gestiune_angajati(list<Angajat*> &ang, list<Operator_comenzi> &op)
{

    char raspuns = 'n';
    do{
        system("cls");
        char alege;
        cout<<"Ati ajuns in meniul pentru gestionarea angajatilor magazinului!\n\n";
        cout<<"Ce operatie doriti sa efectuati? Alegeti din lista de mai jos.\n";
        cout<<"1 - Adaugare angajat in evidenta\n";
        cout<<"2 - Stergere angajat din evidenta\n";
        cout<<"3 - Modificarea numelui unui angajat\n";
        cout<<"4 - Afisare un anumit angajat\n";
        cout<<"5 - Afisarea tuturor angajatilor\n";
        cout<<"6 - Intoarcere meniu pricipal\n";
        verifica_alegere('6', alege);

        if(alege == '1')
            adauga_angajat(ang, op);
        else if(alege == '2')
            stergere_angajat(ang);
        else if(alege == '3')
            modificare_nume_angajat(ang);
        else if(alege == '4')
            afisare_angajat(ang);
        else if(alege == '5')
            afisare_evidenta_angajati(ang);
        else
            return;

        cout<<"Doriti sa va intoarceti la meniul pentru gestionarea angajatilor?\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;

    }while(raspuns == 'd' || raspuns =='D');
}

void meniu_gestiune_produse(list<Produs*> &prod)
{
    char raspuns = 'n';
    do{
        system("cls");
        char alege;
        cout<<"Ati ajuns in meniul pentru gestionarea produselor magazinului!\n\n";
        cout<<"Ce operatie doriti sa efectuati? Alegeti din lista de mai jos.\n";
        cout<<"1 - Adaugare produs in stoc\n";
        cout<<"2 - Stergere produs din stoc\n";
        cout<<"3 - Modificarea stocului unui produs existent\n";
        cout<<"4 - Afisarea datelor pentru un produs\n";
        cout<<"5 - Afisarea stocului intreg de produse\n";
        cout<<"6 - Intoarcere meniu principal\n";
        verifica_alegere('6', alege);

        if(alege == '1')
            adauga_produs(prod);
        else if(alege == '2')
            stergere_produs(prod);
        else if(alege == '3')
            modificare_stoc_produs(prod);
        else if(alege == '4')
            afisare_produs(prod);
        else if(alege == '5')
        {
            system("cls");
            afisare_informatii_afisare_stoc_produse();
            afisare_stoc_produse(prod);
        }
        else
            return;

        cout<<"Doriti sa va intoarceti la meniul pentru gestionarea produselor?\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;

    }while(raspuns == 'd' || raspuns =='D');
}

void meniu_raportari(const list<Angajat*> &ang, const list<Operator_comenzi> &op)
{
    char raspuns = 'n';
    do{
        system("cls");
        char alege;
        cout<<"Ati ajuns in meniul pentru obtinerea raportarilor magazinului!\n\n";
        cout<<"Ce raportare doriti sa obtineti? Alegeti din lista de mai jos.\n";
        cout<<"1 - Angajatul cu cele mai multe comenzi procesate\n";
        cout<<"2 - Top 3 angajati care au gestionat cele mai valoroase comenzi\n";
        cout<<"3 - Top 3 angajati cu cel mai mare salariu in luna curenta\n";
        cout<<"4 - Intoarcere meniu principal\n";
        verifica_alegere('4', alege);

        if(alege == '1')
            creeare_fisier_ang_max_comenzi_procesate(op);
        else if(alege == '2')
            creeare_fisier_Top3_ang_max_val_comenzi(op);
        else if(alege == '3')
            creeare_fisier_Top3_ang_salariu_max(ang);
        else
            return;

        cout<<"Doriti sa mai obtineti o raportare?\nTastati d pentru da sau n pentru nu: ";
        cin>>raspuns;

    }while(raspuns == 'd' || raspuns == 'D');

}


void meniu_procesare_comenzi(list<Angajat*> &ang, list<Produs*> &prod, list<Operator_comenzi> &op, queue<Comanda> &com, queue<int> &stoc_curent)
{
    //get_stoc_curent(prod, stoc_curent);
    creeaza_coada_comenzi(com, prod);
    cout<<"Tastati enter pentru inceperea procesarii de comenzi.";
    cin.get();
    cin.get();
    procesare_comenzi(op, com, prod); //afisez simularea propriu zisa
    updateaza_salariu_op_comenzi(ang, op);
    cout<<"Procesarea de comenzi este finalizata.\nTastati enter pentru intoarcerea la meniul principal.";
    cin.get();
    //resteaza_stoc(prod, stoc_curent);
    //reseteaza_atribute(op);
}

