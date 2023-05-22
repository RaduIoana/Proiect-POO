//changelog -
//  - acum am un vector de metode plata, se pot introduce carduri sau vouchere si se pot initializa metode direct din program
//  - vectorul arr,ce stocheaza aplicatiile din magazin
//  - fct template ce elibereaza memorie pt vectori (creata in special pt vectori de obiecte)
//  - specializare fct pentru vector de App_gratis*
//  - adaugare const in program
//  - fct de creare cont scoasa din clasa Utilizator
//  - contul de utilizator este acum unique ptr, init prin fct de m sus
//  - aplicatiile din main sunt acum pointeri const
//  - sort la introduceri de obiecte in vectori
//  - adaugat fct dezinstalare_apl
//  - find pt a gasi apl de dezinstalat si sort
//  - design patterns:
//  - factory method: functia de adaugare metoda din Util instantiaza obiecte din clasele cerute
//    si declara pointeri din clasa de baza abstracta pentru a adauga obiectele in vector
//  - chain of responsibility? - metoda adauga bani, merge in membrul wallet care preia date din vectorul metode
#include <iostream>
#include <string.h>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <memory>
using namespace std;

template<typename T> void free_memory(vector<T> &v)
{
    for(typename vector<T>::iterator it=v.begin(); it!=v.end(); ++it)
        delete &it;
    v.clear();
}

class Data{
    int luna,an;
public:
    Data(){ luna=0; an=0;}
    Data(int x, int y){ luna=x; an=y;}
    int get_luna() const{ return luna;}
    int get_an() const{ return an;}
    friend istream & operator >> (istream &in, Data& data_calend);
};

class metoda_plata{  //clasa de baza abstracta pt voucher si card
protected:
    double sold_metoda;
    int id_metoda;
public:
    metoda_plata(): sold_metoda(0),id_metoda(0){};
    metoda_plata(double x,int id): sold_metoda(x),id_metoda(id){};
    double get_sold_met() const{ return sold_metoda;}
    void set_sold_met(double x){ sold_metoda=x;}
    virtual void afisare_inf_met()=0;
    void set_id(int i){ id_metoda=i;}
};

class voucher:public metoda_plata{
protected:
    string nume_voucher;
    Data data_exp;
public:
    voucher(): nume_voucher(), data_exp(),metoda_plata(){};
    voucher(double s, int id, string nv, int lu, int a):nume_voucher(nv),metoda_plata(s,id),data_exp(lu,a)
    { cout<<"S-a creat voucherul cu nume: "<<nume_voucher<<", data exp: "<<data_exp.get_luna()<<"/"<<data_exp.get_an()<<", sold: "<<sold_metoda<<endl;}
    virtual void afisare_inf_met()
    {
        cout<<"Voucherul "<<nume_voucher<<" cu sold "<<sold_metoda<<" expira in luna "<<data_exp.get_luna()<<"/"<<data_exp.get_an()<<endl;
    }
    friend istream & operator >> (istream &in, voucher& voucher1);
};

class card: public voucher{
    int CVC,nr_card;
public:
    card(): nr_card(0),CVC(0),voucher(){};
    card(double s, int id, string num, int lu, int a, int C, int n):nr_card(n),CVC(C),voucher(s,id,num,lu,a)
    {
        cout<<"S-a creat cardul cu:\nNume card: "<<nume_voucher;
        cout<<"Numar card: "<<nr_card<<" CVC: "<<CVC<<endl;
        cout<<"Sold card: "<<sold_metoda<<" Data exp: "<<data_exp.get_luna()<<"/"<<data_exp.get_an()<<endl;
    }
    void afisare_inf_met()
    {
        cout<<"Nume card: "<<nume_voucher<<"Numar card: "<<nr_card<<" CVC: "<<CVC<<endl;
        cout<<"Sold card: "<<sold_metoda<<" Data exp: "<<data_exp.get_luna()<<"/"<<data_exp.get_an()<<endl;
    }
    friend istream & operator >> (istream &in, card& card1);
};

