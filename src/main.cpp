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
#include <regex>
//-------------------------------------------------------- Include personnel
#include "../include/utils.h"
#include "../include/LogAnalyser.h"
#include "../include/LogParser.h"
#include "../include/LinksList.h"

// Les flags pouvant être passés dans la commande
struct Flags {
  bool generateDotFile = false;
  string dotFile = "";
  bool ignoreAssets = false;
  bool timespan = false;
  int hour;
};

// Extrait les requêtes d'un fichier
// logFile : fichier de log dont il faut extraire les requêtes
// flags : paramètres à prendre en compte pour filtrer les requêtes
// return LinksList : Liste des liens entre les différentes pages
LinksList parse(const string & logFile, const Flags & flags);

// Récupère la base de l'URL locale dans le fichier config s'il y en a
const string getBaseURL();

// Fonction principale
int main(int argc, char * argv[]) {

  // S'il n'y a qu'un seul argument : erreur
  if (argc == 1) {
    cerr << "Vous devez préciser le nom du fichier de log." << endl;
    return EXIT_FAILURE;
  }

  // Nom du fichier de log
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


  // On extrait les requêtes pour obtenir la liste des liens entre les pages
  LinksList links = parse(logFile, flags);

  // On affiche les 10 pages les plus fréquentées
  LogAnalyser::DisplayTopPages(links);

  // Si un fichier .dot a été spécifié, on le génère
  if (flags.generateDotFile)
    LogAnalyser::GenerateDotFile(flags.dotFile, links);

  return EXIT_SUCCESS;
}

LinksList parse(const string & logFile, const Flags & flags) {
  LinksList links;

  // On instancie l'éxtracteur de log sur le fichier
  LogParser parser(logFile);

  
  // Expression régulière pour matcher les assets (images, script, stylesheet)
  regex assetsRegex = regex(".*\\.(?:jpe?g|JPE?G|png|PNG|gif|GIF|svg|SVG|webp|WEBP|bmp|BMP|ico|ICO|js|JS|css|CSS)\\/?$");

  // Base de l'URL locale
  const string BASE_URL = getBaseURL();

  // On extrait les requêtes et on enregistre les liens qui vérifient les différents flags
  Request * request = NULL;
  while (parser.GetNextRequest(&request)) {

    // Le code de statut doit être dans les 200
    bool checkStatusCodeSuccess = (request->GetStatusCode() >= 200 && request->GetStatusCode() < 300);
    // On ignore les assets si le flag a été spécifié
    bool checkFlagIgnoreAssets = (!flags.ignoreAssets || !regex_match(request->GetTarget(), assetsRegex));
    // On match un intervalle de temps spécifique si le flag a été spécifié
    bool checkFlagTimespan = (!flags.timespan || flags.hour == request->GetDate().hour);

    // Si toutes les conditions ont été vérifiées, on traite la requête
    if (checkStatusCodeSuccess && checkFlagIgnoreAssets && checkFlagTimespan) {
      string referer = request->GetReferer();
      string target = request->GetTarget();

      // On retire la base locale de l'URL si elle y est
      if (referer.substr(0, BASE_URL.length()) == BASE_URL)
        referer.erase(0, BASE_URL.length());

      // On retire de l'URL tout ce qu'il y a après "?" inclus
      int posURLArgs = referer.find("?");
      if (posURLArgs)
        referer = referer.substr(0, posURLArgs);

      // S'il n'y a pas de / au début de l'URL, on le rajoute
      if (referer[0] != '/' && referer[0] != '-')
        referer = '/' + referer;
      if (target[0] != '/' && target[0] != '-')
        target = '/' + target;

      // On crée le lien entre les pages referer et cible
      links.AddLink(referer, request->GetTarget());
    }

    delete request;
  }

  return links;
}

const string getBaseURL() {
  ifstream configStream("config");
  if (configStream) {
    // Si le fichier de configuration existe, on le parcourt
    string configLine;
    while (getline(configStream, configLine)) {
      // Si le champ BASE_URL est présent, on récupère sa valeur
      string fieldName = "BASE_URL=";
      if (configLine.substr(0, fieldName.length()) == fieldName) {
        string baseURL = configLine.substr(fieldName.length());
        if (baseURL[baseURL.length() - 1] == '/')
          baseURL.pop_back();

        return baseURL;
      }
    }
  }

  return "";
}