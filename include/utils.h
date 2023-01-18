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
#include <string>


static bool isInt(string str) {
  int stringLength = str.size();

  for (int i = 0; i < stringLength; ++i)
    if (!isdigit(str[i]))
      return false;

  return true;
}


#endif // UTILS_H
