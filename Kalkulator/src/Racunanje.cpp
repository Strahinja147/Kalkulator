#include "Racunanje.h"
using namespace std;

double Racunanje::IzracunajVrednostIzraza(vector<string>& tokenizovaniUnetiString)
{
    double konacanRezultatRacunanja = 0;

    konacanRezultatRacunanja = ShuntingYardAlgoritam(tokenizovaniUnetiString);

    return konacanRezultatRacunanja;
}

double Racunanje::ShuntingYardAlgoritam(vector<string>& tokenizovaniUnetiString)
{
    double konacanRezultatRacunanja = 0;

    struct sOperator
    {
        int prvenstvo = 0;// njgovo prvenstvo, odnosno starost tipa mnozenje je starije od sabiranja
        int brojArgumenata = 0; // sa koliko argumenata radi, na primer mnozenje radi sa dva
    };

    unordered_map<string, sOperator> mapaOperatora;
    mapaOperatora["/"] = { 4, 2 };// deljenje je najstarija operacija
    mapaOperatora["*"] = { 3,2 };
    mapaOperatora["+"] = { 2,2 };
    mapaOperatora["-"] = { 1,2 };

    struct sSimbol
    {
        string simbol = "";

        enum class TipSimbola
        {
            Nepoznato,
            LiteralNumeric,
            Operator,
            OtvorenaZagrada,
            ZatvoranaZagrada,

        } tip = TipSimbola::Nepoznato;

        sOperator op;
    };

    deque<sSimbol> stkHolding;
    deque<sSimbol> stkOutput;

    
    for (auto token = tokenizovaniUnetiString.begin(); token != tokenizovaniUnetiString.end(); token++)
    {
        if (Parser::IsInteger(token))
        {
            //push-ujemo brojeve pravo na output
            stkOutput.push_back({ *token, sSimbol::TipSimbola::LiteralNumeric });
        }
        else if (*token == "(")
        {
            stkHolding.push_front({ *token, sSimbol::TipSimbola::OtvorenaZagrada });
        }
        else if (*token == ")")
        {
            while (!stkHolding.empty() && stkHolding.front().tip != sSimbol::TipSimbola::OtvorenaZagrada)
            {
                stkOutput.push_back(stkHolding.front());
                stkHolding.pop_front();
            }

            if (stkHolding.empty())
            {
                cout << "Greska sa zagradama shunting yard" << endl;
            }

            if (!stkHolding.empty() && stkHolding.front().tip == sSimbol::TipSimbola::OtvorenaZagrada)
            {
                stkHolding.pop_front();//moze da se desi da je potrebna zatvorena zagrada gore
            }
        }
        else if (mapaOperatora.find(*token) != mapaOperatora.end())// ako postoji taj kljuc onda vraca njega a ako vrati kraj mape, odnosno ako nije vratio kraj znaci da taj kljuc postoji
        {
            //Token je operator
            const auto& noviOperator = mapaOperatora[*token];

            while (!stkHolding.empty() && stkHolding.front().tip != sSimbol::TipSimbola::OtvorenaZagrada)// dokle god stek nije prazan mi radimo ovo
            {
                //provera da li je na pocetku steka operator, jer sta ako je zagrada ili tako nesto (nisu samo brojevi i operatori)
                if (stkHolding.front().tip == sSimbol::TipSimbola::Operator)
                {
                    const auto& holdingStekOperator = stkHolding.front().op;// uzimao sta trenutno na vrhu steka
                    if (holdingStekOperator.prvenstvo >= noviOperator.prvenstvo)
                    {
                        stkOutput.push_back(stkHolding.front());// ako ispunjava uslov operator se izbacuje na output
                        stkHolding.pop_front();// i sklanja se sa vrha prvremenog steka
                    }
                    else
                        break;
                }
            }

            stkHolding.push_front({ *token, sSimbol::TipSimbola::Operator, noviOperator });
        }
    }
    while (!stkHolding.empty())// ako je nesto ostalo u holding steku samo ga prebacuje u autput stek
    {
        stkOutput.push_back(stkHolding.front());
        stkHolding.pop_front();
    }

  /*  cout << "Pisem iz shunting yarda!" << endl;
    for (const auto& s : stkOutput)
    {
        cout << s.simbol;
    }*/

    deque<double> stkSolve;
    //koristim deque da bih moga da iteriram kroz njega
    for (const auto& instanca : stkOutput)
    {
        switch (instanca.tip)
        {
            case sSimbol::TipSimbola::LiteralNumeric:// ako je tip instance broj onda je samo gurni na konacni stek
            {
                stkSolve.push_front(stod(instanca.simbol));
            }
            break;
            case sSimbol::TipSimbola::Operator: //ako je instanca operator
            {
                vector<double> mem(instanca.op.brojArgumenata);// pravimo vektor sa onoliko mesta koliko operatoru treba argumenata, u nasem slucaju uvek dva
                for (int i = 0; i < instanca.op.brojArgumenata; i++)
                {
                    if (stkSolve.empty())
                    {
                        cout << "Greska!!!, shunting yard, mada ovo se ne moze desi u mom slucaju" << endl;
                    }
                    else
                    {
                        mem[i] = stkSolve[0];// stavljamo u vektor argumente redom sa steka, jer na tom steku vec ima brojeve 
                        stkSolve.pop_front();// popujemo sa steka
                    }

                }
                if (instanca.op.brojArgumenata == 2)
                {
                    if (instanca.simbol[0] == '/')
                    {
                        if (mem[0] == 0)
                        {
                            throw "Deljenej nulom nije moguce!";
                        }
                        else
                        {
                            konacanRezultatRacunanja = mem[1] / (double)mem[0];
                        }
                    }
                    if (instanca.simbol[0] == '*')
                        konacanRezultatRacunanja = mem[1] * (double)mem[0];
                    if (instanca.simbol[0] == '+')
                        konacanRezultatRacunanja = mem[1] + (double)mem[0];
                    if (instanca.simbol[0] == '-')
                        konacanRezultatRacunanja = mem[1] - (double)mem[0];
                }
                stkSolve.push_front(konacanRezultatRacunanja);
            }
            break;
        }
    }
    if (!stkSolve.empty()) {
        return stkSolve.front();// da mi mogo da se vrati samo jedan broj
    }
    return 0;
}
