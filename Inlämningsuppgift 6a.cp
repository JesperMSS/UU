//
//  main.cpp
//  Inlämningsuppgift_6
//
//  Created by Jesper Sundin on 2021-08-19.
//
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

//Konstant integers för max_personer och max_transaktioner
const int MAX_PERSONER = 10;
const int MAX_TRANSAKTIONER = 30;

// Klassdeklarationer och variabeldeklarationer
class Person {
private:
    string namn;           // Namn på person
    double betalat_andras; // Ligger ute med totalt
    double skyldig;        // Skyldig totalt
    
public:
    Person();
    Person(const string &namn, double betalat_andras, double skyldig);
    string hamtaNamn();
    double hamtaBetalat();
    double hamtaSkyldig();
    void skrivUt(ostream &os);
};

class Transaktion {
private:
    string datum;
    string typ;
    string namn;
    double belopp;
    int    antal_kompisar;
    string kompisar[MAX_PERSONER];
    
public:
    Transaktion();
    ~Transaktion();
    string hamtaNamn();
    double hamtaBelopp();
    int    hamtaAntalKompisar();
    bool   finnsKompis(const string &namnet);
    bool   lasIn(istream &is);
    void   skrivUt(ostream &os);
    void   skrivTitel(ostream &os);
};

class PersonLista {
private:
    int antal_personer;
    Person personer[MAX_PERSONER];
    
public:
    PersonLista();
    ~PersonLista();
    void laggTill(Person ny_person);
    void skrivUtOchFixa(ostream &os);
    double summaSkyldig();
    double summaBetalat();
    bool   finnsPerson(const string& namn);
};

class TransaktionsLista {
private:
    int antalTransaktioner = 0;
    Transaktion transaktioner[MAX_TRANSAKTIONER];
    
public:
    TransaktionsLista();
    ~TransaktionsLista();
    void lasIn(istream & is);
    void skrivUt(ostream & os);
    void laggTill(Transaktion & t);
    double totalKostnad();
    double liggerUteMed(const string &namnet);
    double arSkyldig(const string &namnet);
    PersonLista fixaPersoner();
};

int main()
{
    cout << "Startar med att läsa från en fil." << endl;
    
    TransaktionsLista transaktioner;
    std::ifstream is("resa.txt");
    transaktioner.lasIn(is);
    
    int operation = 1;
    while (operation != 0)
    {
        cout << endl;
        cout << "Välj i menyn nedan:" << endl;
        cout << "0. Avsluta. Alla transaktioner sparas på fil." << endl;
        cout << "1. Skriv ut information om alla transaktioner." << endl;
        cout << "2. Läs in en transaktion från tangentbordet." << endl;
        cout << "3. Beräkna totala kostnaden." << endl;
        cout << "4. Hur mycket ärr en viss person skyldig?" << endl;
        cout << "5. Hur mycket ligger en viss person ute med?" << endl;
        cout << "6. Lista alla personer mm och FIXA" << endl;
        
        cin >> operation;
        cout << endl;
        
        switch (operation)
        {
            case 1:
            {
                transaktioner.skrivUt(cout);
                break;
            }
            case 2:
            {
                Transaktion transaktion;
                cout << "Ange transaktion i följande format" << endl;
                transaktion.skrivTitel(cout);
                transaktion.lasIn(cin);
                transaktioner.laggTill(transaktion);
                break;
            }
            case 3:
            {
                cout << "Den totala kostnanden för resan var "
                << transaktioner.totalKostnad() << endl;
                break;
            }
            case 4:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ar_skyldig = transaktioner.arSkyldig(namn);
                if (ar_skyldig == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " är skyldig " << ar_skyldig << endl;
                break;
            }
            case 5:
            {
                cout << "Ange personen: ";
                string namn;
                cin >> namn;
                double ligger_ute_med = transaktioner.liggerUteMed(namn);
                if (ligger_ute_med == 0.)
                    cout << "Kan inte hitta personen " << namn << endl;
                else
                    cout << namn << " ligger ute med " << ligger_ute_med << endl;
                break;
            }
            case 6:
            {
                cout << "Nu skapar vi en personarray och reder ut det hela!" << endl;
                PersonLista lista = transaktioner.fixaPersoner();
                lista.skrivUtOchFixa(cout);
                break;
            }
        }
    }
    
    std::ofstream os("transaktioner.txt");
    transaktioner.skrivUt(os);
    
    return 0;
}

// Konstruktor för klassen Person
Person::Person() {
    
};

Person::Person(const string &pNamn, double pBetalat_andras, double pSkyldig) {
    namn = pNamn;
    betalat_andras = pBetalat_andras;
    skyldig = pSkyldig;
};

// Get-metod för att hämta ett namn
string Person::hamtaNamn() {
    return namn;
}

// Get-metod för att hämta vad en person har betalat för andra
double Person::hamtaBetalat() {
    return betalat_andras;
}

// Get-metod för att hämta vad en person är skyldig andra
double Person::hamtaSkyldig() {
    return skyldig;
}

// Metod för att skriva vad en person ligger ute och är skyldig andra
void Person::skrivUt(ostream &os) {
    os << namn << " ligger ute med " << betalat_andras << " och är skyldig " << skyldig << ".";
    if (betalat_andras - skyldig >= 0) {
        os << " Skall ha tillbaka " << betalat_andras - skyldig << " från potten! \n";
    }
    else {
        os << " Skall lägga " << skyldig - betalat_andras  << " till potten! \n";
    }
}

// Konstruktor för klassen Transaktion
Transaktion::Transaktion() {
}

// Destruktor för klassen Transaktion
Transaktion::~Transaktion() {
}

// Get-metod för att hämta namn
string Transaktion::hamtaNamn() {
    return namn;
}

