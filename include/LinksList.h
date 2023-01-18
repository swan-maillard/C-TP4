/*************************************************************************
    LinksList  -  Structure de donnée d'une liste de lien entre 2 pages
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <LinksList> (fichier LinksList.h) ----------------
#if ! defined (LINKS_LIST_H)
#define LINKS_LIST_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <unordered_map>
#include <string>

//-------------------------------------------------------- Include personnel

typedef unordered_map<string, int> LinkMap;
typedef unordered_map<string, LinkMap> LinksListMap;  

class LinksList {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Constructeur
    LinksList();

    // Destructeur
    ~LinksList();

    void AddLink(const string & referer, const string & target);

    LinksListMap GetList() const;

//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
    LinksListMap links;

};

#endif // LINKS_LIST_H
