#pragma once
#include<unordered_map>
#include<deque>
#include <vector>
#include "Parser.h"

class Racunanje
{
public:
	double IzracunajVrednostIzraza(std::vector<std::string>& tokenizovaniUnetiString);
	double ShuntingYardAlgoritam(std::vector<std::string>& tokenizovaniUnetiString);
};

