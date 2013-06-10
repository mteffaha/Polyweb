/*
 * module.c	-- Un module chargé dynamiquement
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 25-Apr-2013 21:11 (eg)
 * Last file update:  8-Jun-2013 22:13 (eg)
 */

#include <stdio.h>
#include <dlfcn.h>
#include "misc.h"

/*
   PRINCIPE:

   Un module doit comporter une fonction

        void init_module(void);

   Cette fonction est en quelque sorte le "main" du module. Elle est
   appelée systématiquement par le serveur au moment du chargement
   d'un module.

   Ce module doit être compilé de la façon suivante:

        gcc -shared -fPIC -o simple-module.so simple-module.c

*/


/*
   Un module super simple qui ne fait rien de spécial.

   Lorsque ce module est chargé, il affiche des choses sur la sortie
   standard. Noter qu'un module peut utiliser des variables globales
   ou des fonctions du programme qui le charge (etant données les
   options que l'on passe à dlopen, il y aura une erreur à l'exécution
   si on fait référence à un symbole qui n'existe pas dans ce
   programme).
*/

void init_module(void)
{
  if (debug_mode)
    // comme on le voit, on peut utiliser une globale du programme dans un module
    fprintf(stderr, "Loading simple-module...\n");

  // et on peut aussi utiliser une fonction du programme
  fprintf(stderr, "isdir(\"/etc\") = %d\n",	   is_dir("/etc"));
  fprintf(stderr, "isdir(\"/etc/passwd\") = %d\n", is_dir("/etc/passwd"));
}
