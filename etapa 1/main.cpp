#include <iostream>
#include <string.h>
using namespace std;
class IntVector{
    int Size;
    int *data;
public:
    IntVector(){ data=nullptr; Size=0; /*cout<<"a fost apelat constr vid (vector)\n";*/} //constr vid
    IntVector(int k, int x=0){ //constr 0
        int i; Size=k;
        data=new int[k];
        for(i=0;i<k;i++)
            data[i]=x;
        if(data==nullptr)cout<<"nu s-a alocat";
        cout<<"vector initializat cu "<<k<<" de 0\n";
        }
    IntVector(const IntVector& ob){ //constr copiere
        int i; Size=ob.Size; data=new int[Size];
        for(i=0;i<Size;i++)
            data[i]=ob.data[i];
        cout<<"copiat\n";}
    ~IntVector(){ //destructor
        if(data!=nullptr)
            {delete[] data;
             cout<<"vector sters\n";}
             }
    IntVector& operator=(const IntVector& ob);
    void add_elem(int x);
    int get_size();
    int get_elem(int i);
    void set_elem(int i, int x);
    friend ostream & operator << (ostream &out, const IntVector& vect);
    friend istream & operator >> (istream &in, IntVector& vect);
};
class String{
    int length;
    char* data;
public:
    String(){ length=0; data=nullptr; /*cout<<"a fost apelat constr vid (str)\n";*/} //constr vid
    String(const char *sir) //constr declarare sir
    {
        length=strlen(sir);
        data=new char[length];
        if(data==nullptr)cout<<"nu s-a alocat";
        strncpy(data,sir,length+1);
        //cout<<"Sirul a fost initializat cu: \""<<data<<"\"\n";
    }
    String(const String& ob) //constr copiere sir
    {
        int i;
        length=ob.length;
        data=new char[length];
        for(i=0;i<=length;i++)
                data[i]=ob.data[i];
        //cout<<"s-a copiat sirul "<<data<<endl;

    }
    ~String(){ if(data!=nullptr){delete[] data; /*cout<<"Sir sters\n";*/}} //destructor sir
    void addchar(char c,int x); //adaugarea in sir a unui caracter c pe pozitia x
    void concat(String s); //concatenarea a doua siruri
    String& operator=(const String& ob);
    bool operator ==(String &str);
    friend ostream & operator << (ostream &out, const String& ob);
    friend istream & operator >> (istream&in, String& ob);
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
class date_card{
    int CVC,nr_card,sold_card;
    String nume_card;
    Data data_exp;
public:
    date_card(): nume_card(),nr_card(0),CVC(0),sold_card(0),data_exp(){};
    date_card(const char* nu, int n, int C, int s,  int z, int a):nume_card(nu),nr_card(n),CVC(C),sold_card(s),data_exp(z,a)
    {
        cout<<"S-a creat cardul test cu:\nNume card: "<<nume_card;
        cout<<"Numar card: "<<nr_card<<" CVC: "<<CVC<<endl;
        cout<<"Sold card: "<<sold_card<<" Data exp: "<<data_exp.get_luna()<<"/"<<data_exp.get_an()<<endl;
    }
    int get_sold_card(){ return sold_card;}
    void set_sold_card(int x){ sold_card=x;}
    friend istream & operator >> (istream &in, date_card& card1);
};
class Portofel{
    int sold_wallet;
    date_card card;
public:
    Portofel():sold_wallet(0),card(){ /*cout<<"s-a creat cardul vid\n";*/};
    Portofel(const char* nu, int n, int C, int s,  int z, int a):sold_wallet(0),card(nu,n,C,s,z,a){};
    date_card& get_card(){ return card;}
    void adaugare_metoda();
    int get_sold_wallet(){ return sold_wallet;}
    void set_sold_wallet(int x){ sold_wallet=x;}
    void arata_sold_card();
};

class Aplicatie{
    String nume,versiune,categorie;
    Data data_lansare,data_update;
    bool free;
    int id_apl, pret, discount;
public:
    Aplicatie():nume{},versiune(),categorie(),data_lansare(1,2001),data_update(1,2001),free(1),id_apl(0),pret(0),discount(0){ cout<<"S-a creat aplicatia vida\n";};
    Aplicatie(const char* nvme,const char* ver,const char* cat,
    int l1,int a1,int l2,int a2,bool f,int id,int pr,int disc):nume(nvme),versiune(ver),categorie(cat),
    data_lansare(l1,a1),data_update(l2,a2),free(f),id_apl(id),pret(pr),discount(disc)
    {
        cout<<"S-a creat aplicatia cu ID: "<<id_apl<<", nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie;
        cout<<"Data lansare: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<", data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: "<<pret<<endl;
    }
    void afisare_inf()
    {
        cout<<"Nume: "<<nume<<"Versiune: "<<versiune<<"Categorie: "<<categorie<<endl;
        cout<<"Data lansarii: "<<data_lansare.get_luna()<<"/"<<data_lansare.get_an()<<"Data ultimului update: "<<data_update.get_luna()<<"/"<<data_update.get_an()<<endl;
        cout<<"Pret: ";
        if(free)
            cout<<"Gratis\n";
        else cout<<pret<<", discount cu abonament: "<<discount<<"%\n";
    }
    bool get_free(){ return free;}
    int get_pret_disc(){ return pret-(pret*discount/100);}
    int get_pret_nodisc(){ return pret;}
    int get_discount(){ return discount;}
    int get_id(){ return id_apl;}
    String get_nume(){ return nume;}
};
Aplicatie** arr=new Aplicatie*[3];
class Utilizator{
    String nume_util,parola;
    IntVector ls_aplicatii;
    Portofel wallet;
    bool abonament;
    int zile_abon_ramase;
public:
    Utilizator():nume_util(),parola(),ls_aplicatii(),wallet(),abonament(0),zile_abon_ramase(0){ cout<<"s-a creat utilizatorul vid\n";};
    Utilizator(const char* n,const char* p,const char* nu, int nr, int C, int s,  int z, int a):nume_util(n),parola(p),ls_aplicatii(),wallet(nu,nr,C,s,z,a),abonament(0),zile_abon_ramase(0)
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Utilizator util1("Utilizator_test","parola\n","Popescu Ion",12345678,123,5000,1,2001); //creare cont implicit
    Aplicatie ap1("calendarul","114","Instrumente",2,2001,12,2014,1,1,0,0);
    *(arr+ap1.get_id())=&ap1;
    Aplicatie ap2("browser web","2.05","Instrumente",6,2016,03,2022,1,1,0,0);
    *(arr+ap2.get_id())=&ap2;
    Aplicatie ap3("solitaire premium","2.00","Jocuri",10,2003,11,2020,0,2,23,13);
    *(arr+ap3.get_id())=&ap3;
    //util1.creare_cont(); //creare cont custom
    //util1.get_wallet().adaugare_metoda(); //adaugare metoda de plata pt contul custom
    util1.adauga_bani(); //adaugare bani in cont
    //int x; cin>>x;
    //util1.get_wallet().get_card().set_sold_card(x); //setare sold card (metoda de plata)
    //util1.get_wallet().arata_sold_card(); //afisare sold card
    //cout<<util1.get_wallet().get_sold_wallet(); //afisare sold cont
    util1.verificare_abonament(); //verificare status abonament
    util1.instalare_apl(2); //instalare aplicatie
    util1.afisare_ls_apl(); //afisare ls aplicatii a clientului
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
bool String::operator ==(String &str)
{
    int i,n;
    n=max(length,str.length);
    for(i=0;i<n;i++)
        if(data[i]!=str.data[i])return 0;
    return 1;
}
String& String::operator=(const String& ob) //sir1=sir2
{
    if(this!=&ob)
        {
            int i;
            if(data!=nullptr)delete[] data;
            length=ob.length;
            data=new char[length];
            for(i=0;i<=length;i++)
                data[i]=ob.data[i];
            cout<<"sir original=sir nou\n";
            cout<<data<<endl;
        }
    return *this;
}
void String::addchar(char c,int x) //adauga caract c pe poz x in sir
{
    String temp; int i;
    temp.length=length+1;
    temp.data=new char[temp.length];
    temp.data[x]=c;
    for(i=0;i<=length;i++)
        {if(i>=x)temp.data[i+1]=data[i];
        else temp.data[i]=data[i];}
    length=temp.length;
    delete[] data;
    data=temp.data;
    cout<<"a fost adaugat caract "<<c<<" pe poz "<<x<<": "<<data<<endl;
}
void String::concat(String s) //concateneaza 2 siruri
{
    String temp1; int i;
    temp1.length=s.length+length;
    temp1.data=new char[temp1.length];
    for(i=0;i<=length;i++)
        temp1.data[i]=data[i];
    for(i=length;i<=temp1.length;i++)
        temp1.data[i]=s.data[i-length];
    length=temp1.length;
    delete[] data;
    data=temp1.data;
    cout<<"concatenarea sirurilor:"<<data<<endl;
}
ostream & operator << (ostream &out, const String& ob) //cout pt sir
{
    out<<ob.data<<endl;
    return out;
}
istream & operator >> (istream&in, String& ob) //cin pt sir
{
    if(ob.data!=nullptr)delete[] ob.data;
    char* new_data;
    new_data=new char[40];
    int i=0; char c;
    while(c!='\n')
    {
        c=getchar();
        new_data[i]=c;
        i++;
    }
    ob.length=i;
    ob.data=new char[ob.length];
    for(i=0;i<ob.length;i++)
        ob.data[i]=new_data[i];
    ob.data[ob.length]='\0';
    delete[] new_data;
    return in;
}
istream & operator >> (istream &in, Data& data_calend) //cin pt data calendaristica
    {
        cout<<"Introduceti luna:\n"; in>>data_calend.luna;
        cout<<"Introduceti anul:\n"; in>>data_calend.an;
        return in;
    }
istream & operator >> (istream &in, date_card& card1) //cin pt date card
 {
     cout<<"Introduceti numele de pe card "; in>>card1.nume_card;
     cout<<"Introduceti nr card "; in>>card1.nr_card; cout<<endl;
     cout<<"Introduceti CVC "; in>>card1.CVC; cout<<endl;
     cout<<"Introduceti data exp "; cout<<endl; in>>card1.data_exp; cout<<endl;
     cout<<"Introduceti sold card "; in>>card1.sold_card; cout<<endl;
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
void Portofel::adaugare_metoda(){ cin>>card;}
void Portofel::arata_sold_card(){ cout<<"Soldul tau este:"<<card.get_sold_card()<<endl;}
void Utilizator::adauga_bani()
    {
        int suma_ad; char c1='Y';
        String parol; int sold=wallet.get_card().get_sold_card();
        cout<<"Introduceti parola:\n";
        cin>>parol;
        while(c1=='Y')
        {
            if(parol==parola)
            {
                cout<<"Introduceti suma de adaugat: "; cin>>suma_ad; cout<<endl;
                sold=wallet.get_card().get_sold_card();
                if(suma_ad<=sold)
                {
                    wallet.set_sold_wallet(wallet.get_sold_wallet()+suma_ad);
                    wallet.get_card().set_sold_card(sold-suma_ad);
                    cout<<"Au fost adaugati "<<suma_ad<<" lei in portofel, iar soldul total este acum:"<<wallet.get_sold_wallet()<<endl;
                    cout<<"Doriti sa mai adaugati bani in portofel?(Y/N)";
                    cin>>c1;
                }
                else {cout<<"Suma de adaugat depaseste suma de bani de pe card. Tranzactie rereusita.\n"; c1='N';}
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
        char c; double nr_luni,suma_finala=0; String parol;
        if(abonament){ cout<<"Aveti "<<zile_abon_ramase<<" zile ramase pana la expirarea abonamentului\nDoriti sa il reinnoiti?(Y/N)\n";}
        else { cout<<"Nu aveti abonament. Doriti sa cumparati un abonament?(Y/N)\n"; }
        cin>>c;
        if(c=='Y')
        {
            cout<<"Selectati nr de luni de adaugat. 1 luna = 25 lei\n"<<"La fiecare luna adaugata aveti un discount de 5% din suma finala, pana la 50%.\n";
            cin>>nr_luni;
            suma_finala=nr_luni*25;
            suma_finala=suma_finala-min((suma_finala/2),(nr_luni*5/100));
            cout<<"Suma finala este:"<<suma_finala<<endl<<"Doriti sa faceti plata?{Y/N)";
            cin>>c; if(c=='N')return;
            if(wallet.get_sold_wallet()-suma_finala>=0)
            {
                wallet.set_sold_wallet(wallet.get_sold_wallet()-suma_finala);
                cout<<"Soldul ramas in cont este: "<<wallet.get_sold_wallet()<<endl;
            }
            else cout<<"Suma finala depaseste soldul contului. Tranzactie nereusita.\n";
        }
    }
void Utilizator::instalare_apl(int id_apl) //instalarea unei aplicatii (scadere pret din sold cont si adaugare id apl la lista apl utilizator)
    {
        char c;
        arr[id_apl]->afisare_inf();
        cout<<"Doriti sa instalati?(Y/N)";
        cin>>c;
        if(arr[id_apl]->get_free()==1)
        {
            ls_aplicatii.add_elem(id_apl);
            cout<<"Aplicatia s-a instalat cu succes\n";
        }
        else
        {
            if(arr[id_apl]->get_pret_nodisc()<=wallet.get_sold_wallet())
            {
                if(abonament==1)
                {
                    cout<<"Datorita abonamentului, aveti o reducere de"<<arr[id_apl]->get_discount()<<"%\n";
                    wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_disc());
                }
                else wallet.set_sold_wallet(wallet.get_sold_wallet()-arr[id_apl]->get_pret_nodisc());

            }
            ls_aplicatii.add_elem(id_apl);
            cout<<"Aplicatia s-a instalat cu succes\n"; return;
        }
    }
void Utilizator::afisare_ls_apl() //afisarea listei de apl a utilizatorului
{
    int i;
    for(i=0;i<ls_aplicatii.get_size();i++)
        arr[i]->afisare_inf();
}
