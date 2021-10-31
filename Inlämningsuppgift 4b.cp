//
//  main.cpp
//  Inlämningsuppgift 4b
//
//  Created by Jesper Sundin on 2021-08-01.
//

#include <string>
#include <cctype>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Globala konstanter:
const int ANTAL_BOKSTAVER = 26;  //A-Z
const int ANTAL_SPRAK = 4;

// 2d-arrayen TOLK_HJALP innehåller bokstavsfrekvensen i %
// för fyra språk. TOLK_HJALP[0][0] är frekvensen av
// bokstaven a för engelska. TOLK_HJALP[0][25] är frekvensen av
// bokstaven z för engelska.
const double TOLK_HJALP[ANTAL_SPRAK][ANTAL_BOKSTAVER]=
{{8.27,1.48,2.94,4.03,11.78,2.22,1.72,6.77, //engelska
    7.39,0.12,0.81,3.76,2.85,6.71,7.79,1.54,
    0.05,5.95,6.69,9.07,2.66,1.13,2.14,0.19,
    1.89,0.03},
    {7.97,1.40,3.55,3.79,16.89,1.02,1.00,0.75, //franska
        7.08,0.38,0.04,5.51,2.82,8.11,5.19,2.78,
        1.01,6.69,8.35,7.22,6.09,1.35,0.02,0.54,
        0.30,0.15},
    {9.50,1.11,1.53,5.30,8.94,1.74,3.57,3.94,  //svenska
        3.98,0.89,3.26,4.93,3.41,8.46,5.01,1.77,
        0.00,6.73,5.56,9.20,1.94,2.42,0.00,0.05,
        0.45,0.00},
    {5.12,1.95,3.57,5.07,16.87,1.35,3.00,5.79, //tyska
        8.63,0.19,1.14,3.68,3.12,10.64,1.74,0.42,
        0.01,6.30,6.99,5.19,3.92,0.77,1.79,0.01,
        0.69,1.24}};

// Funktionsdeklarationer:
void berakna_histogram_abs(string textSträng, int antal[]);
void abs_till_rel (int antal[], double frekvens[]);
void skriv_histogram_abs(int antal[]);
void plotta_histogram_rel(double frekvens[]);
void tolkning(double frekvens[]);
string namn_pa_fil();
string inlasning(string filNamn);

int main()
{
    int antal[ANTAL_BOKSTAVER] = {0};
    double frekvens[ANTAL_BOKSTAVER] = {0};
    string filNamn;
    string textSträng;
    
    filNamn =  namn_pa_fil();
    textSträng = inlasning(filNamn);
    berakna_histogram_abs(textSträng, antal);
    abs_till_rel (antal, frekvens);
    plotta_histogram_rel(frekvens);
    tolkning(frekvens);
    
    return 0;
}

// Funktionsdefinitioner:

// Funktionen berakna_histogram_abs
// Funktionen beräknar ett histogram med den absoluta förekomsten av varje bokstav (A-Z) i given textsträng som ges som inparametern textSträng.
// Referensparametern antal[] kommer efter anrop att innehålla den absoluta förekomsten för respektive bokstav.
void berakna_histogram_abs(string textSträng, int antal[]) {
    int position_i_array;
    char aktuell_bokstav;
    // Loopar igenom inparametern textSträng och kontrollerar att det är en bokstav samt omvandlar den till en versal, sparas sedan i arrayen antal
    for (int i = 0;  i < textSträng.length(); i++) {
        aktuell_bokstav = textSträng.at(i);
        // Kontrollerar ifall det användaren matat in är en bokstav (Genom en kontroll av ASCII-koder), om så är fallet omvandlar den bokstaven till en versal
        if (isalpha(aktuell_bokstav)) {
            position_i_array = (int)toupper(aktuell_bokstav) - 'A';
            antal[position_i_array]++;
        }
    }
}

// Funktionen abs_till_rel
// Funktionen abs_till_rel omvandlar den absoluta frekvensen till relativa frekvenser i procent.
// Inparametern antal[] ska vid anrop innehålla den absoluta förekomsten för respektive bokstav.
// Referensparametern frekvens[] kommer efter anrop att innehålla den relativa frekvensen i procent för respektive bokstav.
void abs_till_rel (int antal[], double frekvens[]) {
    int totaltAntal = 0;
    cout << "Relativa frekvenser: \n";
    //Loopar igenom arrayen antal och adderar värdet i int totaltAntal
    for (int i = 0;  i < ANTAL_BOKSTAVER; i++) {
        totaltAntal = antal[i] + totaltAntal;
    }
    // Loopar igenom arrayen och castar antal och totaltAntal från en int till en double. Beräknar sedan den procentuella frekvensen
    for (int i = 0;  i < ANTAL_BOKSTAVER; i++) {
        frekvens[i] = 100*((double)antal[i] / (double)totaltAntal);
        printf("%c %lf \n", i + 'A', frekvens[i]);
    }
}

