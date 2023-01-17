/*************************************************************************
    Catalogue  -  Contient des trajets et permet d'effectuer des actions (affichage, recherche, ajout)
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined (LOGSCANNER_H)
#define LOGSCANNER_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

//-------------------------------------------------------- Include personnel

class LogScanner {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Constructeur
    LogScanner();

    // Destructeur
    virtual ~LogScanner ();

    void parse();

    void displayTopPages();

    void generateDotFile() const;




//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
  typedef map<string, int> Link;
  typedef map <string, Link> LinksList;

  string logFile;
  string dotFile ="";
  bool ignoreAssets = false ;
  string timespan="";
  LinksList linksList;


};

#endif // LOGSCANNER8H
