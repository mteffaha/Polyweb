/*
 *		Misc.c 
 *
 * Author : TEFFAHA Mortadha (teffaha@polytech.unice.fr)
 *
 * Implementation of the misc.h file
 * this files handles critical varialbles like port number, document root and debug mode.
 * also handles loading modules, and some file manipulation function like is_dir and make_path
 */
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#include "misc.h"
#include "polyweb.h"


char* document_root;	// Répertoire racine du serveur
int   listen_port;	// Port sur lequel le serveur tourne
int   debug_mode;

void safeCopyString(char* dest,const char* src){
	if(dest != NULL){
		free(dest);
	}
	dest = (char*)malloc((sizeof(char)*strlen(src))+1);
	if(dest == NULL){
		trace("[%s:misc] unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
	memcpy(dest,src,strlen(src));
	if(dest == NULL){
		trace("[%s:misc] unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
}

void parseNumber(const char* val,int* number){
	
	// Allocate memory where the bad characters will be stored
	char* endptr = (char*)malloc((sizeof(char)*strlen(val))+1);
	if(endptr == NULL){
		trace("[%s:misc] unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
	endptr[strlen(val)] = '\0';// make sure it's a c string
	int _number = strtol(val,&endptr,10); // parse the number
	
	if(errno == ERANGE){
		trace("[%s:misc] Unvalid port number passed the following unvalid characters where found : %s\n",SERVER_NAME,endptr);
	}else{
		*number = _number;	
	}
}

/*
 * Sets the document_root global variable
 * val the new document root
 */
void set_document_root(const char *val){

	safeCopyString(document_root,val);
}

void set_listen_port(const char *val){
	parseNumber(val,&listen_port);
}

void set_debug_mode(const char *val){
	parseNumber(val,&debug_mode);
}


void set_module_directory(const char *name){
}
void module_load(const char *name){
}
