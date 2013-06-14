#include <stdio.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include "../include/http.h"
#include "../include/handler.h"
#include "../include/misc.h"
#include "../include/network.h"
#include "../include/config.h"

#define MAX 1024


int handler(struct http_request *req){
	
	char adresse[MAX]="";
	strcpy(adresse,document_root);
	strcat(adresse,req->uri);
	int fdout = fileno(req->ci->fout);
	
	//close(fdout);
	if(strstr(req->query_string , "fontify")!=NULL){
		http_send_response(req->ci,200,"Ok","text/html");
		if(fork()){
		dup2(fdout,1);
		execlp("pygmentize","pygmentize", "-f", "html", "-Ofull", adresse,NULL);
		_exit(0);
		}return 1;
	}
	if(strstr(req->query_string , "markdown")!=NULL){
		http_send_response(req->ci,200,"Ok","text/html");
		if(fork()){
			dup2(fdout,1);
		execlp("/usr/bin/pandoc","/usr/bin/pandoc", "-s", adresse,NULL);
			_exit(0);
		}
		return 1;
	}

	return 0;
}

void init_module(void)
{	
	trace("Loading .. \n");
	handler_uri_add(handler);
}

