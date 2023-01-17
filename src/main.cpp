/*************************************************************************
    OUI.SNC++ : Vos trajets n'ont jamais été aussi simples !

    Fichier principal de l'application, gère l'affichage des différents menus.
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------------------- Fichier main.cpp ------------------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include<regex>
//-------------------------------------------------------- Include personnel
#include "../include/LogScanner.h"



// Fonction principale
int main(int argc, char * argv[]) {
  if (argc == 1) {
    cout << "Vous devez préciser le nom du fichier de log." << endl;
    return EXIT_FAILURE;
  }

  string logFile = argv[argc - 1];
  string dotFile = "";
  bool ignoreAssets = false;
  string timespan = "";

  // On parcourt la liste d'arguments
  for (int i = 1; i < argc-1; i++) {
    string arg = string(argv[i]);
    if (arg == "-g" && i < argc-2)
      dotFile = argv[++i];
    else if (arg == "-e")
      ignoreAssets = true;
    else if (arg == "-t" && i < argc-2)
      timespan = argv[++i];
  }

  LogScanner scanner;
  scanner.parse();
  scanner.displayTopPages();

  return EXIT_SUCCESS;
}