// Get-metod för att hämta belopp
double Transaktion::hamtaBelopp () {
    return belopp;
}

// Get-metod för att hämta antal kompisar som är inblandade i en transaktion
int Transaktion::hamtaAntalKompisar()  {
    return antal_kompisar;
}

// Metod för att kontrollera om kompis förekommer som kompis på en transaktion
bool Transaktion::finnsKompis(const string &namnet) {
    bool hittad = false;
    for (int i = 0; i < antal_kompisar; i++) {
        if (!namnet.compare(kompisar[i])) {
            hittad = true;
        }
    }
    return hittad;
}

// Metod för att skriva ut titlar i listan
void Transaktion::skrivTitel(ostream &os) {
    os << "datum" << "\t" << "typ" << "\t" << "namn" << "\t" << "belopp" << "\t" << "Antal och lista av kompisar" << "\t";
}

// Metod som skriver ut data kring varje transaktion
void Transaktion::skrivUt(ostream &os) {
    os << datum << "\t" << typ << "\t" << namn << "\t" << belopp << "\t" << antal_kompisar << "\t";
    for (int i = 0; i < antal_kompisar; i++) {
        os << kompisar[i] << " ";
    }
    os << "\n";

}

// Metod som läser in data som en transaktion
bool Transaktion::lasIn(istream &is) {
    is >> datum;
    is >> typ;
    is >> namn;
    is >> belopp;
    is >> antal_kompisar;
    for (int i = 0; i < antal_kompisar; i++) {
        is >> kompisar[i];
    }
    return !is.eof();
}

// Konstruktor för klassen PersonLista
PersonLista::PersonLista() {
    antal_personer = 0;
}

// Destruktor för klassen PersonLista
PersonLista::~PersonLista() {
}

// Lägger till en ny person i arrayen
void PersonLista::laggTill(Person ny_person) {
    personer[antal_personer] = ny_person;
    antal_personer++;
}

// Skriver ut data om varje element i person-arrayen
void PersonLista::skrivUtOchFixa(ostream &os) {
    for (int i = 0; i < antal_personer; i++) {
        personer[i].skrivUt(os);
    }
}

// Summan av skulder för en person
double PersonLista::summaSkyldig() {
    double summaSkulder = 0.0;
    for (int i = 0; i < antal_personer; i++) {
        summaSkulder = summaSkulder + personer[i].hamtaSkyldig();
    }
    return summaSkulder;
}

// Summan av vad en person betalat
double PersonLista::summaBetalat() {
    double summaBetalat = 0.0;
    for (int i = 0; i < antal_personer; i++) {
        summaBetalat = summaBetalat + personer[i].hamtaBetalat();
    }
    return summaBetalat;
}

// Kontrollerar om en specifik person finns med i person-arrayen
bool PersonLista::finnsPerson(const string& namn){
    bool finns = false;
    for (int i = 0; i < antal_personer; i++) {
        if (namn == personer[i].hamtaNamn()){
            finns= true;
        }
    }
    return finns;
}

// Konstruktor för klassen TransaktionsLista
TransaktionsLista::TransaktionsLista() {
}

// Destruktor för klassen TransaktionsLista
TransaktionsLista::~TransaktionsLista() {
}

// Metod som läser in en rad ur en transaktionslista
void TransaktionsLista::lasIn(istream & is) {
    Transaktion transaktionen;
    while(transaktionen.lasIn(is)) {
        laggTill(transaktionen);
    }
}

// Metod som skriver ut alla transaktioner i en transaktionslista
void TransaktionsLista::skrivUt(ostream & os) {
    for(int i = 0; i < antalTransaktioner; i++) {
        transaktioner[i].skrivUt(os);
    }
}

// Metod som lägger till en transaktion i transaktionslistan
void TransaktionsLista::laggTill(Transaktion &t) {
    transaktioner[antalTransaktioner] = t;
    antalTransaktioner++;
}

// Metod som beräknar den totala kostnaden för hela resan
double TransaktionsLista::totalKostnad() {
    double kostnad = 0.0;
    for (int i = 0; i < antalTransaktioner; i++) {
        kostnad = kostnad + transaktioner[i].hamtaBelopp();
    }
    return kostnad;
}

// Metod som beräknar vad en person ligger ute med
double TransaktionsLista::liggerUteMed(const string &namnet) {
    double summa = 0.00;
    for (int i = 0; i < antalTransaktioner; i++)
        if (transaktioner[i].hamtaNamn() == namnet)
            summa += transaktioner[i].hamtaBelopp() * (1.0 - 1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
    return summa;
}

// Metod som beräknar vad en person är skyldig
double TransaktionsLista::arSkyldig(const string &namnet) {
    double summa = 0.00;
    for (int i = 0; i < antalTransaktioner; i++) {
        if (transaktioner[i].finnsKompis(namnet)){
            summa += transaktioner[i].hamtaBelopp() * (1.0 / (transaktioner[i].hamtaAntalKompisar() + 1));
        }
    }
    return summa;
}

// Skapar en personlista över samtliga personer som förekommer i transaktionslistan
PersonLista TransaktionsLista::fixaPersoner() {
    PersonLista personLista;
    string personNamn;
    double personSkuld = 0.0;
    double personBetalat = 0.0;
    
    for(int i = 0; i < antalTransaktioner; i++)
    {
        if(!personLista.finnsPerson(transaktioner[i].hamtaNamn()))
        {
            personNamn = transaktioner[i].hamtaNamn();
            personSkuld = arSkyldig(personNamn);
            personBetalat = liggerUteMed(personNamn);
            
            Person nyPerson = Person(personNamn, personBetalat, personSkuld);
            personLista.laggTill(nyPerson);
        }
    }
    return personLista;
}
