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

//------------------------------------------------------ Include personnel
#include "../include/LogAnalyser.h"
#include "../include/LinksList.h"


//----------------------------------------------------------------- PUBLIC

void LogAnalyser::Display(const LinksList & links){
  #ifdef MAP
    cout << "Exécution de display de <LogAnalyser>" << endl;
  #endif

    for (const pair<string, LinkMap> & target : links.GetList()) {
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

void LogAnalyser::generateDotFile(){
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogAnalyser>" << endl;
  #endif
}
