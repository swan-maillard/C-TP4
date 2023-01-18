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
#include <fstream>
#include <string>
#include <regex>
//-------------------------------------------------------- Include personnel
#include "../include/utils.h"
#include "../include/LogAnalyser.h"


// Fonction principale
int main(int argc, char * argv[]) {
  if (argc == 1) {
    cerr << "Vous devez préciser le nom du fichier de log." << endl;
    return EXIT_FAILURE;
  }

  string logFile = argv[argc - 1];
  bool flagDotFile = false;
  string dotFile = "";
  bool flagIgnoreAssets = false;
  bool flagTimespan = false;
  int timespan;

  // On parcourt la liste d'arguments pour récupérer les flags
  for (int i = 1; i < argc-1; i++) {
    string arg = string(argv[i]);
    if (arg == "-g") {
      if (i > argc-1) {
        cerr << "Il faut préciser un nom de fichier après -g" << endl;
        return EXIT_FAILURE;
      }

      flagDotFile = true;
      dotFile = argv[++i];
    }
    else if (arg == "-e") {
      flagIgnoreAssets = true;
    }
    else if (arg == "-t") {
      if (i > argc-1 || !isInt(argv[i+1])) {
        cerr << "Il faut préciser une heure après -t" << endl;
        return EXIT_FAILURE;
      }

      flagTimespan = true;
      timespan = stoi(argv[++i]);
    }
    else {
      cerr << argv[i] << " n'est pas un argument valide" << endl;
      return EXIT_FAILURE;
    }
  }

  LogAnalyser analyser;
  analyser.Parse(logFile, flagIgnoreAssets, flagTimespan, timespan);
  analyser.Display();

  return EXIT_SUCCESS;
}
