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

class LogAnalyser {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Constructeur
    LogAnalyser();

    // Destructeur
    ~LogAnalyser();

    void Parse(const string & file, bool flagIgnoreAssets, bool flagTimespan, int timespan);

    void Display();

    void displayTopPages();

    void generateDotFile() const;


//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
    typedef unordered_map<string, int> Link;
    typedef unordered_map <string, Link> LinksList;

    LinksList links;
};

#endif // LOG_ANALYSER_H
