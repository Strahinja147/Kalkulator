#include <iostream>
#include <string>
#include <cctype>
#include"Parser.h"
#include "KalkulatorMenadzer.h"
using namespace std;


void PrikaziUputstvo(const string& imeFajla) {
    cout << "\n===========================================" << endl;
    cout << "           MATEMATICKI KALKULATOR          " << endl;
    cout << "===========================================" << endl;
    cout << " Mozete uneti matematicki izraz (npr. 5 + 3 * 2)" << endl;
    cout << " Podrzani operatori: +, -, *, /, ( )" << endl;
    cout << "\n Specijalne komande:" << endl;
    cout << "  'i' - Prikaz istorije svih rezultata" << endl;
    cout << "  'u' - Undo (ponisti zadnju akciju)" << endl;
    cout << "  'r' - Redo (vrati ponistenu akciju)" << endl;
    cout << "  's' - Sacuvaj istoriju u tekstualni fajl (" << imeFajla << ")" << endl;
    cout << "===========================================\n" << endl;
}

int main() {
    try
    {
        string input;
        Parser parser;
        Istorija istorija;
        bool tacnoUnetIzraz = false;
        bool novoRacunanje = true;
        string imeFajla;
        std::cout << "Unesite ime fajla u kome ce da se cuvaju izrazi: ";
        getline(cin, imeFajla);
        PrikaziUputstvo(imeFajla);
        string zeljaZaNovimRacunanjem = "";
        while (novoRacunanje == true)
        {
            while (!tacnoUnetIzraz)
            {
                std::cout << "Unesesite izraz: ";
                getline(cin, input);
                vector<int> vektorBrojeva;
                vector<string> vektorOperacija;
                vector<string> tokenizovaniUnetiString;
                tokenizovaniUnetiString = parser.Parsiraj(input, vektorBrojeva, vektorOperacija);
                KalkulatorMenadzer kalkulatorMenadzer(istorija, vektorOperacija, tokenizovaniUnetiString);
                tacnoUnetIzraz = kalkulatorMenadzer.UradiNaredbu(imeFajla);
            }

            std::cout << "Da li zelite jos nesto da izracunete, ako zelite ukucajte 'da' ako ne zlite ukucajte 'ne'!" << endl;
            getline(cin, zeljaZaNovimRacunanjem);
            if (zeljaZaNovimRacunanjem == "da")
            {
                novoRacunanje = true;
                tacnoUnetIzraz = false;
            }
            else if (zeljaZaNovimRacunanjem == "ne")
            {
                novoRacunanje = false;
            }
            else
            {
                std::cout << "Uneiste validnu komandu!" << endl;
            }
        }
        std::cout << "Hvala sto ste koristili ovaj kalkulator :)" << endl;
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Sistemska greska: " << e.what() << std::endl;
    }
}