class Portofel{
    double sold_wallet;
    vector<metoda_plata*> metode;
public:
    Portofel():sold_wallet(0),metode(){ /*cout<<"s-a creat cardul vid\n";*/};
    ~Portofel(){ free_memory(metode);}
    metoda_plata* get_metoda(int i){ return metode[i];}
    void adaugare_metoda();
    void adaugare_metoda(double sold_met, int id_met, string nume_vo, int lu, int a, int CVC, int nr_card);
    void adaugare_metoda(double sold_met, int id_met, string nume_vo, int lu, int a); //metode ce permit adaugarea unor metode de plata implicite
    double get_sold_wallet() const{ return sold_wallet;}
    void set_sold_wallet(double x){ sold_wallet=x;}
    void arata_sold_metoda();
    void afisare_inf_metode()
    {
        for(vector<metoda_plata*>::iterator it=metode.begin(); it!=metode.end(); it++)
        {
            (*it)->afisare_inf_met();
        }
    }
};

class Aplicatie_gratis{
protected:
    string nume,versiune,categorie;
    Data data_lansare,data_update;
    int id_apl;
    bool free;
public:
    Aplicatie_gratis():nume(),versiune(),categorie(),data_lansare(1,2001),data_update(1,2001),free(1),id_apl(){ cout<<"S-a creat aplicatia vida\n";};
    Aplicatie_gratis(string nvme,string ver,string cat,
    int l1,int a1,int l2,int a2,bool f,int id):nume(nvme),versiune(ver),categorie(cat),
    data_lansare(l1,a1),data_update(l2,a2),free(f),id_apl(id)
    {
        cout<<"S-a creat aplicatia cu ID: "<<id_apl<<", nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie;
        cout<<"Data lansare: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<", data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
    }
    virtual ~Aplicatie_gratis(){ cout<<"sters ap gratis\n";}
    virtual void afisare_inf() const
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<"Gratis\n";
    }
    bool get_free() const{ return free;}
    int get_id() const{ return id_apl;}
    virtual double get_pret_disc() const{ return 0;}
    virtual double get_pret_nodisc() const{ return 0;}
    virtual double get_pret_disc(double luni) const{ return 0;}
    virtual double get_pret_nodisc(double luni) const{return 0;}
    virtual double get_discount() const{ return 0;}
    virtual double get_discount1() const{ return 0;}
    string get_nume() const{ return nume;}
};

class Aplicatie_cu_plata_initiala:virtual public Aplicatie_gratis{
protected:
    double pret, discount;
public:
    Aplicatie_cu_plata_initiala():Aplicatie_gratis(),pret(0),discount(0){};
    Aplicatie_cu_plata_initiala(string nvme,string ver,string cat,
    int l1,int a1,int l2,int a2,bool f,int id,double pr,double disc):Aplicatie_gratis(nvme,ver,cat,l1,a1,l2,a2,f,id),pret(pr),discount(disc)
    {cout<<"Pret: "<<pret<<" Discount cu abonament: "<<discount<<"%\n";}
    ~Aplicatie_cu_plata_initiala(){ cout<<"sters ap init\n";}
    void afisare_inf() const
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<pret<<", discount cu abonament: "<<discount<<"%\n";
    }
    virtual double get_pret_disc() const{ return pret-(pret*discount/100);}
    virtual double get_pret_nodisc() const{ return pret;}
    double get_discount() const{ return discount;}
};

class Aplicatie_cu_abonament:virtual public Aplicatie_gratis{
protected:
    double pret_pe_luna,discount1;
public:
    Aplicatie_cu_abonament():Aplicatie_gratis(),pret_pe_luna(0),discount1(0){};
    Aplicatie_cu_abonament(string nvme,string ver,string cat,
    int l1,int a1,int l2,int a2,bool f,int id,double prluna,double disc):Aplicatie_gratis(nvme,ver,cat,l1,a1,l2,a2,f,id),pret_pe_luna(prluna),discount1(disc)
    {cout<<"Pret pe luna: "<<pret_pe_luna<<" Discount cu abonament: "<<discount1<<"%\n";}
    ~Aplicatie_cu_abonament(){ cout<<"sters ap abon\n";}
    void afisare_inf() const
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret pe luna: "<<pret_pe_luna<<", discount cu abonament: "<<discount1<<"%\n";
    }
    virtual double get_pret_disc(double luni) const{ if(luni==1)return pret_pe_luna*luni; return pret_pe_luna*luni-(pret_pe_luna*luni*discount1/100);}
    virtual double get_pret_nodisc(double luni) const{ return pret_pe_luna*luni;}
    double get_discount1() const{ return discount1;}
};

