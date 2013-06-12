/*
 *		Handler.c 
 *
 * Author : TEFFAHA Mortadha (teffaha@polytech.unice.fr)
 *
 * Implementation of the handler.h file as requiest in the distribution files
 * for storing the handlers we use a custom built Singly Linked-List.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include "network.h"
#include "http.h"
#include "handler.h"
#include "misc.h"
#include "polyweb.h"
/*
// Le type de handler de requêtes HTTP
typedef int (*uri_handler_t)(struct http_request *req);
*/

/*
 * HTTP 404 error handler
 *
 * the last resort handler that will return a 404 error
 */
 int handler_404Error(struct http_request *req){
	
	FILE* out = req->ci->fout;

	/*fprintf(out,"%s 404 Not Found\n",req->protocol);
	fprintf(out,"Content-Type: text/html\n\n");
	*/
	http_send_response(req->ci,404,"Not Found","text/html");	
	fprintf(out,"<!doctype html>\n<head>\n\t<title>404 Not Found</title>\n</head>\n<body>\n<h1>404 Not Found</h1>\n<p>The requested ressource was not found</p>\n</body>\n</html>\n");
	return 1;
 }

/*
 * FileExplorer handler
 *
 * a handler that allows the user to navigate the files available in the server.
 */
int handler_FileExplorer(struct http_request *req){
	// we start by checking that the query correspond to a valid path relative to the document root
	char* path = calloc(sizeof(char),strlen(req->uri)+strlen(document_root)+2);
	if(path == NULL){
		trace("[%s:handler] Unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
	if(strcmp(req->uri,"/")!=0){
		sprintf(path,"%s/%s",document_root,req->uri);
	}else{
		sprintf(path,"%s",document_root);
	}
	// we try to open it as directory
	int n=0,i=0;
	struct dirent** pdir;
	struct stat stbuf;
	char timebuff[25];
	
	if(!is_dir(path)){
		return 0;
	}

	// we start printing the header
	http_send_response(req->ci, 200, "Ok", "text/html");
	fprintf(req->ci->fout,"<!doctype html>\n<head>\n\t<title>%s : File Exlorer</title>\n",SERVER_NAME);
	fprintf(req->ci->fout,"<style type=\"text/css\">"); 
	fprintf(req->ci->fout,"h1{font-family:verdana;font-size:20pt;margin:20px;}\ndiv{width:960px;margin:auto;}table{width:100%;}table thead{background-color:#EEEEEE;}");
	fprintf(req->ci->fout,"table td{padding:10px;text-align;left;}" );
	fprintf(req->ci->fout,"</style></head>\n<body>\n<div><h1>%s : File Explorer</h1><table><thead><tr><td>Name</td><td>Type</td><td>Last Modified</td><td>Size</td></tr></thead><tbody>",SERVER_NAME);


	n = scandir(path, &pdir, 0, alphasort);
	if(n<0){
		printf("n<0\n");
		return 0;
	}
	while(n--){
		// we skip the current directory
		if(strcmp(".",pdir[i]->d_name)== 0){
			i++;
			continue;
		}
		if(strcmp("..",pdir[i]->d_name)==0){
			i++;
			if(strlen(req->uri) != 1){
				
				int i = strlen(req->uri)-1;
				char parent[strlen(req->uri)];
				
				strcpy(parent,req->uri);
				while(i>0 && parent[i] != '/'){parent[i] = '\0';i--;}
				if(strlen(parent) > 1 && parent[strlen(parent)-1] == '/'){
					parent[strlen(parent)-1] = '\0';
				}
				fprintf(req->ci->fout,"<tr><td colspan=\"4\"><a href=\"%s\">Parent Directory</a></td></tr>",parent);
				continue;
			}
			fprintf(req->ci->fout,"<tr><td colspan=\"4\"><a href=\"/\">Parent Directory</a></td></tr>");
			continue;
		}
		char* file = calloc(sizeof(char),strlen(path)+strlen(pdir[i]->d_name)+2);
		sprintf(file,"%s/%s",path,pdir[i]->d_name);
		fprintf(req->ci->fout,"<tr><td>");
		if(stat(file,&stbuf) != 0){
			trace("[%s:handler] Error while accessing file information , %s\n",SERVER_NAME,strerror(errno));
			
		}
		free(file);
		file = NULL;
		if(S_ISDIR(stbuf.st_mode)){
			if(strlen(req->uri) > 1){
				fprintf(req->ci->fout,"<a href=\"%s/%s\">%s</a></td><td>Folder</td>",req->uri,pdir[i]->d_name,pdir[i]->d_name);
			}else{
				fprintf(req->ci->fout,"<a href=\"/%s\">%s</a></td><td>Folder</td>",pdir[i]->d_name,pdir[i]->d_name);
			}
		}else{
			fprintf(req->ci->fout,"%s</td><td>File</td>",pdir[i]->d_name);
		}
		
		strftime(timebuff, 20, "%d-%m-%Y %H:%M:%S", localtime(&stbuf.st_mtime));
		fprintf(req->ci->fout,"<td>%s</td>",timebuff);
		fprintf(req->ci->fout,"<td>%d</td></tr>",(int)stbuf.st_size);
		i++;
			
	}
	
	

	fprintf(req->ci->fout,"</tbody></table>\n <p> %s , Copyright &copy; Polytech-Nice 2013</p></div>\n</body>\n</html>",SERVER_NAME);
	return 1;
}

/*
 * a structure representing a element in handler queue
 */
typedef struct _handler_element{
	uri_handler_t element; //  the element content
	struct _handler_element* tail;  // the next element in the queue

}handler_element;

handler_element* root_element = NULL; // the root element, the first element to be called




/*
 * Adds a new element in the queue
 *
 * element the new handler to add to the queue
 */
void add_element(uri_handler_t element){

	if(root_element == NULL){ // if the first added element (the tail of the list).
		// we allocate memory for our element
		root_element = (handler_element*) malloc(sizeof(handler_element));
		if(root_element == NULL){
			trace("[%s:Handler] Allocation Error !! Unable to allocate memory for the queue.\n",SERVER_NAME);
			exit(EXIT_FAILURE);
		}
		root_element->tail = NULL;
		root_element->element = handler_404Error; 
		// TODO : Check for memory leaks
		add_element(handler_FileExplorer);
		add_element(element);
	}else{ // if a new Element but not the last one
		// we allocate memory for our element
		handler_element* newElement  = (handler_element*)malloc(sizeof(handler_element));
		if(newElement == NULL){
			trace("[%s:Handler] Allocation Error !! Unable to allocate memory for the queue.\n",SERVER_NAME);
			exit(EXIT_FAILURE);
		}

		// we replace make the new element the root of our structure
		newElement->tail = root_element;
		newElement->element = element;
		root_element = newElement;
	}

}



/* Addes a new Handler (using a FIFO System).
 * 
 * uri_handler_t 	a function pointer to the handler to use
 */
void handler_uri_add(uri_handler_t hdlr){
	add_element(hdlr);
}

/* 
 * Calles the handlers, in FIFO style (last added one first)
 * if handler return 0 continue , if 1 stops
 */
void handler_build_response(struct http_request *req){
	handler_element* current = root_element;
	while(current != NULL && (*current->element)(req) == 0){
		current = current->tail;
	}
}