// Funktionen skriv_histogram_abs
// Funktionen skriv_histogram_abs skriver ut den absoluta förekomsten för varje bokstav.
// Inparametern antal[] ska vid anrop innehålla den absoluta förekomsten för respektive bokstav.
void skriv_histogram_abs(int antal[]) {
    cout << "\nHistogram: \n";
    // Loopar igenom antal-arrayen och skriver ut förekomsten av bokstäverna i histogrammet
    for (int i = 0;  i < ANTAL_BOKSTAVER; i++) {
        cout << (char) (i+'A') << " ";
        cout << antal[i] << "\n";
    }
}

// Funktionen plotta_histogram_rel
// Funktionen plotta_histogram_rel skriver ut en grafisk variant av den relativa frekvensen för varje bokstav.
// Inparametern frekvens[] ska vid anrop innehålla den relativa frekvensen i procent för respektive bokstav.
void plotta_histogram_rel(double frekvens[]) {
    cout << "\nHistogram: \n";
    // Loopar igenom ANTAL_BOKSTAVER-arrayen och skriver ut bokstäverna
    for (int i = 0;  i < ANTAL_BOKSTAVER; i++) {
        cout << (char) (i+'A') << " ";
        // Loopar igenom frekvens-arrayen och skriver ut frekvensen. Frekvensen multipliceras med två eftersom att två symboler motsvarar en procent.
        for (int y = 0; y < frekvens[i] * 2; y++) {
            cout << "*";
        }
        cout << "\n";
    }
}

//Funktionen tolkning
//Funktionen tolkning tar reda på vilket av en antal givna språk histogrammet överensstämmer mest med.
// Inparametern frekvens[] ska vid anrop innehålla den relativa frekvensen i procent för respektive bokstav.
void tolkning(double frekvens[]) {
    string spraknamn[ANTAL_SPRAK] = {"Engelska", "Franska", "Svenska", "Tyska"};
    double skillnad;
    double kvadratsumma=0;
    // __DBL_MAX__ motsvarar det maximala värdet för datatypen double
    double lagstKvadratsumma=__DBL_MAX__;
    int mestSannoliktSprak=-1;
    // For-loop som loopar igenom arrayen aktuelltSprak tills den är större än ANTAL_SPRAK-arrayen
    for(int aktuelltSprak=0; aktuelltSprak < ANTAL_SPRAK; aktuelltSprak++)
    {
        kvadratsumma=0;
        // For-loop som loopar igenom inten i tills den är större än ANTAL_BOKSTAVER-arrayen.
        for(int i=0; i<ANTAL_BOKSTAVER; i++)
        {
            skillnad=TOLK_HJALP[aktuelltSprak][i] - frekvens[i];
            kvadratsumma =kvadratsumma + (skillnad * skillnad);
        } // Om kvadratsumma är lägre än den hittills lägsta kvadratsumman så sätts aktuell kvadratsumma som den nya lägsta kvadratsumman samtidigt som det aktuella språket sätts som det mest sannolika språket
        if (kvadratsumma < lagstKvadratsumma)
        {
            lagstKvadratsumma = kvadratsumma;
            mestSannoliktSprak = aktuelltSprak;
        }
    }
    cout << "Mest sannolikt: " << spraknamn[mestSannoliktSprak] << endl;
}

// Funktionen namn_pa_fil
// Funktionen namn_pa_fil låter användaren ange ett filnamn och kontrollerar ifall användaren har angett ett filnamn som slutar på ".txt", annars läggs det till.
// Funktionen returnerar filnamnet.
string namn_pa_fil() {
    string filNamn;
    string txt = ".txt";
    
    cout << "Mata in ett filnamn: \n";
    getline(cin, filNamn);
    // Söker efter "txt" i filnamnet
    size_t match = filNamn.rfind(txt);
    
    // Om "txt" inte hittades i filnamnet så läggs det till
    if(match == string::npos)
    {
        filNamn = filNamn + txt;
    }
    
    return filNamn;
}

// Funktionen inlasning
// Funktionen inlasning öppnar filen och läser in filens innehåll i en sträng.
// Inparametern filNamn innehåller filnamnet som ska läsas in
// Funktionen returnerar en textsträng med innehållet från filen
string inlasning(string filNamn) {
    string textSträng;
    char tecken;
    ifstream inFile;
    
    // Öppnar angivet filnamn
    //Filen måste ligga i debugg-mappen. Sökvägen för Mac är följande:
    //Users/Ditt användarnamn/Library/Developer/Xcode/DerivedData/Build/Products
    inFile.open(filNamn);
    //Kontrollerar om filen öppnades korrekt
    if (inFile.is_open()) {
        // Läser in filens tecken och lagrar den i strängen textSträng
        while (inFile.get(tecken)) {
            textSträng.push_back(tecken);
        }
    }
    
    else {
        cout << "\n" << "Hittar ingen fil med angivet filnamn" << "\n";
    }
    return textSträng;
}


