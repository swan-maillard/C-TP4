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
#include <map>

//------------------------------------------------------ Include personnel
#include "../include/LogAnalyser.h"
#include "../include/LinksList.h"



//----------------------------------------------------------------- PUBLIC

void LogAnalyser::Display(const LinksList & links){
  #ifdef MAP
    cout << "Exécution de display de <LogAnalyser>" << endl;
  #endif

    for (const LinksListPair & linksListPair : links.GetList()) {
      cout << linksListPair.first;

      int nbLinks = 0;
      for (const LinkPair & linkPair : linksListPair.second)
        nbLinks += linkPair.second;
      
      cout << " (" << nbLinks << " hits)" << endl;
    }
}

void LogAnalyser::DisplayTopPages(const LinksList & links) {
  #ifdef MAP
    cout << "Exécution de displayToPages de <LogAnalyser>" << endl;
  #endif

  // Structure de données des top pages consultées, triées par nombre de liens entrants décroissants
  multimap<int, string, greater<int>> topPages;

  // Pour chaque pages cibles on calcule son nombre de liens entrants
  for (const LinksListPair & linksListPair : links.GetList()) {
    string target = linksListPair.first;

    int nbLinks = 0;
    for (const LinkPair & linkPair : linksListPair.second)
      nbLinks += linkPair.second;
  
    // On ajoute la cible et le nombre de liens entrant dans topPages (ce sera automatiquement trié par nombre de liens décroissants)
    topPages.insert(make_pair(nbLinks, target));

    // S'il y a plus de 10 pages stockées, on supprime la dernière (celle ayant le plus petit nombre de liens entrants)
    if (topPages.size() > 10)
      topPages.erase(prev(topPages.end()));
  }

  // On affiche le top pages consultées
  for (const pair<int, string> & pagePair : topPages)
    cout << pagePair.second << " (" << pagePair.first << " hits)" << endl;

}

void LogAnalyser::generateDotFile(){
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogAnalyser>" << endl;
  #endif
}
