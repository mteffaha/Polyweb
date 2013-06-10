/*
 * main.c	-- Un petit serveur web - projet SI3
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Apr-2013 12:23 (eg)
 * Last file update:  2-Jun-2013 16:03 (eg)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "polyweb.h"
#include "network.h"
#include "misc.h"

char* strupper(char *s)			// met en majuscules la chaîne s
{
  char *tmp;

  for (tmp = s; *s; s++)
    *s = toupper(*s);
  return tmp;
}


void discuter(int server){
  char line[200];
  struct client_info ci;
  int n;

  /* Attendre un client */
  accept_connection(server, &ci);

  if (fork() == 0) {
      printf("Connection from %s (sd = %d)\n", ci.hostname, ci.sd);

      /* Copier toutes les lignes venant du client en majuscules */
      while ((n = read(ci.sd, line, sizeof(line)-1)) > 0) {
	write(1, line, n);			// trace sur stdout
	write(ci.sd, strupper(line), n);	// Envoyer une réponse au client
      }
  }
}


int main(int argc, char **argv)
{
  int server;


  /* Creer un serveur */
  server = create_server(DEFAULT_PORT);
  printf("Server started on port %d...\n", DEFAULT_PORT);

  /* Discuter avec le client */
  while (1)
    discuter(server);

  return 0;
}
