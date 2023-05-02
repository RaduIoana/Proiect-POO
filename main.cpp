#include <iostream>
#include <string.h>
#include <vector>
#include<typeinfo>
using namespace std;

class IntVector{
    int Size;
    int *data;
public:
    IntVector(){ data=nullptr; Size=0; /*cout<<"a fost apelat constr vid (vector)\n";*/} //constr vid
    IntVector(int k, int x=0){ //constr 0
        try
        {
            int i; Size=k;
            data=new int[k];
            for(i=0;i<k;i++)
                data[i]=x;
            if(data==nullptr)throw -1;
            cout<<"vector initializat cu "<<k<<" de 0\n";
        }
        catch(int x){cout<<"nu s-a alocat";}
    }
    IntVector(const IntVector& ob){ //constr copiere
        int i; Size=ob.Size; data=new int[Size];
        for(i=0;i<Size;i++)
            data[i]=ob.data[i];
        cout<<"copiat\n";}
    ~IntVector(){ //destructor
        if(data!=nullptr)
            {delete[] data;
             /*cout<<"vector sters\n";*/}
             }
    IntVector& operator=(const IntVector& ob);
    void add_elem(int x);
    int get_size();
    int get_elem(int i);
    void set_elem(int i, int x);
    friend ostream & operator << (ostream &out, const IntVector& vect);
    friend istream & operator >> (istream &in, IntVector& vect);
};

class Data{
    int luna,an;
public:
    Data(){ luna=0; an=0;}
    Data(int x, int y){ luna=x; an=y;}
    int get_luna(){ return luna;}
    int get_an(){ return an;}
    friend istream & operator >> (istream &in, Data& data_calend);
};

class metoda_plata{  //clasa de baza abstracta pt voucher si card
protected:
    double sold_metoda;
public:
    metoda_plata(): sold_metoda(0){};
    metoda_plata(double x): sold_metoda(x){};
    double get_sold_met(){ return sold_metoda;}
    void set_sold_met(double x){ sold_metoda=x;}
    virtual void afisare_inf_met()=0;
};

class voucher:public metoda_plata{
protected:
    string nume_voucher;
    Data data_exp;
public:
    voucher(): nume_voucher(), data_exp(),metoda_plata(){};
    voucher(string nv, double s2, int z2, int a2):nume_voucher(nv),metoda_plata(s2),data_exp(z2,a2)
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
    card(string num, int n, int C, double s,  int z, int a):nr_card(n),CVC(C),voucher(num,s,z,a)
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
    card card1;
    voucher voucher1;
public:
    Portofel():sold_wallet(0),card1(),voucher1(){ /*cout<<"s-a creat cardul vid\n";*/};
    Portofel(string num, int n, int C, double s,  int z, int a, string nv, double s2, int z2, int a2):sold_wallet(0),card1(num,n,C,s,z,a),voucher1(nv,s2,z2,a2){};
    card& get_card(){ return card1;}
    voucher& get_voucher(){ return voucher1;}
    void adaugare_metoda();
    double get_sold_wallet(){ return sold_wallet;}
    void set_sold_wallet(double x){ sold_wallet=x;}
    void arata_sold_metoda();
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
    virtual void afisare_inf()
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<"Gratis\n";
    }
    bool get_free(){ return free;}
    int get_id(){ return id_apl;}
    virtual double get_pret_disc(){ return 0;}
    virtual double get_pret_nodisc(){ return 0;}
    virtual double get_pret_disc(double luni){ return 0;}
    virtual double get_pret_nodisc(double luni){return 0;}
    virtual double get_discount(){ return 0;}
    virtual double get_discount1(){ return 0;}
    string get_nume(){ return nume;}
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
    void afisare_inf()
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<pret<<", discount cu abonament: "<<discount<<"%\n";
    }
    virtual double get_pret_disc(){ return pret-(pret*discount/100);}
    virtual double get_pret_nodisc(){ return pret;}
    double get_discount(){ return discount;}
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
    void afisare_inf()
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret pe luna: "<<pret_pe_luna<<", discount cu abonament: "<<discount1<<"%\n";
    }
    virtual double get_pret_disc(double luni){ if(luni==1)return pret_pe_luna*luni; return pret_pe_luna*luni-(pret_pe_luna*luni*discount1/100);}
    virtual double get_pret_nodisc(double luni){ return pret_pe_luna*luni;}
    double get_discount1(){ return discount1;}
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
    void afisare_inf()
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<pret<<", discount cu abonament: "<<discount<<"%\n";
        cout<<"Pret pe luna: "<<pret_pe_luna<<", discount pe luna cu abonament: "<<discount1<<"%\n";
    }
    double get_pret_disc(double luni){ if(luni==1)return pret-(pret*discount/100)+pret_pe_luna*luni; return pret-(pret*discount/100)+pret_pe_luna*luni-(pret_pe_luna*luni*discount1/100);}
    double get_pret_nodisc(double luni){ return pret+pret_pe_luna*luni;}
};

