/*
 * main.c	-- Un petit serveur web - projet SI3
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Apr-2013 12:23 (eg)
 * Last file update: 25-May-2013 12:39 (eg)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "polyweb.h"
#include "network.h"
#include "misc.h"


void serve_page(int server){
  char line[200];
  struct client_info ci;
  time_t  lt = time(NULL);

  /* Attendre un client */
  accept_connection(server, &ci);
  printf("Connection from %s (sd = %d)\n", ci.hostname, ci.sd);

  /* Parser le header HTTP */
  while (fgets(line, sizeof(line), ci.fin)) {
    printf("Header => %s", line);
    if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) break;
  }

  // Construire une réponse selon le protocole HTTP
  fprintf(ci.fout, "HTTP/1.0 200 OK\r\n");
  fprintf(ci.fout, "Connection: close\r\n");
  fprintf(ci.fout, "Content-type: text/plain\r\n");
  fprintf(ci.fout, "\r\n");
  fprintf(ci.fout, "Date courante %s\n", asctime(localtime(&lt)));

  // Fermer la connection
  shutdown_connection(&ci);
  printf("Connection with %s closed.\n", ci.hostname);
}


int main(int argc, char **argv)
{
  int server;

  /* Creer un serveur */
  server = create_server(DEFAULT_PORT);
  printf("Polyweb started on port %d...\n", DEFAULT_PORT);

  while (1)
    serve_page(server);

  return 0;
}
