<!--  Pour emacs : -*- mode:  markdown -*-  -->

## Module mytraceuri


### Description

Ce module permet d'afficher une trace pour chaque URI demandée au serveur.

### Exécution

Ce module affiche les informations relatives à l'URI en cours de
traitement et laisse ensuite les modules inférieurs traiter celle-ci.

Pour voir passer toutes les URI, il faut que ce module soit exécuté en
premier (et donc chargé en dernier).

### Fonctionnement

Le handler associé à ce module est simple: il affiche des informations
sur le fichier standard d'erreur et se termine en renvoyant 0 (quand
un handler renvoie 0, il signale au handler inférieur qu'il n'a pas
traité cette URL, et demande à ce dernier de le faire).

### Démo

Pas de démo pour ce module.
