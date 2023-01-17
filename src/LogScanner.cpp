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
#include <map>
#include <regex>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../include/LogScanner.h"


//----------------------------------------------------------------- PUBLIC

LogScanner::LogScanner () {
  #ifdef MAP
      cout << "Construction de <LogScanner>" << endl;
  #endif
}

LogScanner::~LogScanner () {
  #ifdef MAP
      cout << "Destruction de <LogScanner>" << endl;
  #endif
}

void LogScanner::parse(){
  #ifdef MAP
    cout << "Exécution de parse de <LogScanner>" << endl;
  #endif
  ifstream file;
  file.open("test.log");
  if(file){
    string line;
    while (getline(file, line)) {
      smatch match;
      regex_match(line, match, regex(".*\\[.*:(.*):.*:.*\\] \".* (.*) .*\" (.*) .* \"(.*)\" \".*\"$"));

      LinksList::iterator linksListIterator = linksList.find(match[2]);

      Link link;
      if(linksListIterator != linksList.end()){
        link = linksListIterator->second;
        Link::iterator linkIterator = link.find(match[4]);
        if (linkIterator != link.end()) {
          linkIterator->second++;
        }
        else {
          link.insert(make_pair(match[4],1));
        }
        linksListIterator->second = link;
      }
      else{
        link.insert(make_pair(match[4],1));
        linksList.insert(make_pair(match[2],link));
      }

    }
  }else{
    cout<<"Erreur lors de l'ouverture du fichier";

  }

}

void LogScanner::displayTopPages(){
  #ifdef MAP
    cout << "Exécution de displayTopPages de <LogScanner>" << endl;
    #endif
    cout << linksList.size() << endl;
    for (LinksList::iterator linksListIterator = linksList.begin(); linksListIterator != linksList.end(); ++linksListIterator) {
      cout << linksListIterator->first << endl;
      Link link = linksListIterator->second;

      int nb = 0;
      for (Link::iterator linkIterator = link.begin(); linkIterator != link.end(); ++linkIterator) {
        nb += linkIterator->second;
      }
      cout << nb << endl << endl;
    }
}

void LogScanner::generateDotFile() const{
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogScanner>" << endl;
    #endif
}
