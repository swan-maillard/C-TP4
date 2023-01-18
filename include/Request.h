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

//-------------------------------------------------------- Include personnel

struct DateTime {
  int day;
  string month;
  int year;
  int hour;
  int minute;
  int second;
  string timezone;
};

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

    // Constructeur
    Request(const RequestParameters & params);

    // Destructeur
    ~Request();

    // Getters
    string GetAdressIP() { return adressIP; }
    string GetUserLogname() { return userLogname; }
    string GetAuthenticatedUser() { return authenticatedUser; }
    DateTime GetDate() { return date; }
    string GetType() { return type; }
    string GetTarget() { return target; }
    string GetProtocol() { return protocol; }
    int GetStatusCode() { return statusCode; }
    int GetSize() { return size; }
    string GetReferer() { return referer; }
    string GetUserAgent() { return userAgent; }

//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés
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

#endif // REQUEST_H
