#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "http.h"
#include "handler.h"
#include "network.h"
#include "misc.h"
#include "polyweb.h"
#include "mimetype.h"

struct part{
	char* content;
	struct part* head;
	struct part* tail;
};

struct part *head = NULL;
struct part *tail = NULL;

void addPart(char *part){
	if(head == NULL){
		head = calloc(sizeof(struct part),1);
		head->content = NULL;
		tail = head;
	}
	tail->tail = calloc(sizeof(struct part),1);
	tail->tail->content = part;
	tail = tail->tail;
}

int handler_ssi(struct http_request* req){
	return 0;
	char* path = calloc(sizeof(char),strlen(req->uri)+strlen(document_root)+2);
	if(strlen(req->uri)>1){
		sprintf(path,"%s%s",document_root,req->uri);
	}else{ // id root directory
		return 0;
	}
	//if(strcmp(mimetype_find(path),"text/shtml") == 0){
	if(1){
		
		char* str = calloc(sizeof(char),8192);
		FILE* file = fopen(path,"r");
		while(fgets(str,8192,file) != NULL){
			printf("[%s]\n",str);
			regex_t preg;
			char *pattern = "<--# [^-]*-->";
			int rc;
			size_t nmatch=2;
			regmatch_t pmatch[2];

			if (0 != (rc = regcomp(&preg, pattern, 0))) {
				//printf("regcomp() failed, returning nonzero (%d)\n", rc);
				//exit(EXIT_FAILURE);
				addPart(str);
				continue;
			}

			if (0 != (rc = regexec(&preg, str, nmatch, pmatch, 0))) {
				addPart(str);
				continue;
			}
			else {
				char* query = calloc(sizeof(char),strlen(str));
				memcpy(query,&(pmatch[0].rm_so),pmatch[0].rm_eo - pmatch[0].rm_so);
				printf("\n[%s]\n",query);
			}
			regfree(&preg);
		}
	}
	return 0;
}

void init_module(void){
	handler_uri_add(handler_ssi);
}
