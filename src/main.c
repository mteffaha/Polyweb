/*
 * main.c	-- Un petit serveur web - projet SI3
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Apr-2013 12:23 (eg)
 * Last file update:  2-Jun-2013 20:11 (eg)
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "polyweb.h"
#include "network.h"
#include "http.h"
#include "handler.h"
#include "config.h"
#include "mimetype.h"
#include "misc.h"


struct option_action options[] = {
  {"listen-port",   (option_setter) set_listen_port},
  {"document-root", (option_setter) set_document_root},
  {"mime-type",	    (option_setter) mimetype_new_rule},
  {"modules-dir",   (option_setter) set_module_directory},
  {"module",	    (option_setter) module_load},
  {"debug-mode",    (option_setter) set_debug_mode},
  {NULL, NULL}
};

void serve_page(int server){
  struct client_info ci;
  struct http_request* req;

  /* Attendre un client */
  accept_connection(server, &ci);

  if (fork() == 0) {
    tracen(3, "Connection from %s (sd = %d)\n", ci.hostname, ci.sd);

    /* Récuperer la requête */
    req = http_get_request(&ci);
    if (req) {
      /* Construire une réponse en parcourant tous les handlers */
      handler_build_response(req);

	printf("before free_request\n");
      /* Libérer la mémoire */
      http_free_request(req);
      printf("after free request\n");
    }

    tracen(3, "Connection with %s closed.\n", ci.hostname);
    exit(0); //ce exit implique la fermeture de la connexion côté client.
  }
  /* Fermer la connection côté père*/
  shutdown_connection(&ci);
}


int main(int argc, char **argv)
{
  int server;
  char *config_file;

  printf("*** %s started ...\n", SERVER_FULL_NAME);

  switch (argc) {
    case 1:		    // pas de paramètre: prendre le fichier par défaut
      config_file = "./polywebrc";
      break;
    case 2:		    // un paramètre: prendre ce fichier
      config_file = argv[1];
      break;
    default:		    // Erreur
      fprintf(stderr, "Usage: %s [config-file]\n", *argv);
      return EXIT_FAILURE;
  }

  /* Lire le fichier de configuration */
  config_read_file(config_file, options);
  trace("***   Document Root: %s\n", document_root);
  trace("***     Listen port: %d\n", listen_port);

  /* Creer un serveur  et servir les pages demandées */
  server = create_server(listen_port);
  for ( ; ; )
    serve_page(server);

  return EXIT_SUCCESS;
}
