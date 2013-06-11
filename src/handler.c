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

	fprintf(out,"%s 404 Not Found\n",req->protocol);
	fprintf(out,"Content-Type: text/html\n\n");
	fprintf(out,"<!doctype html>\n<head>\n\t<title>404 Not Found</title>\n</head>\n<body>\n<h1>404 Not Found</h1>\n<p>The requiest ressource was not found</p>\n</body>\n</html>\n");
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

