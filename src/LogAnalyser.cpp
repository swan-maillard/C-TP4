/*************************************************************************
    LogAnalyser  -  Analyse un fichier de log
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <LogAnalyser> (fichier LogAnalyser.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream> 
#include <string>
#include <unordered_map>
#include <regex>

//------------------------------------------------------ Include personnel
#include "../include/LogAnalyser.h"
#include "../include/LogParser.h"


//----------------------------------------------------------------- PUBLIC

LogAnalyser::LogAnalyser() {
  #ifdef MAP
      cout << "Construction de <LogAnalyser>" << endl;
  #endif
}

LogAnalyser::~LogAnalyser() {
  #ifdef MAP
      cout << "Destruction de <LogAnalyser>" << endl;
  #endif
}

void LogAnalyser::Parse(const string & file, bool flagIgnoreAssets, bool flagTimespan, int timespan) {
  // On instancie l'éxtracteur de log sur le fichier
  LogParser parser(file);

  // On extrait les requêtes et on enregistre les liens qui vérifient les différents flags
  Request * request = NULL;
  while (parser.GetNextRequest(&request)) {

    bool checkStatusCodeSuccess = (request->GetStatusCode() >= 200 && request->GetStatusCode() < 300);
    bool checkFlagIgnoreAssets = (!flagIgnoreAssets || !regex_match(request->GetTarget(), regex(".*\\.(?:jpe?g|JPE?G|png|PNG|gif|GIF|svg|SVG|webp|WEBP|bmp|BMP|ico|ICO|js|JS|css|CSS)\\/?$")));
    bool checkFlagTimespan = (!flagTimespan || timespan == request->GetDate().hour);

    if (checkStatusCodeSuccess && checkFlagIgnoreAssets && checkFlagTimespan) {
      Link link;

      // On regarde si la cible a déjà été stockée dans la liste
      LinksList::iterator searchTarget = links.find(request->GetTarget());
      if (searchTarget != links.end()) {

        // Si c'est le cas, on récupère les liens correspondant
        link = searchTarget->second;

        // On regarde s'il n'y a pas déjà un lien avec le referer
        Link::iterator searchLink = link.find(request->GetReferer());

        // S'il y a déjà un lien, on incrémente le nombre de liens, sinonon ajoute le nouveau lien
        if (searchLink != link.end())
          searchLink->second++;
        else 
          link.insert(make_pair(request->GetReferer(), 1));

        // On update la liste des liens pour la cible
        searchTarget->second = link;
      }
      else {
        // Si la cible n'était pas encore stockée, on l'insère
        link.insert(make_pair(request->GetReferer(), 1));
        links.insert(make_pair(request->GetTarget(), link));
      }
    }

    delete request;
  }
}

void LogAnalyser::Display(){
  #ifdef MAP
    cout << "Exécution de display de <LogAnalyser>" << endl;
  #endif

    for (const pair<string, Link> & target : links) {
      cout << target.first;

      int nbLinks = 0;
      for (const pair<string, int> & link : target.second)
        nbLinks += link.second;
      
      cout << " (" << nbLinks << " hits)" << endl;
    }
}

void LogAnalyser::displayTopPages() {
  #ifdef MAP
    cout << "Exécution de displayToPages de <LogAnalyser>" << endl;
  #endif
}

void LogAnalyser::generateDotFile() const{
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogAnalyser>" << endl;
  #endif
}
