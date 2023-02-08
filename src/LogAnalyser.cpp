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

void LogAnalyser::generateDotFile(const string &file, const LinksList &links){
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
    noeud="\tnode"+to_string(i)+ " [label=\"" + target + "\"];\n";
    Noderefpair.insert(make_pair(target, i));
    i++;
    dotcontent+=noeud;
  }

//rajoute le noeud dans la liste des noeuds quand il est referer mais jamais target (donc pas encore dans la liste)
  for (const LinksListPair & linksListPair : links.GetList()) {
    string noeud="";
    LinkMap second;
    string referer="";
    int present=0;

    for (const LinkPair & linkPair: linksListPair.second) { //pour chaque referer, on vérifie s'il est déjà présent dans le noeud de ref.
      for(const NodePair & refpair : Noderefpair){
        referer=linkPair.first;
        if(referer==refpair.first){
          present=1;
          break;
        }
      }
      if(present==0){
        Noderefpair.insert(make_pair(referer, i));
        noeud="\tnode"+to_string(i)+ " [label=\"" + referer + "\"];\n";
        dotcontent+=noeud;
        i++;
      }
      present=0;
    }
  }

  for (const LinksListPair & linksListPair : links.GetList()) {
      int numnoeud;

      for(const LinkPair & linkPair: linksListPair.second){ //on parcourt la linkmap
        NodeRef::iterator node = Noderefpair.find(linkPair.first); //on trouve le noeud correspondant au referer de la paire de la linkmap
        numnoeud = node->second;
        if(node!=Noderefpair.end()) {
          relations+="\tnode"+ to_string(numnoeud) + " -> node"+to_string(j);
          int nbrelations=linkPair.second;
          relations+=" [label=\""+to_string(nbrelations)+"\"];\n";
        }
      }

    j++;
  }

  dotcontent+=relations;
  dotcontent+="}\n";

  ofstream fichierdot;
  fichierdot.open(file, fstream::out);
  fichierdot << dotcontent;
}
