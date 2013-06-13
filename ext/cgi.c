/*
 *		cgi.c 
 *
 * Author : TEFFAHA Mortadha (teffaha@polytech.unice.fr)
 *
 * the main file for the extension module cgi, whose responsible for implementing the Common Gateway Interface . more details in cgi.md
 */
#define _XOPEN_SOURCE  
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "http.h"
#include "handler.h"
#include "network.h"
#include "misc.h"
#include "polyweb.h"

#define CGI_GATEWAY 	"CGI/1.1"
#define GET		"GET"
#define POST		"POST"
#define CGI_PATH	"/bin:/usr/bin:/usr/local/bin"
#define SERVER_PROTOCOL "HTTP/1.0"
#define PRINT_ENV(ENV)	print_cgi_env(ENV,stdout)

/*
 * a struct containing all cgi envirement variables
 */
typedef struct{
	char* document_root;		// server root directory 
	char* gateway_interface;	// CGI version ( CGI/1.1 for this server)
	char* path;			// path where the programs are available
	char* query_string;		// query string (GET parameters)
	char* remote_adr;		// client IP Adress
	char* request_method;		// request method (GET or POST)
	char* request_uri;		// the request uri
	char* server_protocol;		// server protocol (HTTP/1.0 for this server)
	char* server_software;		// the name and version of the server
	char* content_type;		// information about POST data encoding
	int content_length;		// the length of the POST data
}cgi_env;


/*
 * Print a cgi_env structure to  target file passed
 * cgi_env	a pointer to the structure to be printed
 * target	a pointer to the file where this struture need to be printed
 */
void print_cgi_env(const cgi_env* env,FILE* target){
	fprintf(target,"Document Root:\t\t%s\n"		,env->document_root);	
	fprintf(target,"Gateway Interface:\t\t%s\n"	,env->gateway_interface);
	fprintf(target,"Path:\t\t%s\n"			,env->path);
	fprintf(target,"Query String:\t\t%s\n"		,env->query_string);
	fprintf(target,"Remote Adr:\t\t%s\n"		,env->remote_adr);
	fprintf(target,"Request Method:\t\t%s\n"	,env->request_method);
	fprintf(target,"Request Uri:\t\t%s\n"		,env->request_uri);
	fprintf(target,"Server Protocol:\t\t%s\n"	,env->server_protocol);
	fprintf(target,"Server Software:\t\t%s\n"	,env->server_software);
	fprintf(target,"Content Length:\t\t%d\n"	,env->content_length);
	fprintf(target,"Content Type:\t\t%s\n"		,env->content_type);
}

/*
 * Free an allocated cgi_env structure
 * env 		the cgi_env structure to be freed
 */
void free_cgi_env(cgi_env* env){
	free(env->document_root);		
	free(env->gateway_interface);	
	free(env->path);		
	free(env->query_string);		
	free(env->remote_adr);	
	free(env->request_method);	
	free(env->request_uri);	
	free(env->server_protocol);	
	free(env->server_software);	
	if(env->content_type != NULL)
		free(env->content_type);	
	free(env);	
}

/*
 * Initialise the cgi envirement 
 * req 	the http_request 
 */
cgi_env* init_cgi_env(struct http_request* req){
	// we allocate the structure
	cgi_env* env =calloc(sizeof(cgi_env),1);
	
	// we prepare the envirement variables
	env->document_root = calloc(sizeof(char),strlen(document_root)+1);
	strcpy(env->document_root,document_root);
	env->gateway_interface = calloc(sizeof(char),strlen(CGI_GATEWAY)+1);
	strcpy(env->gateway_interface,CGI_GATEWAY);
	
	env->path = calloc(sizeof(char),strlen(CGI_PATH));
	strcpy(env->path,CGI_PATH);
	
	env->query_string = calloc(sizeof(char),strlen(req->query_string)+1);
	strcpy(env->query_string,req->query_string);
	
	env->remote_adr = calloc(sizeof(char),strlen(req->ci->hostip)+1);
	strcpy(env->remote_adr,req->ci->hostip);
	
	env->request_method = calloc(sizeof(char),strlen(req->method)+1);
	strcpy(env->request_method,req->method);
	
	env->request_uri = calloc(sizeof(char),strlen(req->uri)+1);
	strcpy(env->request_uri,req->uri);
	
	
	env->server_protocol = calloc(sizeof(char),strlen(SERVER_PROTOCOL)+1);
	strcpy(env->path,SERVER_PROTOCOL);
	
	env->server_software = calloc(sizeof(char),strlen(SERVER_FULL_NAME)+1);
	strcpy(env->path,SERVER_FULL_NAME);
	
	// we set the content_type / content_length to default values
	int infos = req->info_length;
	env->content_length = 0;
	env->content_type =NULL;
	
	// we check if they were set in the http_info structure, and copy the corresponding values
	while(infos-- >=0){
		if(strcmp(req->info[infos].tag,"Content-length") == 0){
			env->content_length = atoi(req->info[infos].value);
			continue;
		}
		if(strcmp(req->info[infos].tag,"Content-Type")==0){
			env->content_type = calloc(sizeof(char),strlen(req->info[infos].value));
			strcpy(env->content_type,req->info[infos].value);
			continue;
		}

	}

	
	return env;
}

/*
 * checks wether the path supplied is an executable
 *
 * path 	path to check
 */
int is_exec(char* path){
	if(is_dir(path)){
		return 0;
	}

	if (access(path, X_OK) != -1) {
    		return 1;
	} else {
		return 0;
	}
}

/*
 *	Setts and envirement variable.
 *
 * var		the name of the variable to be set
 * value	the value of the variable to be set
 */
void setvar(char* var,char*value){
	char* buffer = calloc(sizeof(char),MAX_HTTP_REQUEST_LINE);
	sprintf(buffer,"%s=%s",var,value);
	putenv(buffer);
	
	//free(buffer);
}

/*
 *Creates the necessary envirement variables for running a cgi script
 * env		the cgi_env structu to set
 */
void prepare_env(const cgi_env* env){
	char* clength = calloc(sizeof(char),MAX_HTTP_REQUEST_LINE);
	sprintf(clength,"%d",env->content_length);
	setvar("DOCUMENT_ROOT",env->document_root);
	setvar("GATEWAY_INTERFACE",env->gateway_interface);
	setvar("PATH",env->path);
	setvar("QUERY_STRING",env->query_string);
	setvar("REMOTE_ADDR",env->remote_adr);	
	setvar("REQUEST_METHOD",env->request_method);
	setvar("REQUEST_URI",env->request_uri);
	setvar("SERVER_PROTOCOL",env->server_protocol);
	setvar("SERVER_SOFTWARE",env->server_software);
	setvar("CONTENT_TYPE",env->content_type);
	setvar("CONTENT_LENGTH",clength);
		
}
/*
 * the handler function that will be hooked (Added to the list of available handlers)to the server
 */
int handler_cgi(struct http_request* req){
	char* path = calloc(sizeof(char),strlen(req->uri)+strlen(document_root)+2);
	if(strlen(req->uri)>1){
		sprintf(path,"%s%s",document_root,req->uri);
	}else{ // id root directory
		return 0;
	}
	// we check that this is an executable, and that have access
	if(!is_exec(path)){
		return 0;
	}
	printf("PATH : [%s],DR:[%s]\n",path,document_root);
	// we start by fetching the envirement variables
	cgi_env* env = init_cgi_env(req);
	// set env variables
	prepare_env(env);
	// end POST DATA if available
	printf("send POST data\n");
	return 1;
}

void init_module(void){
	// register the module(hook it to the server).
	handler_uri_add(handler_cgi);
}
