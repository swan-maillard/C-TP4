/*************************************************************************
    Request  -  Contient les informations d'une requête HTTP
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Request> (fichier Request.h) ----------------
#if ! defined (REQUEST_H)
#define REQUEST_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <ostream>

//-------------------------------------------------------- Include personnel

// Structure définissant une date
struct DateTime {
  int day;
  string month;
  int year;
  int hour;
  int minute;
  int second;
  string timezone;
};

// Structure définissant les paramètres d'une requête
struct RequestParameters {
  string adressIP;
  string userLogname;
  string authenticatedUser;
  DateTime date;
  string type;
  string target;
  string protocol;
  int statusCode;
  int size;
  string referer;
  string userAgent;
};

class Request {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Surcharge de l'opérateur <<
    friend ostream & operator << (ostream & out, const Request & request);

    // Constructeur
    // params : paramètres de la requête
    Request(const RequestParameters & params);

    // Destructeur
    ~Request();

    // Getters
    // On les a déclarer dans le fichier d'en-tête car elles ne sont composées que d'une ligne
    string GetAdressIP() { return params.adressIP; }
    string GetUserLogname() { return params.userLogname; }
    string GetAuthenticatedUser() { return params.authenticatedUser; }
    DateTime GetDate() { return params.date; }
    string GetType() { return params.type; }
    string GetTarget() { return params.target; }
    string GetProtocol() { return params.protocol; }
    int GetStatusCode() { return params.statusCode; }
    int GetSize() { return params.size; }
    string GetReferer() { return params.referer; }
    string GetUserAgent() { return params.userAgent; }

//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
    RequestParameters params;
};

#endif // REQUEST_H
