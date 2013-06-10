<!--  Pour emacs : -*- mode:  markdown -*-  -->

## Module cgi

### Description

Ce module permet d'implementer la **Common Gateway Interface**
(littéralement « Interface de passerelle commune »), généralement
abrégée [**CGI**](http://fr.wikipedia.org/wiki/Common_Gateway_Interface).

### Fonctionnement

Lorsque l'URI demandée au serveur correspond a un fichier exécutable,
le module lance l'exécution du programme et redirige les caractères
affichés sur la sortie standard vers le client. Si l'URI ne correspond
pas à un programme exécutable, le module en délègue le traitement au
module inférieur.

Ce module permet de traiter les requêtes
[HTTP](http://fr.wikipedia.org/wiki/M%C3%A9thode_de_requ%C3%AAte#M.C3.A9thodes)
de type `GET` et de type `POST`. Lorsque le programme désigné par
l'URI est exécuté, le répertoire par défaut est positionné sur le
répertoire du serveur qui contient le programme. Par ailleurs, un
certain nombre d'informations sont rangées dans des variables
d'environnement. Ces différents points sont détaillé ci-dessous.

#### Environnement

Avant de lancer l'exécution d'un programme, le module `cgi` construit
l'environnement nécessaire à l'exécution du programme.

*Extrait [Wikipédia](http://fr.wikipedia.org/wiki/Variables_d%27environnement_CGI):*

> Les **variables d'environnement CGI** sont des variables transmises à un
> programme CGI, par le serveur Web l'invoquant, lors de son exécution.
> Elles fournissent des informations sur la requête effectuée par le
> client, sur le serveur et également sur le client lui-même. Par
> exemple, lorsqu'on effectue une recherche sur un site qui fonctionne
> avec des CGI, le script récupérera les termes de la recherche avec la
> variable d'environnement « QUERY_STRING ».

Pour fonctionner, seules quelques variables sont vraiment
nécessaires. Le module `cgi` n'implémente donc qu'un sous-ensemble des
variables CGI. Les variables mises à jour par le module sont:

* `DOCUMENT_ROOT`: la racine des documents du serveur.
* `GATEWAY_INTERFACE`: toujours égale à `CGI/1.1`.
* `PATH`: le path du programme (limité à la valeur
  `/bin:/usr/bin:/usr/local/bin` pour des raisons de sécurité)
* `QUERY_STRING`: Contient tout ce qui suit le « ? » dans l'URL
  envoyée par le client. Toutes les variables provenant d'un
  formulaire envoyé avec la méthode « GET » seront contenues dans le
  QUERY_STRING sous la forme «`var1=val1&var2=val2&...`».
* `REMOTE_ADDR`:L'adresse IP du client.
* `REQUEST_METHOD`: `GET` ou `POST` suivant la méthode HTTP d'accès.
* `REQUEST_URI`: l'URI utilisée pour déclencher l'exécution du programme.
* `SERVER_PROTOCOL`: toujours `HTTP/1.0` ici.
* `SERVER_SOFTWARE`: le nom et la version du serveur web.

Par ailleurs, lorsque le programme est lancé par la méthode `POST`
deux variables supplémentaires doivent être initialisées pour que les
programmes exécutés retrouvent leurs données:

* `CONTENT_TYPE`: qui contient la façon dont les données du programme
  sont encodées.
* `CONTENT_LENGTH`: qui contient la longueur des données du programme.

Les valeurs de `CONTENT_TYPE` et `CONTENT_LENGTH` n'ont pas à être
calculés; elles sont en fait en fait données par le client dans les
en-têtes qui suivent la requête (champs `Content-Length` et
`Content-Type`).


*Exemples de programmes CGI*:

* [Affichage de l'environnement](http://localhost:1234/demos/env.py)
* [Fonction sinus](http://localhost:1234/demos/sinus.py)

#### Méthode GET et Méthode POST

Lorsque l'on remplit un formulaire sur le web, les données saisies
peuvent être envoyées au serveur de deux façons. Ainsi, si on remplit
un formulaire avec deux champs `nom` et `prenom`, le programme peut
être appelé des deux façons suivantes

* **Méthode GET**: Dans ce cas, les valeurs du nom et du prenom sont
passés directement dans l'URL. Par exemple, le formulaire pourra
demander l'affichage de la page
`traiter_personne?nom=Dupond&prenom=Jean`.  Le script
`traiter_personne` sera exécuté et il pourra trouver les valeurs de
`nom` et `prenom` dans la variable d'environnement `QUERY_STRING`.\
\
L'[exemple](http://localhost:1234/demos/env.py?nom=Dupond&prenom=Jean) suivant
montre une telle utilisation de la méyhode `GET`.

* **Méthode POST**: La méthode `GET` précédente présente deux
inconvénient majeurs. Tout d'abord, les données dont visibles dans
l'URL (c'est embêtant pour passer un mot de passe par
exemple). Ensuite, la taille d'une URL est en général limitée et il
n'est donc pas possible de passer de gros volume d'information (*eg*
chargement d'un fichier).\
\
La méthode POST permet de résoudre ce problème: au lieu de passer les
données dans l'URL, celles-ci sont écrites sur le fichier standard
d'entrée du programme. Noter que le programme sait combien de
caractères il doit lire, puisque sa variable d'environnement
`CONTENT_LENGTH` contient la taille des données à lire.\
\
Le fichier [test-cgi.py](http://localhost:1234/demos/test-cgi.py)
montre une utilisation des deux méthodes sur un même formulaire.  De
même, on trouvera aussi dans 
[test-file-upload.py](http://localhost:1234/demos/test-file-upload.py) 
un programme permettant de charger sur le serveur un fichier 
résident sur le client.

### Démo

Quatre démos sont disponibles pour ce module

* [Affichage de l'environnement](http://localhost:1234/demos/env.py)
* [Fonction sinus](http://localhost:1234/demos/sinus.py)
* [Test formulaire](http://localhost:1234/demos/test-cgi.py)
* [Chargement de fichier](http://localhost:1234/demos/test-file-upload.py) 
