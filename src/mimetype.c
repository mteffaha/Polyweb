#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <limits.h>

typedef struct Mimetype{
	char *extension;
	char *mime;
	struct Mimetype *next;
}Mimetype;

Mimetype *phead = NULL;

void mimetype_new_rule(char* rule){

	char extension_tmp[PATH_MAX];
	strcpy(extension_tmp, rule);

	char *extension = strtok(extension_tmp, " \t");
	char *mime  = strtok(NULL, " \t");
	Mimetype *tmp;

	for(tmp = phead;tmp != NULL; tmp = tmp->next){
		if(strncmp(tmp->extension, extension, strlen(extension)) == 0){exit(0);}
	}
 
	Mimetype *pnew = malloc(sizeof(Mimetype));
	pnew->extension = malloc((strlen(extension) + 1)*sizeof(char));
	pnew->mime = malloc((strlen(mime) + 1)*sizeof(char));
	strcpy(pnew->extension, extension);
	strcpy(pnew->mime, mime);
	pnew->next = phead;
	phead = pnew;
}

char *mimetype_find(const char *path){

	char *extensionBis = rindex(path, '.');
	char path_tmp[PATH_MAX];
	strcpy(path_tmp, extensionBis+1);
	char *extension = strtok(path_tmp, " \t");
	int length = strlen(extension);
	Mimetype *tmp;

	for(tmp = phead; tmp != NULL ; tmp=tmp->next){
		if (strncmp(extension, tmp->extension, length) == 0){
			return tmp->mime;
		}
	}
 
	return "text/plain";
}










