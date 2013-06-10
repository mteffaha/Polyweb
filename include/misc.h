/*
 * misc.h	-- Serveur Polyweb -- Trucs divers
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 26-Apr-2013 22:56 (eg)
 * Last file update:  2-Jun-2013 15:13 (eg)
 */

#ifndef POLYWEB_MISC_H
#define POLYWEB_MISC_H

#include <limits.h>

#define DEFAULT_PORT    1234	// port sur lequel le serveur répond par défaut
#define DEFAULT_ROOT    "./"	// racine par défaut du serveur
#define DEFAULT_EXT_DIR "./"	// répertoire par défaut extensions/modules

/* ----------------------------------------------------------------------
 *  Variables globales publiques du serveur
 * ---------------------------------------------------------------------- */

extern char* document_root;	// Répertoire racine du serveur
extern int   listen_port;	// Port sur lequel le serveur tourne
extern int   debug_mode;	// > 0 si on est en debug


/* ----------------------------------------------------------------------
 *  Primitives liées à la configuration du serveur
 * ---------------------------------------------------------------------- */

void set_document_root(const char *val);  // permet de changer document_root
void set_listen_port(const char *val);	  // permet de changer listen_port
void set_debug_mode(const char *val);	  // permet de changer debug_mode


/* ----------------------------------------------------------------------
 *  Gestion du chargement dynamique
 * ---------------------------------------------------------------------- */
void set_module_directory(const char *name); // répertoire des extensions
void module_load(const char *name);	     // chargement d'une extension


/* ----------------------------------------------------------------------
 * Utilitaires 
 * ---------------------------------------------------------------------- */

typedef char path_t[PATH_MAX];


// Renvoie 1 si "dir" est un répertoire, 0 sinon
int is_dir(const char *dir);

// Construction d'un chemin à partir du nom de répertoire "dir" et du nom de
// fichier "file" dans "res".
void make_path(char *res, const char *dir, const char *file);

// Pour afficher des traces sur stderr si on est en mode debug
#define trace(...)	{if (debug_mode) fprintf(stderr, __VA_ARGS__);}
#define tracen(n, ...)  {if (debug_mode>=(n)) fprintf(stderr, __VA_ARGS__);}
#endif
