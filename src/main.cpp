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
#include <string>
#include <regex>
//-------------------------------------------------------- Include personnel
#include "../include/utils.h"
#include "../include/LogAnalyser.h"
#include "../include/LogParser.h"
#include "../include/LinksList.h"

struct Flags {
  bool generateDotFile = false;
  string dotFile = "";
  bool ignoreAssets = false;
  bool timespan = false;
  int hour;
};


LinksList parse(const string & logFile, const Flags & flags);

// Fonction principale
int main(int argc, char * argv[]) {
  if (argc == 1) {
    cerr << "Vous devez préciser le nom du fichier de log." << endl;
    return EXIT_FAILURE;
  }

  string logFile = argv[argc - 1];
  Flags flags;

  // On parcourt la liste d'arguments pour récupérer les flags
  for (int i = 1; i < argc-1; i++) {
    string arg = string(argv[i]);
    if (arg == "-g") {
      if (i > argc-1) {
        cerr << "Il faut préciser un nom de fichier après le flag -g" << endl;
        return EXIT_FAILURE;
      }

      flags.generateDotFile = true;
      flags.dotFile = argv[++i];
    }
    else if (arg == "-e") {
      flags.ignoreAssets = true;
    }
    else if (arg == "-t") {
      if (i > argc-1 || !isInt(argv[i+1])) {
        cerr << "Il faut préciser une heure après le flag -t" << endl;
        return EXIT_FAILURE;
      }
      
      int hour = stoi(argv[++i]);
      if (hour < 0 || hour > 23) {
        cerr << hour << " n'est pas une heure valide" << endl;
        return EXIT_FAILURE;
      }

      flags.timespan = true;
      flags.hour = hour;
    }
    else {
      if (argv[i][0] == '-')
        cerr << "Le flag " << argv[i] << " n'est pas reconnu" << endl;
      else
        cerr << "L'argument " << argv[i] << " n'est pas valide" << endl;

      return EXIT_FAILURE;
    }
  }


  LinksList links = parse(logFile, flags);
  LogAnalyser::DisplayTopPages(links);

  return EXIT_SUCCESS;
}

LinksList parse(const string & logFile, const Flags & flags) {
  LinksList links;

  // On instancie l'éxtracteur de log sur le fichier
  LogParser parser(logFile);

  // On extrait les requêtes et on enregistre les liens qui vérifient les différents flags
  Request * request = NULL;
  while (parser.GetNextRequest(&request)) {

    bool checkStatusCodeSuccess = (request->GetStatusCode() >= 200 && request->GetStatusCode() < 300);
    bool checkFlagIgnoreAssets = (!flags.ignoreAssets || !regex_match(request->GetTarget(), regex(".*\\.(?:jpe?g|JPE?G|png|PNG|gif|GIF|svg|SVG|webp|WEBP|bmp|BMP|ico|ICO|js|JS|css|CSS)\\/?$")));
    bool checkFlagTimespan = (!flags.timespan || flags.hour == request->GetDate().hour);

    if (checkStatusCodeSuccess && checkFlagIgnoreAssets && checkFlagTimespan) {
      links.AddLink(request->GetReferer(), request->GetTarget());
    }

    delete request;
  }

  return links;
}
