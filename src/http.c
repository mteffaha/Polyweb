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
#include <stdlib.h>

#include "network.h"
#include "misc.h"
#include "http.h"
#include "polyweb.h"

struct http_request* http_get_request(struct client_info *ci){
	struct http_request *struc_http;
	struc_http=malloc(sizeof(*struc_http)+MAX_HTTP_INFO*sizeof(struct http_info));
	struc_http->ci =ci;
	char chaine[MAX_HTTP_REQUEST_LINE];
	int copy=0;
	int nbHeaders=0;
	char *pointeur = fgets(chaine,sizeof(chaine),ci->fin);

	while(strcmp(pointeur,"\r\n") != 0 && (nbHeaders <=MAX_HTTP_INFO)  ){
		
		if(copy==1){
			char* item = strtok(chaine,": ");
			if(item == NULL)
			continue;
			struc_http->info[nbHeaders].tag= strdup((item != NULL)?item:"");
			item = strtok(NULL,"\n");
			struc_http->info[nbHeaders].value = strdup((item != NULL)?item:"");
			nbHeaders++;
		}

		if(copy ==0){	
			char* item = strtok(chaine," ");
			struc_http->method=strdup((item!=NULL)?item:"");
			item = strtok(NULL," ");
			struc_http->uri=strdup((item!=NULL)?item:"");
			item = strtok(NULL,"\n");
			struc_http->protocol=strdup((item!=NULL)?item:"");
			
			copy=1;
		}
		pointeur = fgets(chaine,sizeof(chaine),ci->fin);
	}

	if(strstr(struc_http->uri , "?") != NULL){
		char* item = strtok(struc_http->uri,"?");
		struc_http->uri = strdup((item!=NULL)?item:"");
		item = strtok(NULL,"\n");
		struc_http->query_string = strdup((item!=NULL)?item:"");
	}
	else{
		struc_http->query_string = calloc(sizeof(char),1);
	}	

	struc_http->info_length=nbHeaders;

	return struc_http;
}

void http_send_response(struct client_info *ci, int code, char *msg, char* mime){
	fprintf(ci->fout, "HTTP/1.0 %d %s\n",code,msg);
	fprintf(ci->fout, "Connection: close\n");
	fprintf(ci->fout, "Server: %s\n",SERVER_FULL_NAME);
	fprintf(ci->fout, "Content-type: %s\n",mime);
	fprintf(ci->fout, "\n");
}


void http_file_has_moved(struct client_info *ci, char *destination){
	fprintf(ci->fout, "HTTP/1.0 302 File has moved\n");
	fprintf(ci->fout, "Location : %s\n",destination);
	fprintf(ci->fout, "\n");
}


void http_free_request(struct http_request *r){

	free(r);
}
