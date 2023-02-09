/*************************************************************************
    utils  -  Fonctions utiles
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
#include <string>

// Vérifie si une chaine de caractère correspond à un entier
// str : chaine de caractère à vérifier
// return bool : true si c'est un entier
static bool isInt(string str) {

  // Si la chaine ne commence ni par un entier, ni par + ni par -, ce n'est pas un entier
  // Si la chaine est uniquement constituée d'un + ou d'un -, ce n'est pas un entier
  if (str[0] != '+' && str[0] != '-') {
    if (!isdigit(str[0]))
      return false;
  }
  else if (str.length() == 1) {
    return false;
  }

  // Pour chaque autre caractère de la chaine, on vérifie que c'est un chiffre
  for (int i = 1; i < (int)str.length(); i++)
    if (!isdigit((str[i])))
      return false;

  return true;
}


#endif // UTILS_H
