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
#include <fstream>
#include <string>
#include <map>
#include <regex>
using namespace std;

//------------------------------------------------------ Include personnel
#include "../include/LogScanner.h"


//----------------------------------------------------------------- PUBLIC

LogScanner::LogScanner(string logFile, string dotFile, bool ignoreAssets, string timespan) {
  #ifdef MAP
      cout << "Construction de <LogScanner>" << endl;
  #endif
  this->logFile = logFile;
  this->dotFile = dotFile;
  this->ignoreAssets = ignoreAssets;
  this->timespan = timespan;
}

LogScanner::~LogScanner() {
  #ifdef MAP
      cout << "Destruction de <LogScanner>" << endl;
  #endif
}

void LogScanner::parse(){
  #ifdef MAP
    cout << "Exécution de parse de <LogScanner>" << endl;
  #endif

  ifstream file;
  file.open(logFile);
  
  // On vérifie que le fichier de log existe
  if(file){

    // Pour chaque ligne de log
    string line;
    while (getline(file, line)) {
      
      // On enlève les retour chariots s'il y en a
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());

      // On utilise une expression régulière pour décomposer les lignes de log
      smatch match;
      regex_match(line, match, regex(".*\\[.*:(.*):.*:.*\\] \".* (.*) .*\" (.*) .* \"(.*)\" \".*\"$"));

      // Si on n'a pas matché suffisamment d'éléments, la ligne n'est pas valide donc on passe à la suivante
      if (match.size() < 5) 
        continue;

      // On récupère l'heure, la cible, le code HTTP et le referer
      string timeHour = match[1];
      string target = match[2];
      string HTTPCode = match[3];
      string referer = match[4];

      // On vérifie que le code HTTP est de la forme 2XX : Succès de la requête
      if (!regex_match(HTTPCode, regex("^2[0-9]{2}$")))
        continue;

      // On ignore les images, css et js si le flag correspondant a été précisé
      if (ignoreAssets && regex_match(target, regex(".*\\.(?:jpe?g|JPE?G|png|PNG|gif|GIF|svg|SVG|webp|WEBP|bmp|BMP|ico|ICO|js|JS|css|CSS)\\/?$")))
        continue;

      // Si un flag spécifie une heure spécifique, on ne conserve que les lignes obtenues à cette heure
      if (!timespan.empty() && timespan != timeHour)
        continue;

      Link link;

      // On regarde si la cible a déjà été stockée dans la liste
      LinksList::iterator linksListIterator = linksList.find(target);
      if(linksListIterator != linksList.end()){

        // Si c'est le cas, on récupère les liens correspondant
        link = linksListIterator->second;

        // On regarde s'il n'y a pas déjà un lien avec le referer
        Link::iterator linkIterator = link.find(referer);

        // S'il y a déjà un lien, on incrémente le nombre de liens, sinonon ajoute le nouveau lien
        if (linkIterator != link.end())
          linkIterator->second++;
        else 
          link.insert(make_pair(referer, 1));

        // On update la liste des liens pour la cible
        linksListIterator->second = link;
      }
      else{
        // Si la cible n'était pas encore stockée, on l'insère
        link.insert(make_pair(referer, 1));
        linksList.insert(make_pair(target, link));
      }

    }
  } else {
    cout << "Erreur lors de l'ouverture du fichier" << endl;
  }

}

void LogScanner::display(){
  #ifdef MAP
    cout << "Exécution de display de <LogScanner>" << endl;
  #endif

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

void LogScanner::displayTopPages() {
  #ifdef MAP
    cout << "Exécution de displayToPages de <LogScanner>" << endl;
  #endif
}

void LogScanner::generateDotFile() const{
  #ifdef MAP
    cout << "Exécution de generateDotFile de <LogScanner>" << endl;
  #endif
}
