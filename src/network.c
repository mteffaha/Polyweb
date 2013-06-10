/*
 * network.c	-- Serveur Polyweb -- la partie réseau
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Apr-2013 12:26 (eg)
 * Last file update: 24-Apr-2013 15:54 (eg)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "network.h"

int create_server(int port)
{
  int sd, yes = 1;
  struct sockaddr_in sin;

  /* Get an internet domain socket */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("exit");
    exit(1);
  }

  /* Allow reusing the socket port */
  if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
    perror("setsockopt");
    exit(1);
  }

  /* Fill  socket structure */
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons(port);

  /* bind the socket to the port number */
  if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
    perror("bind");
    exit(1);
  }

  /* Listen */
  if (listen(sd, 5) == -1) {
    perror("listen");
    exit(1);
  }

  return sd;
}

void accept_connection(int server, struct client_info *ci)
{
  struct sockaddr_in sin;
  struct hostent *host;
  socklen_t len = sizeof(sin);
  int new_sd;
  FILE *fin, *fout;

  /* Accept the connection */
  if ((new_sd = accept(server, (struct sockaddr *) &sin, &len)) < 0) {
    perror("accept");
    exit(1);
  }

  /* Create input and output handlers on the socket descriptor as FILE*  */
  if ((fin = fdopen(new_sd, "r")) < 0) {
      perror("fdopen (read)");
      exit(1);
  }
  if ((fout = fdopen(new_sd, "w")) < 0) {
      perror("fdopen (write)");
      exit(1);
  }

  /* Fill the client info structure */
  host = gethostbyaddr((char *) &sin.sin_addr, sizeof(sin.sin_addr), AF_INET);

  ci->hostip   = (char *) inet_ntoa(sin.sin_addr);
  ci->hostname = host? (char*) host->h_name: ci->hostip;
  ci->sd       = new_sd;
  ci->fin      = fin;
  ci->fout     = fout; 
}

void shutdown_connection(struct client_info *ci)
{
  fflush(ci->fout);
  fclose(ci->fin);
  fclose(ci->fout); 
  shutdown(ci->sd, SHUT_RDWR);
  close(ci->sd);
}
