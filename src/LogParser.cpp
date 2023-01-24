/*************************************************************************
    LogParser  -  Extrait les informations d'une requête de log
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la clarequestStreame <LogParser> (fichier LogParser.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

//------------------------------------------------------ Include personnel
#include "../include/LogParser.h"
#include "../include/Request.h"
#include "../include/utils.h"


//----------------------------------------------------------------- PUBLIC

LogParser::LogParser(const string & logFile) {
  #ifdef MAP
      cout << "Construction de <LogParser>" << endl;
  #endif

  fileStream.open("resources/" + logFile, fstream::in);

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

  if (!getline(fileStream, requestLine))
    return false;

  // On enlève les retour chariots s'il y en a
  requestLine.erase(remove(requestLine.begin(), requestLine.end(), '\r'), requestLine.end());

  stringstream requestStream;
  requestStream << requestLine;

  // smatch match;
  // regex requestRegex("^(.*) (.*) (.*) \\[(.*)\\/(.*)\\/(.*):(.*):(.*):(.*) (.*)\\] \"(.*) (.*) (.*)\" (.*) (.*) \"(.*)\" \"(.*)\"$");
  // regex_match(requestLine, match, requestRegex);

  RequestParameters params;
  string tmp;
  bool invalidRequest = false;

  getline(requestStream, tmp, ' ');
  params.adressIP = tmp;

  getline(requestStream, tmp, ' ');
  params.userLogname = tmp;

  getline(requestStream, tmp, ' ');
  params.authenticatedUser = tmp;

  if (requestStream.peek() == '[') {
    requestStream.ignore();
    getline(requestStream, tmp, '/');
    params.date.day = (isInt(tmp) ? stoi(tmp) : -1);
  }
  else {
    invalidRequest = true;
  }


  getline(requestStream, tmp, '/');
  params.date.month = tmp;

  getline(requestStream, tmp, ':');
  params.date.year = (isInt(tmp) ? stoi(tmp) : -1);

  getline(requestStream, tmp, ':');
  params.date.hour = (isInt(tmp) ? stoi(tmp) : -1);

  getline(requestStream, tmp, ':');
  params.date.minute = (isInt(tmp) ? stoi(tmp) : -1);

  getline(requestStream, tmp, ' ');
  params.date.second = (isInt(tmp) ? stoi(tmp) : -1);

  getline(requestStream, tmp, ']');
  params.date.timezone = tmp;

  if (requestStream.peek() == ' ') {
    requestStream.ignore();
    if (requestStream.peek() == '"') {
      requestStream.ignore();
      getline(requestStream, tmp, ' ');
      params.type = tmp;
    }
    else {
      invalidRequest = true;
    }
  } 
  else {
    invalidRequest = true;
  }

  getline(requestStream, tmp, ' ');
  params.target = tmp;

  getline(requestStream, tmp, '"');
  params.protocol = tmp;

  if (requestStream.peek() == ' ') {
    requestStream.ignore();
    getline(requestStream, tmp, ' ');
    params.statusCode = (isInt(tmp) ? stoi(tmp) : -1);
  }
  else {
    invalidRequest = true;
  }

  getline(requestStream, tmp, ' ');
  params.size = (isInt(tmp) ? stoi(tmp) : -1);

  if (requestStream.peek() == '"') {
    requestStream.ignore();
    getline(requestStream, tmp, '"');
    params.referer = tmp;
  }
  else {
    invalidRequest = true;
  }
  
  if (requestStream.peek() == ' ') {
    requestStream.ignore();
    if (requestStream.peek() == '"') {
      requestStream.ignore();
      getline(requestStream, tmp, '"');
      params.userAgent = tmp;
    }
    else {
      invalidRequest = true;
    }
  }
  else {
    invalidRequest = true;
  }

  getline(requestStream, tmp, '\n');
  string endLine = "";
  for (int i = 0; i < (int)tmp.length(); i++) {
    if (isprint(tmp[i]) && !isblank(tmp[i]))
      endLine += tmp[i];
  }
  if (endLine.length() > 0)
    invalidRequest = true;
  
  // Si la requête est invalide, on passe à la suivante
  if (invalidRequest)
    GetNextRequest(requestPointer);


  // On renvoie true avec la requête
  *requestPointer = new Request(params);
  //cout << **requestPointer << endl;

  return true;
}