/*************************************************************************
    LogParser  -  Extrait les informations d'une requête de log
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <LogParser> (fichier LogParser.h) ----------------
#if ! defined (LOG_PARSER_H)
#define LOG_PARSER_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <fstream>
#include <string>

//-------------------------------------------------------- Include personnel
#include "Request.h"


class LogParser {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Constructeur
    LogParser(const string & logFile);

    // Destructeur
    ~LogParser();

    bool GetNextRequest(Request ** request);

//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés

  ifstream fileStream;

};

#endif // LOG_PARSER_H
