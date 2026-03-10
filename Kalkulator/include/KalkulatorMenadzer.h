#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Parser.h"
#include "Validator.h"
#include "Racunanje.h"
#include "Istorija.h"

class KalkulatorMenadzer
{
private:
	Istorija& istorija;
	std::vector<std::string>& vektorOperacija;
	std::vector<std::string>& tokenizovaniUnetiString;
public:

	KalkulatorMenadzer(Istorija& istorija, std::vector<std::string>& vektorOperacija, std::vector<std::string>& tokenizovaniUnetiString);// menadzer radi direkto sa originalnim podacima bez kopije

	bool UradiNaredbu(const std::string& imefajla);
};

