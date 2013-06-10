<!--  Pour emacs : -*- mode:  markdown -*-  -->

##Module ssi


### Description

Ce module permet d'implémenter une version simplifiée du mécanisme de
[Server Side Includes](http://fr.wikipedia.org/wiki/Server_Side_Includes).

### Exécution

Ce module ne traite que deux directives (voir ci-dessous). Le
traitement des directives ne se fait que sur les fichiers suffixés par
`.shtml`. La autres fichiers sont traités par les modules inférieurs.

### Fonctionnement

Cette version n'implémente que deux directives:

* include
* exec

De plus, pour simplifier l'analyse, il ne peut y avoir qu'un seule
directive directives sur seule ligne du fichier `.shtml` (mais il peut
y avoir du texte avant et après la balise d'inclusion ou d'exécution).

Lorsqu'on inclut un fichier ou lorsqu'on exécute une commande, le
répertoire par défaut est le répertoire qui contient le fichier
`.shtml`. Cela permet l'inclusion de commandes dans le contexte du
fichier qui a déclenché l'exécution du module sans à avoir à connaître
le chemin exact du fichier `.shtml`. L'accès aux fichiers ou au
commandes contenues dans le fichier `.shtml` peur donc se faire de
façon relative.

Un exemple de fichier .shtml est donné ci-dessous:

````{.html}
           <!--#include file="entete.html" -->
           <p>Le répertoire contient les fichiers suivants&nbsp;:</p>
           <pre><!--#exec cmd="ls"--></pre>
           <!--#include file="pied.html" -->
````


**Note**: l'analyse des balises SSI se fait avec des expressions
  régulières (primitives `regcomp`, `regexec`, ...).


### Démo

Deux démos sont disponibles pour ce module:

* [demo1](http://localhost:1234/demos/test-ssi1.shtml) 
* [demo2](http://localhost:1234/demos/test-ssi2.shtml)
