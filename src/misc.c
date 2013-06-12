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
#include <unistd.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "misc.h"
#include "polyweb.h"

typedef void (*initModule)();


/*
 * Global variables definition (details in misc.h)
 */
char* document_root = NULL; // the root document for the server 
int   listen_port;   // the port number to use
int   debug_mode;    // the debug mode (0 : no debug , 1 : all errors displayed)
char* module_dir = NULL;    // the module directory


/*
 * Safely copy a string from src to dest, checks for errors and does the necessary allocations
 * dest  	the destination to copy to
 * src	 	the source to copy from
 */
void safeCopyString(char** dest,const char* src){
	if(dest == NULL){
		trace("[%s:misc] unvalid string pointer passed to safeCopyString\n",SERVER_NAME);
	exit(EXIT_FAILURE);
	}
	if(*dest != NULL){
		free(dest);
	}

	*dest =(char*)calloc(sizeof(char),strlen(src)+1);
	if(dest == NULL){
		trace("[%s:misc] unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
	memcpy(*dest,src,strlen(src));
	if(dest == NULL){
		trace("[%s:misc] unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
}


/*
 * Parse a string containing a number and sets the number with the corresponding string (if a valid base10 number)
 * val	 	the string containing the number
 * number 	the number to store the parsed number in
 */
void parseNumber(const char* val,int* number){
	
	// Allocate memory where the bad characters will be stored
	char* endptr = (char*)calloc(sizeof(char),strlen(val)+1);
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

	safeCopyString(&document_root,val);
}


/*
 * sets the port number from a string containing the actual number
 *
 * val		a string containing a base10 number representing the port
 */
void set_listen_port(const char *val){
	parseNumber(val,&listen_port);
}

/*
 * Parses the debug mode (Number) from a sting containing the actual number
 * 
 * val		a string containing a base10 number representing the debug mode
 */
void set_debug_mode(const char *val){
	parseNumber(val,&debug_mode);
}


/*
 * Sets the directory containing the modules that will be loaded
 *
 * name			the name of directory to use (full path will be document_root/name)
 */
void set_module_directory(const char *name){
	safeCopyString(&module_dir,name);
}

/*
 * loads the module with the given name from the module directory
 *
 * name			the name of the module to be loaded
 */
void module_load(const char *name){
	char* fullModulePath = NULL; 
	void* handle = NULL;
	initModule miFcn;
	// Checks wether module_dir was set or not
	if(module_dir == NULL){
		safeCopyString(&module_dir,".");
	}
	// then constructs the full path to the module
	if(name != NULL){
	fullModulePath  = calloc(sizeof(char),(strlen(name)+strlen(module_dir)+6));
	}else{
		return;
	}
	if(fullModulePath == NULL){
		trace("[%s:misc] Unable to allocate memory\n",SERVER_NAME);
		exit(EXIT_FAILURE);
	}
	memset(fullModulePath,0,strlen(name)+strlen(module_dir)+5);
	strcpy(fullModulePath,module_dir);
	strcpy(fullModulePath+strlen(module_dir),"/");
	strcpy(fullModulePath+strlen(module_dir)+1,name);
	strcpy(fullModulePath+strlen(module_dir)+1+strlen(name),".so");
	// Checks that the module exists and is readable
	if(access(fullModulePath,F_OK|R_OK) != 0){
		trace("[%s:misc] Module : %s is either non existing or not readable\n",SERVER_NAME,name);
		return;
	}

	// loads the module
	handle= dlopen(fullModulePath,  RTLD_LAZY | RTLD_GLOBAL);
	if(handle == NULL){
		trace("[%s:misc] Unable to load module\n",SERVER_NAME);
		return ;
	}

	// We locate the init_module function
	miFcn = (initModule)dlsym(handle,"init_module");
	if(miFcn == NULL){
		trace("[%s:misc] Module : %s does not contain an init_module function\n",SERVER_NAME,name);
	}

	// We call the init_module function
	(*miFcn)();
}

int is_dir(const char *dir){
	if(dir == NULL)
		return 0;
	struct stat statbuf;
   	stat(dir, &statbuf);
   	return S_ISDIR(statbuf.st_mode);
}


void make_path(char *res, const char *dir, const char *file){
	res = (char*)calloc(sizeof(char),(strlen(dir)+strlen(file)+2));
	strcpy(res,dir);
	strcpy(res+strlen(dir),"/");
	strcpy(res+strlen(dir)+1,file);
}
