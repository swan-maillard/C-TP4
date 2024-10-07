# Extracteur de requêtes de log et analyseur de liens

## Description

Ce projet a pour but de faciliter l'analyse des fichiers de log en extrayant les requêtes et en visualisant les liens entre les différentes pages web. Il permet aux utilisateurs de mieux comprendre le comportement de leurs visiteurs et d'optimiser leur site en fonction des résultats.

## Format du fichier de log

Pour que l'application puisse fonctionner correctement, chaque ligne du fichier de log doit respecter le format suivant :

```
ADRESS_IP USER_LOGNAME AUTHENTICATED_USER [J/M/A:H:M:S TIMEZONE] "GET URL_TARGET HTTP_PROTOCOL" STATUS_CODE RESPONSE_SIZE "URL_REFERER" "USER_AGENT"
```

### Exemple :

```
192.168.0.0 - - [10/fev/2023:10:14:31 +0200] "GET /page1.html HTTP/1.1" 200 666 "www.google.fr" "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko"
```

Les lignes ne respectant pas ce format ne seront pas prises en compte par l'application.

## Fichier de configuration

Un fichier nommé *config* doit être présent à la racine du projet. Il permet de définir une adresse locale à ignorer lors de l'analyse des URL. Le format doit être :

```
BASE_URL=AdresseLocale
```

### Exemple de contenu du fichier `config` :

```
BASE_URL=http://intranet-if.insa-lyon.fr/
```

## Instructions de compilation

Pour compiler le projet, utilisez le Makefile fourni dans le répertoire. Les commandes disponibles sont les suivantes :

- **`make`** : compile le projet et effectue l'édition des liens.
- **`make dev`** : compile le projet en mode développement.
- **`make fclean`** : supprime les fichiers objets et l'exécutable.
- **`make help`** : affiche des informations sur les commandes disponibles.

## Utilisation de l'application

Pour exécuter l'application, utilisez la commande suivante :

```
./analog [options] nomfichier.log
```

### Fonctionnalités par défaut :

Sans options, l'application extrait les requêtes du fichier spécifié (ex. : `monfichier.log`) et affiche sur la console les 10 pages les plus consultées par ordre décroissant. Aucune génération de fichier `.dot` n'a lieu.

### Options disponibles :

- **`-g nomfichier.dot`** :
  - Génère un fichier au format GraphViz nommé `nomfichier.dot`, représentant un graphe des liens entre les différentes pages.

- **`-e`** :
  - Exclut les requêtes correspondant à des ressources statiques telles que les images, les fichiers CSS et JavaScript.
  - Les extensions supportées sont : **jpg, jpeg, png, gif, svg, webp, bmp, ico, js, css** (insensible à la casse).

- **`-t heure`** :
  - Filtre les requêtes pour ne garder que celles dans l'intervalle d'une heure donnée (ex. : `[ heure ; heure+1 [ `).
  - L'heure doit être un entier compris entre **0 et 24**. Sinon, une erreur sera affichée.

## Tests

Il est important d'effectuer des tests réguliers pour s'assurer que les nouvelles modifications n'affectent pas le bon fonctionnement de l'application. 

### Comment exécuter les tests :

1. Accédez au répertoire **`tests/`**.
2. Exécutez la commande suivante :

```
./mktest.sh
```

## Auteurs

- Swan Maillard (maillard.swan@gmail.com)
- Sarah Malard (sarah.malard@insa-lyon.fr)

## Licence

Ce projet est sous licence MIT. Veuillez consulter le fichier `LICENSE` pour plus d'informations.
