#include <iostream>
#include <cstring>
#include <vector>
#include <typeinfo>
#define N 10000

using namespace std;


class Accesoriu /// clasa de baza
{
protected:
    string nume, culoare;
    double pret;
    int id;

public:
    virtual void citire()
    {
        cout << "Accesoriul: ";
        cin >> nume >> culoare >> pret >> id;
    }

    virtual void afisare()
    {
        cout << nume <<" "<< culoare<<" " << pret <<" "<< id<<" ";
    }

    /// CONSTRUCTORS AND DISTRUCTOR
    Accesoriu(string Nume="anonim", string Culoare="neutru", double Pret=0.0, int Id=0) //constructor de initializare parametrizat
    {
        nume = Nume;
        culoare = Culoare;
        pret = Pret;
        id = Id;
    }

    Accesoriu() // Constructor gol
    {
        nume = "";
        culoare = "";
        pret = 0.0;
        id = 0;
    }

    Accesoriu(const Accesoriu& ob) // constructor de copiere
    {
        nume = ob.nume;
        culoare = ob.culoare;
        pret = ob.pret;
        id = ob.id;
    }

     ~Accesoriu() // destructor
    {
        /*nume="", culoare="", pret=0.0, id = 0;*/
        cout << "accesoriu distrus"<<"\n";
    }



    friend ostream& operator<<(ostream& out, Accesoriu& ob); //afisare
    friend istream& operator>>(istream& in, Accesoriu& ob); //citire
    virtual Accesoriu& operator=(Accesoriu&); /// va fi declarata si in alte clase


};



class Palarie :  public Accesoriu
{
protected:
    char size; // care poate fi  S M L

public:
    ///Palarie(): Accesoriu() {size = 'X';}
    Palarie(string Nume="anonim", string Culoare="neutru", double Pret=0.0, int Id=0, char Size='X') : Accesoriu(Nume, Culoare, Pret, Id) { size = Size;}
    Palarie(const Palarie &ob) : Accesoriu(ob) {size = ob.size;} /// Constructor de copiere
    ~Palarie()   { /*cout << "palarie distrusa"<<"\n"; */ }
    void citire() { Accesoriu::citire(); cin >> size;}
    void afisare() { Accesoriu::afisare(); cout << size;}
    Palarie& operator=(Palarie&);
    friend ostream& operator<<(ostream& out, Palarie& ob);
    friend istream& operator>>(istream& in, Palarie& ob);


};



class Ochelari : public Accesoriu
{
protected:
    string forma; /// hexagon, cerc, dreptunghi

public:
    ///Ochelari() : Accesoriu() { forma = "neutru";}
    Ochelari(string Nume="anonim", string Culoare="neutru", double Pret=0.0, int Id=0, string Forma="neutru") : Accesoriu(Nume, Culoare, Pret, Id) { forma = Forma;}
    Ochelari(const Ochelari &ob) : Accesoriu(ob) { forma = ob.forma;}  ///Constructor de copiere
    ~Ochelari() {cout <<"ochelari distrusi"<<"\n";}

    void citire() {Accesoriu::citire(); cin >> forma;}
    void afisare() {Accesoriu::afisare(); cout << forma;}
    Ochelari& operator=(Ochelari&);
    friend ostream& operator<<(ostream& out, Ochelari& ob);
    friend istream& operator>>(istream& in, Ochelari& ob);


};

class Client
{
protected:
    string nume;
    double pay;
public:
    Client(string Nume="Anonim", double Pay = 0.0)
    {
        nume = Nume;
        pay = Pay;
    }
    Client( const Client &ob)
    {
        nume = ob.nume;
        pay = ob.pay;
    }

    ~Client()
    {
        cout << "a disparut clientul"<<"\n";
    }

    friend ostream& operator<<(ostream& out, Client&);
    friend istream& operator>>(ifstream& in, Client&);
    Client& operator=(Client&);

};


/// CLASA ABSTRACTA = o clasa care contine cel putin o functie virtuala pura
class Angajat
{
protected:
    string nume_angajat;
    int salariu_lunar, raion_accesoriu;
    //radionul poate avea valoarea 1 pentru palarie si 2 pentru ochelari

public:
    Angajat()
    {
        nume_angajat = "Anonim";
        salariu_lunar = 0;
        raion_accesoriu = 0;
    }

    Angajat(string Nume_angajat = "Anonim", int Salariu = 0, int Raion_accesoriu = 0)
    {
        nume_angajat = Nume_angajat;
        salariu_lunar = Salariu;
        raion_accesoriu = Raion_accesoriu;
    }

    Angajat( Angajat& ob)
    {
        nume_angajat = ob.nume_angajat;
        salariu_lunar = ob.salariu_lunar;
        raion_accesoriu = ob.raion_accesoriu;
    }
    ~Angajat()
    {
        cout << "Angajatul a plecat acasa"<<"\n";
    }

    ///functie virtuala pentru Clasa abstracta
    virtual void start() = 0
    {
        cout <<"Buna, cu ce pot sa te ajut?";
    }

