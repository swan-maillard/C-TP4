/*************************************************************************
    Request  -  Contient les informations d'une requête HTTP
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <Request> (fichier Request.cpp) ------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <string>
#include <regex>

//------------------------------------------------------ Include personnel
#include "../include/Request.h"


//----------------------------------------------------------------- PUBLIC

Request::Request(const RequestParameters & params) {
  #ifdef MAP
      cout << "Construction de <Request>" << endl;
  #endif

  this->params = params;
}

Request::~Request() {
  #ifdef MAP
      cout << "Destruction de <Request>" << endl;
  #endif
}

// Affichage de la requête sur une ligne
ostream & operator << (ostream & out, const Request & request) {
  RequestParameters req = request.params;
  out << req.adressIP << " " << req.userLogname << req.authenticatedUser;
  out << " [" << req.date.day << "/" << req.date.month << "/" << req.date.year << ":" << req.date.hour << ":" << req.date.minute << ":" << req.date.second << " " << req.date.timezone << "]" << endl;
  out << " \"" << req.type << " " << req.target << " " << req.protocol << "\"";
  out << " " << req.statusCode << " " << req.size;
  out << " \"" << req.referer << "\" \"" << req.userAgent << "\"";
  out << endl;

  return out;
}