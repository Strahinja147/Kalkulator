#pragma once
#include <string>
#include <iostream>
#include <vector>

class Parser
{
public:
    Parser() {};
    

    static bool IsInteger(std::vector<std::string>::iterator s);

    std::vector<std::string> Tokenizuj(const std::string& stringZaTokenizaciju);
    std::vector<std::string> Parsiraj(const std::string& stringZaParsiranje, std::vector<int>& vektorBrojeva, std::vector<std::string>& vektorOperacija);
};

