#include "procesare_comenzi.h"

void creeaza_lista_op_comenzi(list<Operator_comenzi> &op, const list<Angajat*> &ang)
{
    for(auto i=ang.begin(); i!=ang.end(); i++)
    {
        Operator_comenzi* aux = dynamic_cast<Operator_comenzi*>(*i);
        if(aux != nullptr)
            op.push_back(*aux);
    }
}

void creeaza_coada_comenzi(queue<Comanda> &com, const list<Produs*> &prod)
{
    ifstream f("comenzi.in");
    if(!f)
        cout<<"Eroare la deschiderea fisierului!";
    int nr_comenzi;
    f>>nr_comenzi;
    for(int i=0; i<nr_comenzi; i++)
    {
        Comanda aux;
        f>>aux;
        aux.set_ID_corect_produse_comanda(prod);
        com.push(aux);
    }
    f.close();
}

void afisare_op_comenzi_inceput(const list<Operator_comenzi> &op)
{
    for(auto i=op.begin(); i!=op.end(); i++)
    {
        if((*i).com_procesate.front().get_timp_ramas() == (*i).com_procesate.front().get_durata() && !(*i).com_procesate.empty())
        {
            cout<<"Operatorul de comenzi: "<<(*i).get_nume()<<" "<<(*i).get_prenume();
            cout<<", proceseaza comanda: \n"<<(*i).com_procesate.front();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

void updateaza_salariu_op_comenzi(list<Angajat*> &ang, const list<Operator_comenzi> &op)
{
    for(auto i=op.begin(); i!=op.end(); i++)
    {
        auto iter = find_if(ang.begin(), ang.end(), [=](Angajat* a)
                        {
                            return ((*i).get_nume() == a->get_nume() && (*i).get_prenume() == a->get_prenume());
                        });
        if(iter != ang.end())
        {
            Operator_comenzi* aux = static_cast<Operator_comenzi*>(*iter);
            aux->set_val_tot_comenzi_procesate((*i).get_val_tot_comenzi_procesate());
        }
    }
}

void procesare_comenzi(list<Operator_comenzi> &op, queue<Comanda> &comenzi, list<Produs*> &prod)
{
    int durata_simulare = 0;
    while(!comenzi.empty() || any_of(op.begin(), op.end(), [](const Operator_comenzi &i){return !(i.com_procesate.empty());}))
    {

        cout<<"\nSecunda: "<<++durata_simulare<<endl<<endl<<endl;

        //verificam daca toti angajatii sunt ocupati
        bool ocupati = all_of(op.begin(), op.end(), [](const Operator_comenzi& i)
                              {
                                return i.com_procesate.size() == 3;
                              });

        if(ocupati && !comenzi.empty())
            cout<<"Toti angajatii sunt ocupati! Se asteapta finalizarea unei comenzi.\n"<<endl;
        else
        {
            for(auto i=op.begin(); i!=op.end(); i++)//atribuim comenzi operatorilor de comenzi
            {
                int t = 1;
                do{
                    if((*i).verifica_capacitate_op_comenzi(2) == 1 && !comenzi.empty())
                    {
                        Comanda aux(comenzi.front());
                        try
                        {
                            aux.verifcare_conditii_procesare(prod);
                            (*i).com_procesate.push(aux);
                            cout<<"Se adauga in coada operatorului de comenzi: "<<(*i).get_nume()<<" "<<(*i).get_prenume();
                            cout<<" comanda cu ID-ul: "<<(*i).com_procesate.back().get_ID()<<endl<<endl;
                            this_thread::sleep_for(chrono::seconds(1));
                            t = 0;
                        }
                        catch(const invalid_argument &e)
                        {
                            cout<<"Comanda cu ID-ul: "<<aux.get_ID()<<" nu poate fi procesata!\n";
                            cout<<e.what()<<endl<<endl;
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        catch(const Exceptie_Custom &e)
                        {
                            cout<<"Comanda cu ID-ul: "<<aux.get_ID()<<" nu poate fi procesata!\n";
                            cout<<e.what()<<endl<<endl;
                            this_thread::sleep_for(chrono::seconds(1));
                        }
                        comenzi.pop();
                    }
                    else    break;
                }while(t == 1 && !comenzi.empty());
            }
        }
        afisare_op_comenzi_inceput(op);

        for(auto i=op.begin(); i!=op.end(); i++)
        {
            if(!(*i).verifica_capacitate_op_comenzi(0))
            {
                if((*i).com_procesate.front().get_timp_ramas() == 0)
                {
                    cout<<"Operatorul de comenzi: "<<(*i).get_nume()<<" "<<(*i).get_prenume();
                    cout<<" a finalizat comanda cu ID-ul: "<<(*i).com_procesate.front().get_ID()<<endl<<endl;
                    (*i).set_val_tot_comenzi_procesate((*i).get_val_tot_comenzi_procesate() + (*i).com_procesate.front().get_valoare_comanda());
                    (*i).incrementeaza_nr_comenzi();
                    (*i).val_comenzi_procesate.push_back((*i).com_procesate.front().get_valoare_comanda());
                    (*i).com_procesate.pop();
                }
                else
                    (*i).com_procesate.front().actualizeaza_timp();
            }

        }

        this_thread::sleep_for(chrono::seconds(1));
    }

}

void creeare_fisier_ang_max_comenzi_procesate(const list<Operator_comenzi> &op)
{
    int nr_max_com = 0;
    list <Operator_comenzi> op_max;
    for(auto i=op.begin(); i!=op.end(); i++)
    {
        if(nr_max_com < (*i).get_nr_comenzi())
        {
            nr_max_com = (*i).get_nr_comenzi();
            op_max.clear();
            op_max.push_back(*i);
        }
        else if(nr_max_com == (*i).get_nr_comenzi())
            op_max.push_back(*i);
    }
    ofstream f("Raportari/Angajat_comenzi_max.txt");
    if(!f)
        cout<<"Eroare la deschiderea fisierului.";
    if(op_max.size() == 1)
        f<<"Angajatul cu cele mai multe comenzi procesate este: \n";
    else
        f<<"Angajatii cu cele mai multe comenzi procesate sunt: \n";
    for(auto i=op_max.begin(); i!=op_max.end(); i++)
    {
        (*i).afisare(f);
        f<<endl;
    }
    if(op_max.size() == 1)
        f<<"Acesta a procesat ";
    else
        f<<"Acestia au procesat ";
    f<<nr_max_com<<" comenzi.";

    f.close();
}

void creeare_fisier_Top3_ang_max_val_comenzi(list<Operator_comenzi> op)
{
    for(auto i=op.begin(); i!=op.end(); i++)
    {
        sort((*i).val_comenzi_procesate.begin(), (*i).val_comenzi_procesate.end(), [](double a, double b)
            {
                return a > b;
            });
    }

    vector<Operator_comenzi> top3;
    double maxim[3]{};

    for(int nr=0; nr<3; nr++)
    {
        list<Operator_comenzi>::iterator poz;
        for(auto i=op.begin(); i!=op.end(); i++)
        {
            if(!(*i).val_comenzi_procesate.empty() && maxim[nr] <= (*i).val_comenzi_procesate.front())
            {
                maxim[nr] = (*i).val_comenzi_procesate.front();
                poz = i;
            }
        }

        top3.push_back(*poz);
        (*poz).val_comenzi_procesate.erase((*poz).val_comenzi_procesate.begin());
    }

    int k = 0;
    ofstream f("Raportari/Top3_angajati_val_max_comenzi.txt");
    if(!f)
        cout<<"Eroare la deschiderea fisierului.";
    f<<"Top 3 angajati care au gestionat cele mai valoroase comenzi: \n\n";
    for(auto i=top3.begin(); i!=top3.end(); i++)
    {
        (*i).afisare(f);
        f<<" a gestionat comanda in valoare de "<<maxim[k++]<<endl;
    }
    f.close();

}

