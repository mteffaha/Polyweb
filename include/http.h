/*
 * http.h	-- Gestion du protocole HTTP
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 24-Apr-2013 09:13 (eg)
 * Last file update:  2-Jun-2013 13:25 (eg)
 */

#ifndef _POLYWEB_HTTP_H
#define _POLYWEB_HTTP_H


#define MAX_HTTP_REQUEST_LINE  500 // Lg max d'une requête HTTP: "GET XXX HTTP/z"
#define MAX_HTTP_INFO	       50 // Nombre maximal de headers dans une requête

// Structure permettant de représenter les infomations passées dans
// les en-têtes d'une requête HTTP
struct http_info {		// Content-Length: 20 ==>
  char *tag;			// 'content-length'
  char *value;			// '20'
};

// Représentation interne d'une requête HTTP. Cette structure contient
// toutes les informations sur la requête elle même (méthode employée,
// URL demandé, ...). Les en-têtes de la requête HTTP sont rangés à la
// dans le tableau info qui est "taillé" à la bonne valeur au moment
// ou la structure est allouée.
struct http_request {
  struct client_info *ci;	// Connexion au client
  char *method;			// GET, POST ....
  char *uri;			// l'URI à traiter
  char *query_string;		// CGI Query string (eventuellement)
  char *protocol;		// "HTTP/1.x"
  int info_length;		// nombre de headers dans info
  struct http_info info[0];     // Les headers 'découpés' de la requête
};


//Lecture d'une requête sur la connexion "ci" et construction de la
//représentation interne de cette requête.
struct http_request* http_get_request(struct client_info *ci);


// construction de la ligne de header indiquant le code de retour de
// la requête, le message qui lui est associé et le type MIME de la
// réponse qui va suivre.
// Par exemple:
//     http_send_response(ci, 404, "File not found", "text/html");
// écrit sur la connexion "ci" les lignes suivantes:
//	HTTP/1.0 404 File not found
//	Connection: close
//	Server: Polyweb ( version ...)
//	Content-type: text/html
//
// Par ailleurs, ces lignes seront suivies d'une ligne vide indiquant que 
// l'en-tête est terminé
//
// Par convention si mime = "", la ligne Content-type et la ligne vide
// finale ne sont pas écrites. Cela sert au scripts CGI, pour qui les
// première information doivent être écrites, alors que la
// détermination du type MIME incombe au script.
void http_send_response(struct client_info *ci, int code, char *msg, char* mime);


// Indique que l'URI demandée se trouve en fait ailleurs. Cette
// fonction produira toujours les 3 lignes suivante
//	HTTP/1.0 302 File has moved
//	Location: XXXX
//	<ligne vide>
// où XXXX est la "destination" passée en paramètre
void http_file_has_moved(struct client_info *ci, char *destination);


// Libération de la mémoire utilisée par la requête r
void http_free_request(struct http_request *r);

#endif
