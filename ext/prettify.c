#include <stdio.h>
#include <dlfcn.h>
#include "unistd.h"
#include "../include/http.h"
#include "../include/handler.h"
#include "../include/misc.h"

int handler(struct http_request *req){
	//printf("rres : %s OK",req->uri); // affiche ca : "rres : /ext/simple-module.c OKrres : /ext/simple-module.c OK"

	execlp(req->uri,req->uri, "-f html", "Ofull", "simple-module.c",NULL);
	return 0;
}

void init_module(void)
{	
	trace("bouboul\n");
	handler_uri_add(handler);
}

