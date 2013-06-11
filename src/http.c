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
#include "http.h"

struct http_request* http_get_request(struct client_info *ci){
	struct http_request *struc_http;
	struc_http=malloc(sizeof(*struc_http)+50*sizeof(struct http_info));
	struc_http->ci=ci;
	FILE*fi=fopen("fichier.txt", "r"); 
	char chaine[500]="";
	char chaineFin[500]="";
	char *pointeur;
	int copy=0;
	int nbHeaders=0;
	int ptInterro = 0;
	int i=0;

	while(strcmp(fgets(chaine,sizeof(chaine),fi),"\n") && (nbHeaders <=50)  ){
		strcat(chaineFin, chaine );
	}

	if(copy ==0){//Pour remplir la première ligne de la requète	
		struc_http->method=strtok(chaineFin," ");
		pointeur = strtok(NULL," ");
		struc_http->protocol=strtok(NULL,"\n");
	}
		
	while((struc_http->info->tag= strtok(NULL,": ")) != NULL ){
		struc_http->info->value=strtok(NULL,"\n");
		nbHeaders++;
	}

	if(copy==0){
		while(pointeur[i]!=' '){//A la recherche du Query-string
			if(pointeur[i]=='?'){
				ptInterro =1;
			}
			i++;//Position de la fin de chaine URI + Query String
		}
		if(ptInterro ==1){//S'il y a un query string
			struc_http->uri=strtok(pointeur,"?");
			struc_http->query_string=strtok(NULL,"\n");
		}
		else{//S'il y a pas de Query String
			struc_http->uri=pointeur;
			struc_http->query_string=NULL;
		}	
		copy=1;
	}	

	struc_http->info_length=nbHeaders;
	return struc_http;
}

void http_send_response(struct client_info *ci, int code, char *msg, char* mime){
	struct * struc_http= http_get_request(ci);
	struc_http->uri=mime;

	fprintf(ci->fout, "HTTP/1.0 %d %s\n",code,msg);
	fprintf(ci->fout, "Connection: close\n");
	fprintf(ci->fout, "Server: Polyweb ( version ...)\n");
	fprintf(ci->fout, "Content-type: %s\n",mime);
	fprintf(ci->fout, "");
}


void http_file_has_moved(struct client_info *ci, char *destination){
	fprintf(ci.fout, "HTTP/1.0 302 File has moved\n");
	fprintf(ci.fout, "Location : %s\n",destination);
	fprintf(ci.fout, "");
}


void http_free_request(struct http_request *r){
	if(r->ci){
		free(r->ci);
	}
	if(r->info){
		free(r->info);
	}
	if(r->info_length)
		free(r->info_length);

	free(r);
}
