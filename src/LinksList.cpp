/*************************************************************************
    LinksList  -  Structure de donnée d'une liste de lien entre 2 pages
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <LinksList> (fichier LinksList.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>

//------------------------------------------------------ Include personnel
#include "../include/LinksList.h"


//----------------------------------------------------------------- PUBLIC

LinksList::LinksList() {
  #ifdef MAP
      cout << "Construction de <LinksList>" << endl;
  #endif
}

LinksList::~LinksList() {
  #ifdef MAP
      cout << "Destruction de <LinksList>" << endl;
  #endif
}

void LinksList::AddLink(const string & referer, const string & target) {
  LinkMap link;

  // On regarde si la cible a déjà été stockée dans la liste
  LinksListMap::iterator searchTarget = links.find(target);
  if (searchTarget != links.end()) {

    // Si c'est le cas, on récupère les liens correspondant
    link = searchTarget->second;

    // On regarde s'il n'y a pas déjà un lien avec le referer
    LinkMap::iterator searchLink = link.find(referer);

    // S'il y a déjà un lien, on incrémente le nombre de liens, sinonon ajoute le nouveau lien
    if (searchLink != link.end())
      searchLink->second++;
    else
      link.insert(LinkPair(referer, 1));

    // On update la liste des liens pour la cible
    searchTarget->second = link;
  }
  else {
    // Si la cible n'était pas encore stockée, on l'insère
    link.insert(LinkPair(referer, 1));
    links.insert(LinksListPair(target, link));
  }
}

LinksListMap LinksList::GetList() const {
  return links;
}
