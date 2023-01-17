/*************************************************************************
    Catalogue  -  Contient des trajets et permet d'effectuer des actions (affichage, recherche, ajout)
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <fstream>

//-------------------------------------------------------- Include personnel

class Catalogue {

//----------------------------------------------------------------- PUBLIC
  public:
//----------------------------------------------------- Méthodes publiques

    // Constructeur
    Catalogue();

    // Destructeur
    virtual ~Catalogue ();


//----------------------------------------------------------------- PRIVE
  protected:
//----------------------------------------------------- Attributs protégés

};

#endif // CATALOGUE_H