class Aplicatie_abon_si_init:public Aplicatie_cu_plata_initiala,public Aplicatie_cu_abonament{
public:
    Aplicatie_abon_si_init():Aplicatie_cu_plata_initiala(),Aplicatie_cu_abonament(){};
    Aplicatie_abon_si_init(string nvme,string ver,string cat,
    int l1,int a1,int l2,int a2,bool f,int id,double pr,double disc,
    double prluna,double disc2):Aplicatie_gratis(nvme,ver,cat,l1,a1,l2,a2,f,id)
    {
        pret=pr; discount=disc; pret_pe_luna=prluna; discount1=disc2;
        cout<<"Pret: "<<pret<<", discount cu abonament: "<<discount<<"%\n";
        cout<<"Pret pe luna: "<<pret_pe_luna<<", discount pe luna cu abonament: "<<discount1<<"%\n";
    };
    ~Aplicatie_abon_si_init(){ cout<<"sters ap diam\n";}
    void afisare_inf() const
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<pret<<", discount cu abonament: "<<discount<<"%\n";
        cout<<"Pret pe luna: "<<pret_pe_luna<<", discount pe luna cu abonament: "<<discount1<<"%\n";
    }
    double get_pret_disc(double luni) const{ if(luni==1)return pret-(pret*discount/100)+pret_pe_luna*luni; return pret-(pret*discount/100)+pret_pe_luna*luni-(pret_pe_luna*luni*discount1/100);}
    double get_pret_nodisc(double luni) const{ return pret+pret_pe_luna*luni;}
};

vector<Aplicatie_gratis*> arr;

class Utilizator{
    string nume_util,parola;
    vector<int> ls_aplicatii;
    Portofel wallet;
    bool abonament;
    int zile_abon_ramase;
public:
    Utilizator():nume_util(),parola(),ls_aplicatii(),wallet(),abonament(0),zile_abon_ramase(0){ cout<<"s-a creat utilizatorul vid\n";};
    Utilizator(string n,string p):nume_util(n),parola(p),ls_aplicatii(),wallet(),abonament(0),zile_abon_ramase(0)
    { cout<<"S-a creat utilizatorul test:\nUser: "<<nume_util;
      cout<<"Parola: "<<parola<<endl; }
    ~Utilizator(){ free_memory(ls_aplicatii);}
    vector<int>& get_ls(){ return ls_aplicatii;}
    Portofel&  get_wallet(){ return wallet;}
    void verificare_abonament();
    void adauga_bani();
    void instalare_apl(int id_apl);
    void afisare_ls_apl() const;
    void dezinstalare_apl();
};

template<> void free_memory(vector<Aplicatie_gratis*> &v)
{
    for(typename vector<Aplicatie_gratis*>::iterator it=v.begin(); it!=v.end(); ++it)
    {
        delete (*it);
        delete&it;
    }
    v.clear();
}

