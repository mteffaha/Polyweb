/*
 * config.h	-- Serveur Polyweb: gestion des options de configuration
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 26-Apr-2013 19:04 (eg)
 * Last file update:  2-Jun-2013 15:34 (eg)
 */

#ifndef POLYWEB_OPTIONS_H
#define POLYWEB_OPTIONS_H

#define DFLT_CONFIG_FILE  "./polywebrc" // Fichier de configuration par default

#define MAX_OPTIONS	  100	// Nombre maximal d'options possibles
#define CONFIG_MAX_LENGTH 200	// Longueur maximale d'une ligne de configuration

typedef void (*option_setter)(const char *arg);

// Structure permettant d'associer une action à une option du
// serveur. La fonction présente dans la stucture sera appelée lors de
// la lecture du fichier d'options avec le texte qui suit le nom de la
// commande.
struct option_action {
  char *command;	// nom de l'option
  option_setter func;	// action à déclencher losque l'option est lue
};


// Ajouter les nouvelles options contenues dans le tableau "actions".
// Ces actions s'ajoutent aux actions déjà connues du système.
void config_register(struct option_action *actions);



// Lecture du fichier de configuration du serveur. La liste d'actions
// passée en paramètre permet de définir complètement le traitement
// associé à chacune des options du serveur. La syntaxe d'un fichier
// d'options est simple:
//    - les commentaires commencent par un "#" et se poursuivent
//      jusqu'à la fin de la ligne
//    - Une option de configuration est formée de 2 "mots":
//         - le nom de l'option (placé en début de ligne)
//         - la valeur de l'option (texte qui suit le nom de l'option).
// Exemple de ligne du fichier d'options
//
// opt       abc def gh         # une exemple
//
// Ici le nome de l'option est 'opt' et sa valeur est 'abc def gh'.
// Noter que les espaces avant et après la valeur de l'option ne font
// pas partie de la valeur de l'option
void config_read_file(const char* pathname, struct option_action *actions);

#endif
