//
//  main.cpp
//  Inlämningsuppgift 2
//
//  Created by Jesper Sundin on 2021-07-22.
//


#include <iostream>
using namespace std;

int startNummer;
int ledandeStartNummer;
int antalTävlande;

int startTimme, startMinut, startSekund;
int målTimme, målMinut, målSekund;

int startTidSek, målTidSek;

int totTim, totMin, totSek, totTid;
int ledandeTidTim, ledandeTidMin, ledandeTidSek, ledandeTid = INT_MAX;

bool fortsättRegistrera = true;
bool registreringStartad = false;

int main() {
    
    // While-loop som körs medans fortsättRegistrera == true (Dvs så länge användaren inte matar in ett negativt tal som startnummer)
    while (fortsättRegistrera == true) {
        
        cout << "Startnummer?";
        cin >> startNummer;
        
        // Kontrollerar om användaren har matat in tävlande
        if (startNummer <=0 && registreringStartad == false) {
            fortsättRegistrera = false;
            cout << "Inga tävlande \n";
            cout << "Programmet avslutas" << endl;
        }
        
        // Kontrollerar om användaren är färdig med registreringen
        else if (startNummer <= 0) {
            fortsättRegistrera = false;
            cout << "Vinnare är startnr: " << ledandeStartNummer << "\n";
            cout << "Tim: " << ledandeTidTim << " Min: " << ledandeTidMin << " Sek: " << ledandeTidSek << "\n";
            cout << "Antal tävlande: " << antalTävlande << "\n";
            cout << "Programmet avslutas" << endl;
        }
        
        else {
            cout << "Starttid?";
            cin >> startTimme >> startMinut >> startSekund;
            
            cout << "Måltid?";
            cin >> målTimme >> målMinut >> målSekund;
            
            registreringStartad = true;
            antalTävlande++;
            
            // Beräknar måltid och starttid i enhet sekunder efter midnatt
            målTidSek = (målTimme * 3600) + (målMinut * 60 ) + målSekund;
            startTidSek = (startTimme * 3600) + (startMinut * 60) + startSekund;
            
            // Om måltiden är mindre än starttiden så innebär det att tävlande har sprungit över midnatt, då läggs det på ett dygn
            if (målTidSek < startTidSek) {
                målTidSek = målTidSek + (24 * 3600);
            }
            
            // Omvandlar tiden till sekunder
            totTid = målTidSek - startTidSek;
            
            // Kontrollerar om den aktuella tiden är den bästa tiden, och sprarar den om så är fallet
            if (totTid < ledandeTid) {
                ledandeStartNummer = startNummer;
                ledandeTid = totTid;
                ledandeTidTim = totTid / 3600;
                ledandeTidMin = ((totTid / 60) % 60) ;
                ledandeTidSek = totTid % 60;
                
            }
        }
    }
    
    return 0;
}


