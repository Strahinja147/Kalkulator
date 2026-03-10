#include "Istorija.h"

using namespace std;

bool Istorija::Undo()
{
    if (istorijaElemenata.empty()) {
        cout << "Nema elemenata za Undo!" << endl;
        return false;
    }

    redoStack.push_front(istorijaElemenata.front()); 
    istorijaElemenata.pop_front();                   

    return true;
}

bool Istorija::Redo()
{
    if (redoStack.empty()) {
        cout << "Nema elemenata u redo stack-u!" << endl;
        return false;
    }

    istorijaElemenata.push_front(redoStack.front()); 
    redoStack.pop_front();                           

    return true;
}

bool Istorija::IstorijaNaredbi() const
{
    if (istorijaElemenata.empty()) {
        cout << "Nema jos ni jednog elementa u istoriji!" << endl;
        return false;
    }

    for (const string& izraz : istorijaElemenata) {
        cout << izraz << endl;
    }

    return true;
}

void Istorija::SacuvajIzrazUIstoriji(const vector<string>& tokenizovaniString, double rezultat)
{
    redoStack.clear();

    string ceoIzraz = "";
    for (const string& token : tokenizovaniString) {
        ceoIzraz += token;
    }

    ceoIzraz += " = " + to_string(rezultat);

    istorijaElemenata.push_front(ceoIzraz);
}

bool Istorija::UpisiUFajl(const string& imeFajla) const
{
    if (istorijaElemenata.empty()) {
        cout << "Nema elemenata u istoriji za upis u fajl!" << endl;
        return false;
    }

    ofstream file(imeFajla);

    if (!file.is_open()) {
        cout << "Greska pri otvaranju fajla!" << endl;
        return false;
    }

    for (const string& izraz : istorijaElemenata) {
        file << izraz << endl;
    }

    return true;
}