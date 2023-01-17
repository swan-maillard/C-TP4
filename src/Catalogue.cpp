/*************************************************************************
    Catalogue  -  Contient des trajets et permet d'effectuer des actions (affichage, recherche, ajout)
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <ctype.h>

//------------------------------------------------------ Include personnel
#include "../include/Catalogue.h"


//----------------------------------------------------------------- PUBLIC

Catalogue::Catalogue () {
  #ifdef MAP
      cout << "Construction de <Catalogue>" << endl;
  #endif
}

Catalogue::~Catalogue () {
  #ifdef MAP
      cout << "Destruction de <Catalogue>" << endl;
  #endif
}