    friend ostream& operator<<(ostream& out, Angajat&);
    friend istream& operator>>(ifstream& in, Angajat&);
    Angajat& operator=(Angajat&);


};



class Boutique
{
    vector <Accesoriu> accesorii;
    vector <Client> clienti;
    vector <Angajat> angajati;
    int numarAccesorii;

public:
    Boutique(Accesoriu *aux, int n) /// Constructor de initializare cu parametrii
    {
        numarAccesorii = n;
        for(int i=0; i<n; i++)
        {
            Accesoriu accesoriu(aux[i]);
            accesorii.push_back(accesoriu);
        }
    }

    Boutique() /// constructor de initializare fara parametrii
    {
        numarAccesorii = 0;
    }


    ~Boutique()
    {
        numarAccesorii = 0;
        vector <Accesoriu>().swap(accesorii);
        cout << "Magazin distrus" <<"\n";
    }


};



int main()
{
    vector<Accesoriu*> a;
    int n;
    cout << "Introdu numarul de accesorii: ";
    cin >> n;
    for(int i=0; i<n; i++)
    {
        cout <<"Tip de Accesoriu: 1 - Palarie; 2 - Ochelari"<<"\n";
        int op;
        cin >> op;
        switch(op)
        {
            case 1: {a.push_back(new Palarie()); break;}
            case 2: {a.push_back(new Ochelari()); break;}
        }
    }


    for(auto p = a.begin(); p != a.end(); p++)
        (**p).citire();

    /// afisare palarii
    for(auto p = a.begin(); p!=a.end(); p++)
        if(typeid(**p) == typeid(Palarie)) cout << *dynamic_cast<Palarie*>(*p);

    /// afisare ochelari
    for(auto p = a.begin(); p!=a.end(); p++)
        if(typeid(**p) == typeid(Ochelari)) cout << *dynamic_cast<Ochelari*>(*p);



    return 0;
}


///clasa Accesoriu
Accesoriu& Accesoriu::operator=(Accesoriu &ob)  {

    if(this!=&ob)
    {
        this -> nume = ob.nume;
        this -> culoare = ob.culoare;
        this -> id = ob.id;
        this -> pret = ob.pret;
    }

    return *this;
}
ostream& operator<<(ostream& out, Accesoriu& ob)
{
    out << ob.nume <<" "<< ob.culoare <<" "<< ob.pret <<" "<<ob.id << " ";
    return out;
}
istream& operator>>(istream& in, Accesoriu& ob)
{
    in >> ob.nume >> ob.culoare >> ob.pret >> ob.id;
    return in;
}

// clasa Palarie

Palarie& Palarie::operator=( Palarie& ob)
{
    if(this != &ob)
    {
        this-> Accesoriu::operator=(ob);
        this ->size = ob.size;
    }
    return *this;
}
ostream& operator<<(ostream& out, Palarie& ob)
{
    out << dynamic_cast <Accesoriu&> (ob);
    out << "Marimea " << ob.size<< endl;
    return out;
}
istream& operator>>(istream& in, Palarie& ob)
{
    in >> dynamic_cast <Accesoriu&> (ob);
    in >> ob.size;
    return in;
}

// clasa Ochelari
Ochelari& Ochelari::operator=(Ochelari& ob)
{
    if(this != &ob)
    {
        this -> Accesoriu::operator=(ob);
        this -> forma = ob.forma;
    }
    return *this;
}
ostream& operator<<(ostream& out, Ochelari& ob)
{
    out << dynamic_cast <Accesoriu&> (ob);
    out <<"Forma " << ob.forma << endl;
    return out;
}
istream& operator>>(istream& in, Ochelari& ob)
{
    in >> dynamic_cast <Accesoriu&> (ob);
    in >> ob.forma;
    return in;
}

///Client
ostream& operator<<(ostream& out, Client& ob)
{
    out << "Numele clientului este: " << ob.nume <<" si plateste  " << ob.pay;
    return out;
}

istream& operator>>(istream& in, Client& ob)
{
    in >> ob.nume >> ob.pay;
    return in;
}

Client& Client::operator=(Client& ob)
{
    if(this != ob)
    {
        this -> nume = ob.nume;
        this -> pay = ob.pay;
    }
    return *this;
}

///Angajat
ostream& operator<<(ostream& out, Angajat& ob)
{
    out << "Numele angajatului este: " << ob.nume_angajat <<",primeste lunar  " << ob.salariu_lunar<<" si se ocupa de raionul de "<< ob.raion_accesoriu;
    return out;
}

istream& operator>>(istream& in, Angajat& ob)
{
    in >> ob.nume_angajat >> ob.salariu_lunar >> ob.raion_accesoriu;
    return in;
}

Angajat& Angajat::operator=(Angajat& ob)
{
    if(this != ob)
    {
        this -> nume_angajat = ob.nume_angajat;
        this -> salariu_lunar = ob.salariu_lunar;
    }
    return *this;
}