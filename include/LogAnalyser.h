/*************************************************************************
    LogAnalyser  -  Analyse un fichier de log
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <LogAnalyser> (fichier LogAnalyser.h) ----------------
#if ! defined (LOG_ANALYSER_H)
#define LOG_ANALYSER_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <unordered_map>

//-------------------------------------------------------- Include personnel
#include "../include/LinksList.h"

// Map contenant la paire <nom de la page, id de la page> 
typedef unordered_map<string, int> PagesName;
typedef pair<string, int> PagesNamePair;

class LogAnalyser {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Méthode statique affichant les 10 pages les plus consultées
    // links : Liste de liens entre les pages
    static void DisplayTopPages(const LinksList & links);

    // Méthode statique générant le fichier .dot 
    // file : Fichier qui sera généré
    // links : Liste de liens entre les pages
    static void GenerateDotFile(const string &file, const LinksList &links);


//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
};

#endif // LOG_ANALYSER_H
