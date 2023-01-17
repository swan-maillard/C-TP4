/*************************************************************************
    OUI.SNC++ : Vos trajets n'ont jamais été aussi simples !

    Fichier principal de l'application, gère l'affichage des différents menus.
                             -------------------
    début                : 13/12/2022
    copyright            : (C) 2022 par MALARD Sarah & MAILLARD Swan
    e-mail               : sarah.malard@insa-lyon.fr & swan.maillard@insa-lyon.fr
*************************************************************************/


//---------------------- Fichier main.cpp ------------------------


//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include<regex>
//-------------------------------------------------------- Include personnel
#include "../include/Catalogue.h"



void displayMenu(Catalogue * catalogue);

// Fonction principale
int main(int argc, char * argv[]) {

  for (int i = 0; i < argc; i++) {
    cout << string(argv[i]) << endl;
  }

  smatch match;
  string line = "192.168.0.0 - - [08/Sep/2012:11:16:02 +0200] \"GET /temps/4IF16.html HTTP/1.1\" 200 12106 \"http://intranet-if.insa-lyon.fr/temps/4IF15.html\" \"Mozilla/5.0 (Windows NT 6.1; WOW64; rv:14.0) Gecko/20100101 Firefox/14.0.1\"";
  regex_match(line, match, regex(".*\\[.*:(.*):.*:.*\\] \".* (.*) .*\" (.*) .* \"(.*)\" \".*\"$"));

  for (int i = 1; i<=(int)match.size(); i++)
    cout << match[i] << endl;


  //Catalogue catalogue;
  //displayMenu(&catalogue);

  return EXIT_SUCCESS;
}

// Affiche le menu principal
void displayMenu(Catalogue * catalogue) {

  int choice;

  do {
    cout << "Grand Catalogue :" << endl;
    cout << " 1 - Afficher les trajets" << endl;
    cout << " 2 - Rechercher un trajet" << endl;
    cout << " 3 - Ajouter un trajet" << endl;
    cout << " 4 - Charger un fichier" <<endl;
    cout << " 5 - Sauvegarder dans un fichier" <<endl;
    cout << " 6 - Quitter" << endl;
    cin >> choice;

    cout << endl;

    if (!cin) {
      choice = -1;
      cin.clear();
      cin.ignore();
    }

    switch (choice) {
      case 1: // Affichage
        break;
      case 2: // Recherche simple
        break;
      case 3: // Ajout
        break;
      case 4: // Chargement du catalogue depuis un fichier
        break;
      case 5: // Sauvegarde du catalogue dans un fichier
        break;
      case 6: // Fin
        break;
      default: // Erreur de saisie
        break;
    }

    cout << endl;

  } while (choice != 6);

}