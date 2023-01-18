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

  this->adressIP = params.adressIP;
  this->userLogname = params.userLogname;
  this->authenticatedUser = params.authenticatedUser;
  this->date = params.date;
  this->type = params.type;
  this->target = params.target;
  this->protocol = params.protocol;
  this->statusCode = params.statusCode;
  this->size = params.size;
  this->referer = params.referer;
  this->userAgent = params.userAgent;
}

Request::~Request() {
  #ifdef MAP
      cout << "Destruction de <Request>" << endl;
  #endif
}