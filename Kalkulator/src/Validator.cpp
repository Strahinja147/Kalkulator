#include "Validator.h"

using namespace std;

bool Validator::TekstJeValidan(const vector<string>& vektorStringova, vector<string>& tokenizovaniUnetiString)
{
    if (tokenizovaniUnetiString.size() == 1) {
        const string& cmd = tokenizovaniUnetiString[0];
        if (cmd == "i" || cmd == "u" || cmd == "r" || cmd == "s") {
            return true;
        }
    }

    if (tokenizovaniUnetiString.empty() || tokenizovaniUnetiString.size() < 3) {
        return false;
    }
    
    const string& prvi = tokenizovaniUnetiString.front();
    const string& zadnji = tokenizovaniUnetiString.back();

    if (prvi == "+" || prvi == "*" || prvi == "/" || prvi == ")") {
        return false;
    }

    if (zadnji == "+" || zadnji == "-" || zadnji == "*" || zadnji == "/" || zadnji == "(") {
        return false;
    }

    for (const string& op : vektorStringova) {
        if (op != "+" && op != "-" && op != "*" && op != "/" && op != "(" && op != ")") {
            return false;
        }
    }

    for (size_t i = 0; i < tokenizovaniUnetiString.size() - 1; ++i)
    {
        auto itTrenutni = tokenizovaniUnetiString.begin() + i;
        auto itSledeci = tokenizovaniUnetiString.begin() + i + 1;

        bool trenutniJeBroj = Parser::IsInteger(itTrenutni);
        bool sledeciJeBroj = Parser::IsInteger(itSledeci);

        const string& trenutniToken = *itTrenutni;
        const string& sledeciToken = *itSledeci;

        if (trenutniJeBroj && sledeciJeBroj) {
            return false;
        }

        if (!trenutniJeBroj && !sledeciJeBroj)
        {
            bool dozvoljeno = (sledeciToken == "(") || (trenutniToken == ")");

            if (!dozvoljeno) {
                return false;
            }
        }
    }

    return true;
}