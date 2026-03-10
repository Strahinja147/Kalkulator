#include "Parser.h"
using namespace std;



bool Parser::IsInteger(vector<string>::iterator s)
{
    const string& pomocna = *s;// prvo moram da dereferenciram iterator, tek sada u pomocna imam string koji mi je poslat
    //if (velicinaVektora == 0) return false;
    for (size_t i = 0; i < pomocna.size(); ++i) {
        if (!isdigit(pomocna[i])) return false;
    }
    return true;
}

vector<string> Parser::Tokenizuj(const string& stringZaTokenizaciju)// metoda parsiraj ce pozove ovu metodu u svom prvom koraku
{
    // ako je prvi token koji se ovde napravi operaija onda ce setujemo vrednost validan tekst koju cu da napravim kao bool argument klase na false i ako su dva operatora ili dva broja za redom dodate isto i tada se setuje na false, znam da se malo to ne uklapa u ovu metodu ali sta je tu je
    // za undo i redo verovatno moze samo da se proveri da li je strintZaTokenizaciju == "undo" || strintZaTokenizaciju == "redo" i ako jeste odma ceo string da se gurne kao token
    vector<string> tokeni;
    string trenutno;

    for (int i = 0; i < stringZaTokenizaciju.length(); i++)
    {
        char ch = stringZaTokenizaciju[i];

        if (isspace(ch))
            continue;// ako smo naisli na blnako znak preskacemo ovu iteraciju petlje
        else if (isdigit(ch))
        {
            trenutno += ch; //pravimo broj
        }
        else
        {
            if (!trenutno.empty())// ako ima imamo broj u stringu ubaci ga u vektor tokena i spremi pomocnu za novi broj
            {
                tokeni.push_back(trenutno);
                trenutno.clear();
            }
            
            string operacija(1, ch);// plus minus puta podeljeno
            tokeni.push_back(operacija); // dodajemo operaciju u vektor tokena
        }
    }

    if (!trenutno.empty())
        tokeni.push_back(trenutno);

    return tokeni;
}

vector<string> Parser::Parsiraj(const string& stringZaParsiranje, vector<int>& vektorBrojeva, vector<string>& vektorOperacija)
{
    vector<string> tokenizovaniString = Tokenizuj(stringZaParsiranje);
    //int brojTokena = tokenizovaniString.size();
    for (vector<string>::iterator token = tokenizovaniString.begin(); token != tokenizovaniString.end(); token++)
    {
        if (IsInteger(token))
        {
            string izvuceniToken = *token;
            int izvuceniBroj = stoi(izvuceniToken);
            vektorBrojeva.emplace_back(izvuceniBroj);
        }
        else
        {
            string izvuceniToken = *token;
            vektorOperacija.emplace_back(izvuceniToken);
        }
    }
    return tokenizovaniString;
}
