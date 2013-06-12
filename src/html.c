/*
 * html.c	-- Un petit serveur web - projet SI3
 *
 * Copyright © 2013 Paul Lavoine - Polytech'Nice-Sophia
 *
 *           Author: Paul Lavoine
 *    Creation date: 10-Juin-2013 
 *    Last file update: 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "polyweb.h"
#include "network.h"
#include "misc.h"

struct http_request* http_get_request(struct client_info *ci){
	struct *http_request struc_http;
	
	struc_http->ci=ci;
	struc_http->protocole ="HTTP/1.0";

	return struc_http;
}

void http_send_response(struct client_info *ci, int code, char *msg, char* mime){
	struct * struc_http= http_get_request(ci);
	struc_http->uri=mime;


	fprintf(ci.fout, "HTTP/1.0 %d %s\r\n",msg,code);
	fprintf(ci.fout, "Connection: close\r\n");
	fprintf(ci.fout, "Server: Polyweb ( version ...)\r\n");
	fprintf(ci.fout, "Content-type: %s\r\n",mime);
	fprintf(ci.fout, "");
}


void http_file_has_moved(struct client_info *ci, char *destination){
	fprintf(ci.fout, "HTTP/1.0 302 File has moved\n");
	fprintf(ci.fout, "Location : %s\n",destination);
	fprintf(ci.fout, "");
}


void http_free_request(struct http_request *r){
	/*r->ci->tag=NULL;			
	r->ci->value=NULL;			
	r->method=UNSUPPORTED;			
	r->uri=NULL;			
	r->query_string=NULL;		
	r->protocol=NULL;	
	r->info_length=50;*/

	if ( r->uri )
		free(r->uri);	
	if ( r->query_string )
		free(r->query_string);
	if ( r->protocol )
		free(r->protocol);
}






