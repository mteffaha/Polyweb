/*
 * mimetype.h	-- Polyweb: gestion des types mime
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 24-Apr-2013 15:15 (eg)
 * Last file update:  2-Jun-2013 13:26 (eg)
 */

#ifndef POLYWEB_MIMETYPE_H
#define POLYWEB_MIMETYPE_H


// Ajout d'une règle de type MIME. La règle contient deux mots: un
// suffixe de fichier et le type MIME qui lui est associé. Le suffixe
// et le type doivent être séparés par un ou plusieurs espaces ou
// caractères de tabulation.
void mimetype_new_rule(char* rule);


// Recherche du type MIME associé au chemin de fichier passé en
// paramètre.  Si le fichier n'a pas de suffixe ou si le suffixe ne
// correspond pas à une association connue, la valeur "text/plain" est
// renvoyée.
char *mimetype_find(const char *path);

#endif
