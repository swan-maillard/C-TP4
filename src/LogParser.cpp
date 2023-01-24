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

  if (fileStream.peek() == EOF)
    return false;

  // On enlève les retour chariots s'il y en a
  //requestLine.erase(remove(requestLine.begin(), requestLine.end(), '\r'), requestLine.end());

  // smatch match;
  // regex requestRegex("^(.*) (.*) (.*) \\[(.*)\\/(.*)\\/(.*):(.*):(.*):(.*) (.*)\\] \"(.*) (.*) (.*)\" (.*) (.*) \"(.*)\" \"(.*)\"$");
  // regex_match(requestLine, match, requestRegex);

  // // Si on n'a pas matché suffisamment d'éléments, la ligne n'est pas valide donc on passe à la suivante
  // if (match.size() != 18) 
  //   return GetNextRequest(requestPointer);

  RequestParameters params;
  string tmp;
  getline(fileStream, tmp, ' ');
  params.adressIP = tmp;

  getline(fileStream, tmp, ' ');
  params.userLogname = tmp;

  getline(fileStream, tmp, ' ');
  params.authenticatedUser = tmp;

  fileStream.ignore();
  getline(fileStream, tmp, '/');
  params.date.day = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, '/');
  params.date.month = tmp;

  getline(fileStream, tmp, ':');
  params.date.year = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, ':');
  params.date.hour = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, ':');
  params.date.minute = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, ' ');
  params.date.second = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, ']');
  params.date.timezone = tmp;

  fileStream.ignore(2);
  getline(fileStream, tmp, ' ');
  params.type = tmp;

  getline(fileStream, tmp, ' ');
  params.target = tmp;

  getline(fileStream, tmp, '"');
  params.protocol = tmp;

  fileStream.ignore();
  getline(fileStream, tmp, ' ');
  params.statusCode = (isInt(tmp) ? stoi(tmp) : -1);

  getline(fileStream, tmp, ' ');
  params.size = (isInt(tmp) ? stoi(tmp) : -1);

  // if (tmp.substr(0, baseURL.length()) == baseURL)
  // {
  //     tmp = tmp.substr(baseURL.length());
  // }

  fileStream.ignore();
  getline(fileStream, tmp, '"');
  params.referer = tmp;

  fileStream.ignore(2);
  getline(fileStream, tmp, '"');
  params.userAgent = tmp;

  getline(fileStream, tmp, '\n');
  cout << "Restant : " << tmp.length() << endl;

  // On renvoie true avec la requête
  *requestPointer = new Request(params);

  return true;
}