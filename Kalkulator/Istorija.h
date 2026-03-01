#pragma once
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <fstream>

class Istorija
{
private:
    std::deque<std::string> istorijaElemenata;
    std::deque<std::string> redoStack;

public:
    bool Undo();
    bool Redo();

    // Ove dve metode ne menjaju stanje klasa pa su const
    bool IstorijaNaredbi() const;
    bool UpisiUFajl(const std::string& imeFajla) const;

    // Prosledjujemo vektor po referenci da izbegnemo kopiranje
    void SacuvajIzrazUIstoriji(const std::vector<std::string>& tokenizovaniString, double rezultat);
};