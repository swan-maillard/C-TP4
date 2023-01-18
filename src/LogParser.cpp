/*************************************************************************
    LogParser  -  Extrait les informations d'une requête de log
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <LogParser> (fichier LogParser.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

//------------------------------------------------------ Include personnel
#include "../include/LogParser.h"
#include "../include/Request.h"
#include "../include/utils.h"


//----------------------------------------------------------------- PUBLIC

LogParser::LogParser(const string & logFile) {
  #ifdef MAP
      cout << "Construction de <LogParser>" << endl;
  #endif

  fileStream.open(logFile, fstream::in);

  if (!fileStream) {
    cerr << "Le fichier '" << logFile << "' est introuvable." << endl;
    exit(EXIT_FAILURE); 
  }

}

LogParser::~LogParser() {
  #ifdef MAP
      cout << "Destruction de <LogParser>" << endl;
  #endif
}

bool LogParser::GetNextRequest(Request ** requestPointer) {
  string requestLine;

  // On récupère la prochaine requête jusqu'à arriver à la fin du fichier
  if (!getline(fileStream, requestLine))
    return false;

  // On enlève les retour chariots s'il y en a
  requestLine.erase(remove(requestLine.begin(), requestLine.end(), '\r'), requestLine.end());

  smatch match;
  regex requestRegex("^(.*) (.*) (.*) \\[(.*)\\/(.*)\\/(.*):(.*):(.*):(.*) (.*)\\] \"(.*) (.*) (.*)\" (.*) (.*) \"(.*)\" \"(.*)\"$");
  regex_match(requestLine, match, requestRegex);

  // Si on n'a pas matché suffisamment d'éléments, la ligne n'est pas valide donc on passe à la suivante
  if (match.size() != 18) 
    return GetNextRequest(requestPointer);

  RequestParameters params;
  params.adressIP = match[1];
  params.userLogname = match[2];
  params.authenticatedUser = match[3];

  DateTime date;
  date.day = (isInt(match[4]) ? stoi(match[4]) : -1);
  date.month = match[5];
  date.year = (isInt(match[6]) ? stoi(match[6]) : -1);
  date.hour = (isInt(match[7]) ? stoi(match[7]) : -1);
  date.minute = (isInt(match[8]) ? stoi(match[8]) : -1);
  date.second = (isInt(match[4]) ? stoi(match[4]) : -1);
  date.timezone = match[10];

  params.date = date;
  params.type = match[11];
  params.target = match[12];
  params.protocol = match[13];
  params.statusCode = (isInt(match[14]) ? stoi(match[14]) : -1);
  params.size = (isInt(match[15]) ? stoi(match[15]) : -1);
  params.referer = match[16];
  params.userAgent = match[17];

  // On renvoie true avec la requête
  *requestPointer = new Request(params);
  return true;
}