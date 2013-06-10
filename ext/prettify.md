<!--  Pour emacs : -*- mode:  markdown -*-  -->

## Module prettify


### Description

Ce module permet d'embellir un fichier lorsqu'il est chargé par un
navigateur Web. Cela peut servir pour "fontifier" des programmes ou
afficher en HTML des fichiers
[Markdown](http://fr.wikipedia.org/wiki/Markdown).

### Exécution
Ce module délègue le traitement d'une URL au module inférieur
si celle-ci ne comporte pas de directive d'embellissement.

### Fonctionnement
Deux directives sont reconnues par ce module.

* **fontify**: cette directive permet d'afficher une version
  "fontifiée" en HTML du fichier. Pour effectuer la transformation en
  HTML, on pourra utiliser la commande *pygmentize*. Par exemple, pour
  obtenir sur la sortie standard une version enjolivée du fichier C
  `file.c`, on peut exécuter:

    `pygmentize -f html -Ofull file.c`

* **markdown**: cette directive permet d'afficher une version HTML
d'un fichier utilisant le langage de balises légères
[Markdown](http://fr.wikipedia.org/wiki/Markdown).  La version HTML
d'un fichier markdown peut être obtenue grâce à la commande *pandoc*.
Ainsi, pour obtenir une version enjolivée du fichier `file.md` sur la
sortie standard, on peut exécuter:

	`pandoc -s file.md`

Les directives *fontify* et *markdown* sont placées à la fin de
l'URI. Ainsi,

* l'URI <http://localhost:1234/ext/simple-module.c> permet d'afficher
  le fichier simple-module.c normalement (dans ce cas, le module ne
  fait rien et délègue l'affichage au module inférieur).

* l'URI <http://localhost:1234/ext/simple-module.c?fontify> permet de
  voir le fichier enjolivé (dans ce cas le module effecte le
  traitement en utilisant la sortie de la commande de "fontification"
  sur le fichier `ext/simple-module.c`).

De même:

* l'URI: <http://localhost:1234/ext/prettify.md> permet d'afficher la
  documentation du fichier *prettify* en texte brut, alors que

* l'URI: <http://localhost:1234/ext/prettify.md?markdown> permet de
  l'afficher en HTML.

### Options du module prettify

Ce module accepte deux options `fontify-cmd` et `markdown-cmd` qui
peuvent être placées dans le fichier de configuration du serveur web
(fichier `polywebrc`). L'utilisation de ces options doit se faire
après que le module `prettify ait été chargé.

* `fontify-cmd`: permet de spécifier la commande Unix utilisée pour la
  fontification. Par exemple: `fontify-cmd	pygmentize -f html -Ofull`

* `markdown-cmd`: permet de spécifier la commande Unix utilisée pour
  afficher en HTML  un fichier Markdown. Par exemple: 
  `markdown-cmd	pandoc -s`


### Démo

Une démo de ce module est accessible
[ici](<http://localhost:1234/ext/prettify.md?markdown>).


### Divers

Pour fonctionner, les modules suivants doivent être installés:

* **pandoc** (pour installer sur Ubuntu: `sudo apt-get install pandoc`)

* **python-pygments** (pour installer sur Ubuntu: `sudo apt-get install python-pygments`)

<!--  LocalWords:  pygmentize markdown pandoc md fontifier fontify
 -->
<!--  LocalWords:  Ubuntu
 -->
