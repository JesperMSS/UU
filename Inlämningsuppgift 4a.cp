
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

const int ANTAL_BOKSTAVER = 26;  //A-Z

// Funktionsdeklarationer
void berakna_histogram_abs(string textSträng, int antal[]);
void skriv_histogram_abs(int antal[]);

int main()
{
    int antal[ANTAL_BOKSTAVER] = {0};
    
    // Läs in en rad med text från tangentbordet
    string textSträng;
    cout << "Mata in en sträng \n";
    getline (cin,textSträng);
    
    berakna_histogram_abs(textSträng, antal);
    skriv_histogram_abs(antal);
    
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
// Funktionen skriv_histogram_abs
// Funktionen skriv_histogram_abs skriver ut den absoluta förekomsten för varje bokstav.
// Inparametern antal[] ska vid anrop innehålla den absoluta förekomsten för respektive bokstav.
void skriv_histogram_abs(int antal[]) {
    cout << "\nHistogram \n";
    // Loopar igenom antal-arrayen och skriver ut förekomsten av bokstäverna i histogrammet
    for (int i = 0;  i < ANTAL_BOKSTAVER; i++) {
        cout << (char) (i+'A') << " ";
        cout << antal[i] << "\n";
    }
}
