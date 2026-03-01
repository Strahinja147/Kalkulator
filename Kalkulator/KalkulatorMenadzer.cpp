#include "KalkulatorMenadzer.h"
using namespace std;

KalkulatorMenadzer::KalkulatorMenadzer(Istorija& istorija, vector<string>& vektorOperacija, vector<string>& tokenizovaniUnetiString)
    :istorija(istorija), vektorOperacija(vektorOperacija), tokenizovaniUnetiString(tokenizovaniUnetiString)// mora ovakav konstruktor jer radim sa referencama a ne sa kopijama
{
}

bool KalkulatorMenadzer::UradiNaredbu(const string& imeFajla)
{

    if (Validator::TekstJeValidan( vektorOperacija, tokenizovaniUnetiString))
    {
        
        unordered_map<string, std::function<bool()>> komande = {
            {"i", [&] {return istorija.IstorijaNaredbi(); }},
            {"u", [&] {return istorija.Undo(); }},
            {"r", [&] {return istorija.Redo(); }},
            {"s", [&] {return istorija.UpisiUFajl(imeFajla); }}
        };
        if (komande.contains(tokenizovaniUnetiString[0]))
        {
            if (!komande[tokenizovaniUnetiString[0]]())
            {
                return false;
            }
            else
            {
                cout << "Uspesno izvrena komanda: " << tokenizovaniUnetiString[0] << endl;
                return true;
            }
        }
        else
        {
            try {
                Racunanje racunanje;
                double rezultat = 0;
                rezultat = racunanje.IzracunajVrednostIzraza(tokenizovaniUnetiString);
                istorija.SacuvajIzrazUIstoriji(tokenizovaniUnetiString, rezultat);
                cout << "Rezultat izraza je: " << rezultat << endl;
            }
            catch (const char* porukaOGresci) {
                cout << "GRESKA: " << porukaOGresci << endl;
            }
        }

        return true;
    }
    else
    {
        cout << "Nisi uneo dobar izraz" << endl;
        return false;
    }
}