unique_ptr<Utilizator> Creare_cont() //fct creare cont
{
    cout<<"Introduceti numele de utilizator:\n"; string nume_util;
    cin>>nume_util;
    cout<<"Introduceti parola:\n"; string parola;
    cin>>parola;
    unique_ptr<Utilizator> uti(new Utilizator(nume_util,parola));
    cout<<"Contul a fost creat cu succes!";
    return uti;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    unique_ptr<Utilizator> util1 = Creare_cont(); //creare cont
    util1->get_wallet().adaugare_metoda(5000,0,"Popescu Ion",1,2001,123,12345678);
    util1->get_wallet().adaugare_metoda(25,1,"voucher1",18,2023);
    Aplicatie_gratis* const ap1=new  Aplicatie_gratis("calendar","1.14","Instrumente",2,2001,12,2014,1,0); arr.push_back(ap1);
    Aplicatie_gratis* const ap2=new Aplicatie_cu_abonament("browser web","2.05","Instrumente",6,2016,03,2022,0,1,15,20); arr.push_back(ap2);
    Aplicatie_gratis* const ap3=new Aplicatie_cu_plata_initiala("solitaire premium","2.00","Jocuri",10,2003,11,2020,0,2,23,13); arr.push_back(ap3);
    Aplicatie_gratis* const ap4=new Aplicatie_abon_si_init("photoshop","4.01","Instrumente",3,2001,4,2023,0,3,40,15,20,5); arr.push_back(ap4);
    //util1.get_wallet().adaugare_metoda(); //adaugare metoda de plata pt cont
    util1->adauga_bani(); //adaugare bani in cont
    //cout<<util1.get_wallet().get_sold_wallet(); //afisare sold cont
    util1->verificare_abonament(); //verificare status abonament
    util1->instalare_apl(3); //instalare aplicatie
    util1->afisare_ls_apl(); //afisare ls aplicatii a clientului
    util1->dezinstalare_apl();
    free_memory(arr);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

istream & operator >> (istream &in, Data& data_calend) //cin pt data calendaristica
    {
        cout<<"Introduceti luna:\n"; in>>data_calend.luna;
        cout<<"Introduceti anul:\n"; in>>data_calend.an;
        return in;
    }

istream & operator >> (istream &in, card& card1) //cin pt date card
{
     cout<<"Introduceti numele de pe card "; in>>card1.nume_voucher;
     cout<<"Introduceti nr card "; in>>card1.nr_card; cout<<endl;
     cout<<"Introduceti CVC "; in>>card1.CVC; cout<<endl;
     cout<<"Introduceti data exp "; cout<<endl; in>>card1.data_exp; cout<<endl;
     cout<<"Introduceti sold card "; in>>card1.sold_metoda; cout<<endl;
     return in;
}

istream & operator >> (istream &in, voucher& voucher1) //cin pt voucher
{
     cout<<"Introduceti numele voucherului "; in>>voucher1.nume_voucher;
     cout<<"Introduceti data exp "; cout<<endl; in>>voucher1.data_exp; cout<<endl;
     cout<<"Introduceti sold voucher "; in>>voucher1.sold_metoda; cout<<endl;
     return in;
}

void Portofel::adaugare_metoda()
{
    string alegere;
    cout<<"Ce metoda de plata doriti sa adaugati? (card/voucher)\n";
    cin>>alegere;
    if(alegere=="card")
    {
        card card1;
        cin>>card1;
        card1.set_id(metode.size()+1);
        metoda_plata* p=&card1;
        metode.push_back(p);
    }
    else if(alegere=="voucher")
    {
        voucher voucher1;
        cin>>voucher1;
        voucher1.set_id(metode.size()+1);
        metoda_plata* p=&voucher1;
        metode.push_back(p);
    }
    sort(metode.begin(),metode.end());
}

void Portofel::adaugare_metoda(double sold_met, int id_met, string nume_vo, int lu, int a, int CVC, int nr_card) //adaugare card
{
    metoda_plata* car=new card(sold_met,id_met,nume_vo,lu,a,CVC,nr_card);
    metode.push_back(car);
    sort(metode.begin(),metode.end());
}

void Portofel::adaugare_metoda(double sold_met, int id_met, string nume_vo, int lu, int a) //adaugare voucher
{
    metoda_plata* vou=new voucher(sold_met,id_met,nume_vo,lu,a);
    metode.push_back(vou);
    sort(metode.begin(),metode.end());
}

void Portofel::arata_sold_metoda()
{
    int x; afisare_inf_metode();
    cout<<"Selectati metoda a carui sold doriti sa-l verificati:"; cin>>x;
    cout<<"Soldul tau este:"<<metode[x]->get_sold_met()<<endl;
}

void Utilizator::adauga_bani()
{
    double suma_ad; char c1='Y'; int alegere;
    string parol;
    cout<<"Introduceti parola:\n";
    cin>>parol;
    while(c1=='Y')
    {
        if(parol==parola)
        {
            cout<<"Din ce metoda doriti sa adaugati bani?\n";
            wallet.afisare_inf_metode();
            cin>>alegere;
            if(typeid((*wallet.get_metoda(alegere)))==typeid(card))
            {
                cout<<"Introduceti suma de adaugat: "; cin>>suma_ad; cout<<endl;
                double sold=wallet.get_metoda(alegere)->get_sold_met();
                try
                {
                    if(suma_ad>sold) throw -1;
                    wallet.set_sold_wallet(wallet.get_sold_wallet()+suma_ad);
                    wallet.get_metoda(alegere)->set_sold_met(sold-suma_ad);
                    cout<<"Au fost adaugati "<<suma_ad<<" lei in portofel, iar soldul total este acum:"<<wallet.get_sold_wallet()<<endl;
                    cout<<"Doriti sa mai adaugati bani in portofel?(Y/N)";
                    cin>>c1;
                }
                catch(int x){cout<<"Suma de adaugat depaseste suma de bani de pe card. Tranzactie rereusita.\n"; c1='N';}
            }
            else if(typeid((*wallet.get_metoda(alegere)))==typeid(voucher))
            {
                cout<<"Pe voucher sunt "<<wallet.get_metoda(alegere)->get_sold_met()<<" lei. Doriti sa ii adaugati in cont?(Y/N)\n";
                cin>>c1;
                if(c1=='Y')
                {
                    wallet.set_sold_wallet(wallet.get_sold_wallet()+wallet.get_metoda(alegere)->get_sold_met());
                    wallet.get_metoda(alegere)->set_sold_met(0);
                    cout<<"Doriti sa mai adaugati bani in portofel?(Y/N)";
                    cin>>c1;
                }
            }
        }
        else
        {
            cout<<"Parola incorecta. Incercati din nou?(Y+parola/N)";
            cin>>c1;
            if(c1=='Y')cin>>parol;
        }
    }
}

void Utilizator::verificare_abonament()
    {
        char c; double nr_luni,suma_finala=0; string parol;
        if(abonament){ cout<<"Aveti "<<zile_abon_ramase<<" zile ramase pana la expirarea abonamentului\nDoriti sa il reinnoiti?(Y/N)\n";}
        else { cout<<"Nu aveti abonament. Doriti sa cumparati un abonament?(Y/N)\n"; }
        cin>>c;
        if(c=='Y')
        {
            cout<<"Selectati nr de luni de adaugat. 1 luna = 25 lei\n"<<"La fiecare luna adaugata aveti un discount de 5% din suma finala, pana la 50%.\n";
            cin>>nr_luni;
            if(nr_luni==1)suma_finala=25;
            else{suma_finala=nr_luni*25;
                suma_finala=suma_finala-min((suma_finala/2),(nr_luni*5/100));}
            cout<<"Suma finala este:"<<suma_finala<<endl<<"Doriti sa faceti plata?{Y/N)";
            cin>>c; if(c=='N')return;
            try
            {
                if (suma_finala>wallet.get_sold_wallet())throw -1;
                if(wallet.get_sold_wallet()-suma_finala>=0)
                {
                    wallet.set_sold_wallet(wallet.get_sold_wallet()-suma_finala);
                    abonament=1;
                    cout<<"Soldul ramas in cont este: "<<wallet.get_sold_wallet()<<endl;
                }
            }
            catch(int x){ cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";}
        }
    }

void Utilizator::instalare_apl(const int id_apl) //instalarea unei aplicatii (scadere pret din sold cont si adaugare id apl la lista apl utilizator)
    {
        char c;
        arr[id_apl]->afisare_inf();
        cout<<"Doriti sa instalati?(Y/N)";
        cin>>c;
        if(c=='Y'){
            if(arr[id_apl]->get_free()==1)
            {
                ls_aplicatii.push_back(id_apl);
                cout<<"Aplicatia s-a instalat cu succes\n";
            }
            else
            {
                if(typeid((*arr[id_apl])).name()==typeid(Aplicatie_cu_plata_initiala).name())
                {
                    try{
                        if (arr[id_apl]->get_pret_nodisc()>wallet.get_sold_wallet())throw -1;
                        cout<<"Suma de platit: "<<arr[id_apl]->get_pret_nodisc()<<endl;
                        if(abonament==1)
                        {
                            cout<<"Datorita abonamentului, aveti o reducere de "<<arr[id_apl]->get_discount()<<"%\n";
                            cout<<"Suma de platit: "<<arr[id_apl]->get_pret_disc()<<endl;
                            wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_disc());
                        }
                        else wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_nodisc());
                        ls_aplicatii.push_back(id_apl);
                        cout<<"Aplicatia s-a instalat cu succes\n"; return;
                    }
                    catch(int x){ cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";}
                }
                if(typeid((*arr[id_apl])).name()==typeid(Aplicatie_cu_abonament).name())
                {
                    cout<<"Introduceti numarul de luni de adaugat:"; double nr_luni; cin>>nr_luni;
                    cout<<"Suma de platit: "<<arr[id_apl]->get_pret_nodisc(nr_luni)<<endl;
                    try{
                        if (arr[id_apl]->get_pret_nodisc()>wallet.get_sold_wallet())throw -1;
                        if(abonament==1)
                        {
                            cout<<"Datorita abonamentului, aveti o reducere de "<<arr[id_apl]->get_discount()<<"%\n";
                            cout<<"Suma de platit: "<<arr[id_apl]->get_pret_disc(nr_luni)<<endl;
                            wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_disc(nr_luni));
                        }
                        else wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_nodisc(nr_luni));
                        ls_aplicatii.push_back(id_apl);
                        cout<<"Aplicatia s-a instalat cu succes\n"; return;
                    }
                    catch(int x){ cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";}
                }
                if(typeid((*arr[id_apl])).name()==typeid(Aplicatie_abon_si_init).name())
                {
                    cout<<"Introduceti numarul de luni de adaugat:"; double nr_luni; cin>>nr_luni;
                    cout<<"Suma de platit: "<<arr[id_apl]->get_pret_nodisc(nr_luni)<<endl;
                    try{
                        if (arr[id_apl]->get_pret_nodisc()>wallet.get_sold_wallet())throw -1;
                        if(abonament==1)
                        {
                            cout<<"Datorita abonamentului, aveti o reducere de "<<arr[id_apl]->get_discount()<<"% la plata initiala,\n";
                            cout<<"Si de "<<arr[id_apl]->get_discount1()<<"% la 2+ luni de abonament.\n";
                            cout<<"Suma de platit: "<<arr[id_apl]->get_pret_disc(nr_luni)<<endl;
                            wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_disc(nr_luni));
                        }
                        else wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_nodisc(nr_luni));
                        ls_aplicatii.push_back(id_apl);
                        cout<<"Aplicatia s-a instalat cu succes\n"; return;
                    }
                    catch(int x){ cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";}
                }
            }
        }
        sort(ls_aplicatii.begin(),ls_aplicatii.end());
    }

void Utilizator::afisare_ls_apl() const //afisarea listei de apl a utilizatorului
{
    int i,x;
    for(i=0;i<ls_aplicatii.size();i++)
    {
        x=ls_aplicatii[i];
        arr[x]->afisare_inf();
    }
}

void Utilizator::dezinstalare_apl()
{
    afisare_ls_apl();
    cout<<"Ce aplicatie doriti sa dezinstalati?\n";
    int alegere; cin>>alegere;
    auto de_scos = find(ls_aplicatii.begin(),ls_aplicatii.end(),alegere);
    if(de_scos!=ls_aplicatii.end())
    {
        ls_aplicatii.erase(de_scos);
        cout<<"Aplicatia a fost dezinstalata cu succes.\n";
    }
    sort(ls_aplicatii.begin(),ls_aplicatii.end());
}
