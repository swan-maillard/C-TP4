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
#include <iostream>
#include <fstream>

//-------------------------------------------------------- Include personnel
#include "../include/LinksList.h"

typedef unordered_map<string, int> NodeRef; //le string correspond au nom de la page, int : numéro du noeud
typedef pair<string, int> NodePair;

class LogAnalyser {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    static void Display(const LinksList & links);

    static void DisplayTopPages(const LinksList & links);

    static void generateDotFile(const string &file, const LinksList &links);


//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
};

#endif // LOG_ANALYSER_H
