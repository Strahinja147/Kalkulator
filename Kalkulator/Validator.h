#pragma once
#include <vector>
#include <string>
#include "Parser.h"

class Validator
{
public:
    
    static bool TekstJeValidan(const std::vector<std::string>& vektorStringova, std::vector<std::string>& tokenizovaniUnetiString);
};