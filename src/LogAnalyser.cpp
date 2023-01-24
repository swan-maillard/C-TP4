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
#include <fstream>


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

void LogAnalyser::generateDotFile(const ifstream &file, const LinksList &links){
  //file en param juste pr test
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogAnalyser>" << endl;
  #endif
  string dotcontent="digraph {\n";
  LinksListMap::iterator parcours;
  string target;
  int i=0; //indice du parcours
  int j=0; //parcours des relations
  string relations="";
  NodeRef Noderefpair;

  // pour parcourir toutes les paires de la map
  for (const LinksListPair & linksListPair : links.GetList()) {
      string noeud="";
      target = linksListPair.first;
      noeud="node"+to_string(i)+ " [label=\"" + target + "\"];\n";
      Noderefpair.insert(make_pair(target, i));
      i++;
      dotcontent+=noeud;
    }
    for (const LinksListPair & linksListPair : links.GetList()) {
            int numnoeud;
              for(const LinkPair & linkPair: linksListPair.second){
                string referer = linkPair.first;
                string base = "http://intranet-if.insa-lyon.fr";
                int basePos = referer.find(base);
                if (basePos >= 0) {
                  referer.erase(basePos, base.length());
                }

                NodeRef::iterator node = Noderefpair.find(referer);

                if(node!=Noderefpair.end()){
                  numnoeud = node->second;
                  relations+="node"+ to_string(numnoeud) + "-> node"+to_string(j);

                  int nbrelations=linkPair.second;
                  relations+=" [label=\""+to_string(nbrelations)+"\"];\n";
                }
      }
      j++;
    }

  dotcontent+=relations;
  dotcontent+="}";
  ofstream { "court.dot" };
  ofstream fichierdot;
  fichierdot.open("court.dot");
  fichierdot<<dotcontent;
  //cout<<dotcontent;

}
