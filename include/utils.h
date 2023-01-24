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
  if (str[0] != '+' && str[0] != '-') {
    if (!isdigit(str[0]))
      return false;
  }
  else if (str.length() == 1) {
    return false;
  }

  for (int i = 1; i < (int)str.length(); i++)
    if (!isdigit((str[i])))
      return false;

  return true;
}


#endif // UTILS_H