Aplicatie_gratis** arr=new Aplicatie_gratis*[3];

class Utilizator{
    string nume_util,parola;
    IntVector ls_aplicatii;
    Portofel wallet;
    bool abonament;
    int zile_abon_ramase;
public:
    Utilizator():nume_util(),parola(),ls_aplicatii(),wallet(),abonament(0),zile_abon_ramase(0){ cout<<"s-a creat utilizatorul vid\n";};
    Utilizator(string n,string p,string num, int nr, int C, double s,  int z, int a,string nv, double s2, int z2, int a2):nume_util(n),parola(p),ls_aplicatii(),wallet(num,nr,C,s,z,a,nv,s2,z2,a2),abonament(0),zile_abon_ramase(0)
    { cout<<"S-a creat utilizatorul test:\nUser: "<<nume_util;
      cout<<"Parola: "<<parola<<endl; };
    IntVector& get_ls(){ return ls_aplicatii;}
    Portofel&  get_wallet(){ return wallet;}
    void creare_cont();
    void verificare_abonament();
    void adauga_bani();
    void instalare_apl(int id_apl);
    void afisare_ls_apl();
};

void del(Aplicatie_gratis* ap){ delete ap;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Utilizator util1("Utilizator_test","parola","Popescu Ion",12345678,123,5000,1,2001,"voucher1",25,18,2023); //creare cont implicit
    Aplicatie_gratis* ap1=new  Aplicatie_gratis("calendar","1.14","Instrumente",2,2001,12,2014,1,0); *(arr+ap1->get_id())=ap1;
    Aplicatie_gratis* ap2=new Aplicatie_cu_abonament("browser web","2.05","Instrumente",6,2016,03,2022,0,1,15,20); *(arr+ap2->get_id())=ap2;
    Aplicatie_gratis* ap3=new Aplicatie_cu_plata_initiala("solitaire premium","2.00","Jocuri",10,2003,11,2020,0,2,23,13); *(arr+ap3->get_id())=ap3;
    Aplicatie_gratis* ap4=new Aplicatie_abon_si_init("photoshop","4.01","Instrumente",3,2001,4,2023,0,3,40,15,20,5); *(arr+ap4->get_id())=ap4;
    //Utilizator util1;
    //util1.creare_cont(); //creare cont custom
    //util1.get_wallet().get_voucher().afisare_inf_met();
    //util1.get_wallet().adaugare_metoda(); //adaugare metoda de plata pt contul custom
    util1.adauga_bani(); //adaugare bani in cont
    //int x; cin>>x;
    //util1.get_wallet().get_card().set_sold_card(x); //setare sold card (metoda de plata)
    //util1.get_wallet().arata_sold_card(); //afisare sold card
    //cout<<util1.get_wallet().get_sold_wallet(); //afisare sold cont
    util1.verificare_abonament(); //verificare status abonament
    util1.instalare_apl(3); //instalare aplicatie
    util1.afisare_ls_apl(); //afisare ls aplicatii a clientului
    delete ap1; delete ap2;
    delete ap3; delete ap4;
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void IntVector::add_elem(int x) //adauga un elem la vector
    {
        int i; Size++;
        int* data1=new int[Size];
        for(i=0;i<Size-1;i++)
            data1[i]=data[i];
        data1[Size-1]=x;
        delete[] data;
        data=data1;
    }

int IntVector::get_size(){ return Size;}
int IntVector::get_elem(int i){ return data[i];}
void IntVector::set_elem(int i, int x){ data[i]=x;}

IntVector& IntVector::operator=(const IntVector& ob) //vector1=vector2
    {
        if(this!=&ob)
        {
            int i;
            if(data!=nullptr)delete[] data;
            Size=ob.Size;
            data=new int[ob.Size];
            for(i=0;i<Size;i++)
                data[i]=ob.data[i];
            cout<<"ob original=ob nou\n";
        }
        return *this;
    }

ostream & operator << (ostream &out, const IntVector& vect) //cout pt vector
{
    int i;
    for(i=0;i<vect.Size;i++)
        {out<<vect.data[i]; cout<<" ";}
    cout<<"\n";
    return out;
}

istream & operator >> (istream &in, IntVector& vect) //cin pt vector
{
    int i;
    if(vect.data!=nullptr)delete[] vect.data;
    in>>vect.Size;
    vect.data=new int[vect.Size];
    for(i=0;i<vect.Size;i++)
        in>>vect.data[i];
    return in;
}

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

void Utilizator::creare_cont() //fct creare cont
    {
        cout<<"Introduceti numele de utilizator:\n";
        cin>>nume_util;
        cout<<"Introduceti parola:\n";
        cin>>parola;
        cout<<"Contul a fost creat cu succes!";
    }

void Portofel::adaugare_metoda()
{
    string alegere;
    cout<<"Ce metoda de plata doriti sa adaugati? (card/voucher)\n";
    cin>>alegere;
    //AICI EXC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    if(alegere=="card")
    {
        cin>>card1;
    }
    else if(alegere=="voucher")
    {
        cin>>voucher1;
    }
}

void Portofel::arata_sold_metoda()
    {
        cout<<"Sold voucher sau sold card?\n"; string alegere; cin>>alegere;
        if(alegere=="card")cout<<"Soldul tau este:"<<card1.get_sold_met()<<endl;
        else if(alegere=="voucher")cout<<"Soldul tau este:"<<voucher1.get_sold_met()<<endl;
    }

void Utilizator::adauga_bani()
    {
        double suma_ad; char c1='Y';
        string parol,alegere;
        cout<<"Introduceti parola:\n";
        cin>>parol;
        while(c1=='Y')
        {
            if(parol==parola)
            {
                cout<<"Doriti sa adaugati bani de pe card sau sa folositi un voucher?\n";
                cin>>alegere;
                if(alegere=="card")
                {
                    cout<<"Introduceti suma de adaugat: "; cin>>suma_ad; cout<<endl;
                    double sold=wallet.get_card().get_sold_met();
                    try
                    {
                        if(suma_ad>sold) throw -1;
                        wallet.set_sold_wallet(wallet.get_sold_wallet()+suma_ad);
                        wallet.get_card().set_sold_met(sold-suma_ad);
                        cout<<"Au fost adaugati "<<suma_ad<<" lei in portofel, iar soldul total este acum:"<<wallet.get_sold_wallet()<<endl;
                        cout<<"Doriti sa mai adaugati bani in portofel?(Y/N)";
                        cin>>c1;
                    }
                    catch(int x){cout<<"Suma de adaugat depaseste suma de bani de pe card. Tranzactie rereusita.\n"; c1='N';}
                }
                else if(alegere=="voucher")
                {
                    cout<<"Pe voucher sunt "<<wallet.get_voucher().get_sold_met()<<" lei. Doriti sa ii adaugati in cont?(Y/N)\n";
                    cin>>c1;
                    if(c1=='Y')
                    {
                        wallet.set_sold_wallet(wallet.get_sold_wallet()+wallet.get_voucher().get_sold_met());
                        wallet.get_voucher().set_sold_met(0);
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

void Utilizator::instalare_apl(int id_apl) //instalarea unei aplicatii (scadere pret din sold cont si adaugare id apl la lista apl utilizator)
    {
        char c;
        arr[id_apl]->afisare_inf();
        cout<<"Doriti sa instalati?(Y/N)";
        cin>>c;
        if(c=='Y'){
            if(arr[id_apl]->get_free()==1)
            {
                ls_aplicatii.add_elem(id_apl);
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
                        ls_aplicatii.add_elem(id_apl);
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
                        ls_aplicatii.add_elem(id_apl);
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
                        ls_aplicatii.add_elem(id_apl);
                        cout<<"Aplicatia s-a instalat cu succes\n"; return;
                    }
                    catch(int x){ cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";}
                }
            }
        }
    }

void Utilizator::afisare_ls_apl() //afisarea listei de apl a utilizatorului
{
    int i,x;
    for(i=0;i<ls_aplicatii.get_size();i++)
    {
        x=ls_aplicatii.get_elem(i);
        arr[x]->afisare_inf();
    }
}
