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

void LogAnalyser::GenerateDotFile(const string &file, const LinksList &links){
  #ifdef MAP
    cout << "Exécution de GenerateDotFile de <LogAnalyser>" << endl;
  #endif

  // Contenu du fichier .dot
  string content = "digraph {\n";

  // Map contenant le nom et l'identifiant de chaque page
  PagesName pagesName;
  // Index de la page
  int pageIndex = 0;

  // On parcourt toutes les pages cibles et on les ajoute dans pagesName ainsi que sur le .dot
  for (const LinksListPair & linksListPair : links.GetList()) {
    string target = linksListPair.first;
    pagesName.insert(make_pair(target, pageIndex));
    content += "\tnode" + to_string(pageIndex) + " [label=\"" + target + "\"];\n";

    pageIndex++;
  }

  // Attention : il y a peut-être des pages qui sont referer mais jamais cible.
  // Il faut donc maintenant parcourir toutes les pages referer et les rajouter si elles ne font pas encore partie de pagesName.
  for (const LinksListPair & linksListPair : links.GetList()) {

    for (const LinkPair & linkPair: linksListPair.second) {
      string referer = linkPair.first;
      PagesName::iterator searchReferer = pagesName.find(referer);

      // La page referer ne fait pas partie de pagesName
      if (searchReferer == pagesName.end()) {
        pagesName.insert(make_pair(referer, pageIndex));
        content += "\tnode" + to_string(pageIndex) + " [label=\"" + referer + "\"];\n";
        pageIndex++;
      }
    }
  }

  // On reparcourt tous les liens pour les afficher dans le .dot
  for (const LinksListPair & linksListPair : links.GetList()) {
      int targetID = pagesName.find(linksListPair.first)->second;

      for(const LinkPair & linkPair: linksListPair.second) {
        int refererID = pagesName.find(linkPair.first)->second;

        content += "\tnode" + to_string(refererID) + " -> node" + to_string(targetID) + " [label=\"" + to_string(linkPair.second) + "\"];\n";
      }
  }

  // Fin du fichier .dot
  content += "}\n";

  // On écrit le contenu dans le fichier .dot
  ofstream dotFile(file, fstream::out);
  dotFile << content;
}
