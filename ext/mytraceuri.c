#include <stdio.h>
#include <dlfcn.h>

#include "../include/http.h"
#include "../include/handler.h"
#include "../include/misc.h"

int handler(struct http_request *req){
	trace("mytrace: URI=' : %s' Query='%s'\n",req->uri,req->query_string);
	return 0;
}

void init_module(void)
{
	handler_uri_add(handler);
}

