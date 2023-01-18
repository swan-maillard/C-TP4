/*************************************************************************
    utils  -  Fonction utiles en vrac
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

#if ! defined (UTILS_H)
#define UTILS_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <regex>
#include <string>


static bool isInt(string str) {
  return regex_match(str, std::regex("^[\\-+]?[0-9]+$"));
}


#endif // UTILS_H
