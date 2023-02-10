# Manuel d'utilisation

## 1. Motivation
---
Cette application permet d'extraire les requêtes d'un fichier de log, d'afficher les 10 pages les plus consultées et de générer un graphe des liens entre les différentes pages.

## 2. Spécification du fichier de log
---
Chaque ligne du fichier de log doit suivre ce format :

`ADRESS_IP USER_LOGNAME AUTHENTICATED_USER [J/M/A:H:M:S TIMEZONE] "GET URL_TARGET HTTP_PROTOCOL" STATUS_CODE RESPONSE_SIZE "URL_REFERER" "USER_AGENT"`

**Exemple :**

`192.168.0.0 - - [10/fev/2023:10:14:31 +0200] "GET /page1.html HTTP/1.1" 200 666 "www.google.fr" "Mozilla/5.0 (Windows NT 6.3; Trident/7.0; rv:11.0) like Gecko"`

Si ce format exact n'est pas respecté, la requête ne sera pas prise en compte.

## 3. Fichier de configuration
---
Le fichier *config* situé à la racine permet de préciser une adresse locale à ignorer dans les URL des requêtes. Il faut spécifier **`BASE_URL=AdresseLocale`**.

**Exemple :**
##### **`config`**
```
BASE_URL=http://intranet-if.insa-lyon.fr/
```

## 4. Compilation
---
**Commandes à exécuter avec MakeFile :**

**$ `make`** pour compiler et faire l'édition des liens.

**$ `make dev`** pour compiler en mode développement et faire l'édition des liens.

**$ `make fclean`** pour supprimer les fichiers objets et l'éxecutable.

**$ `make help`** pour obtenir plus d'informations sur les commandes disponibles.

## 4. Exécution
---
**Commandes à exécuter pour lancer l'application :**

**$ `./analog [options] nomfichier.log`**
> Par défaut, c’est-à-dire quand il n’y a aucune option, il extraira les requêtes du fichier **`monfichier.log`** et  affichera sur la console la liste des 10 documents les plus consultés par ordre décroissant de popularité. Aucun fichier
`.dot` n’est généré dans ce cas.

> Si le fichier **`monfichier.log`** n'existe pas, une erreur sera levée.

**Les différentes [options] sont les suivantes :**

**[`-g nomfichier.dot`]**
> Cette option permet de générer le fichier **`nomfichier.dot`** au format *GraphViz*. Il permet d'obtenir un graph des liens entre les différentes pages.

**[`-e`]**
> Cette option permet d’exclure tous les documents qui ont une extension de type image, css ou
javascript.

> Les extensions prises en charge (insensible à la casse) sont : **jpg, jpeg, png, gif, svg, webp, bmp, ico, js et css.**

**[`-t heure`]**
> Cette option permet de ne prendre en compte que les hits qui sont dans le créneau horaire
correspondant à l’intervalle **[ heure ; heure+1 [**.

> L'heure doit être un nombre entier compris dans l'intervalle **[ 0 ; 24 [**. Autrement, une erreur sera levée.

## 5. Tests
---
Les tests doivent être régulièrement exécutés afin de vérifier que les nouvelles fonctionnalités n'ont pas introduit d'erreur dans les anciennes.

**Exécution des tests :**
- Se placer dans le répertoire **`tests/`**
- Exécuter **$ `./mktest.sh`**