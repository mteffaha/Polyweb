/*
 * network.h	-- Serveur Polyweb -- la partie réseau
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 22-Apr-2013 12:26 (eg)
 * Last file update: 24-Apr-2013 09:56 (eg)
 */

#ifndef _POLYWEB_NETWORK_H
#define _POLYWEB_NETWORK_H

struct client_info {
  char *hostip;		// client IP number
  char *hostname;	// client host name (if known) or client IP
  int sd;		// client socket descriptor
  FILE *fin;		// client socket descriptor as an input file
  FILE *fout;		// client socket descriptor as an output file
};

// create a server on given port. Return a socket descriptor where we must
// accept the connections
int create_server(int port);

// Wait for a connection. Unlock when a client is present
void accept_connection(int server, struct client_info *ci);

// Shudown the connection in ci
void shutdown_connection(struct client_info *ci);

#endif 
