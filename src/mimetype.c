#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct mimetype 
{
	char	*extension;
	char	*mime;
	struct	mimetype *next;
}mimetype_list;

mimetype_list	*list = NULL;

void mimetype_new_rule(char* rule)
{
	mimetype_list *new;
	new = malloc(sizeof(*new));
	if (new == NULL)
	{
		perror("malloc");
        exit(1);
	}
    if (strstr(rule, " ") == NULL)
    return ;
    new->extension = strtok(strdup(rule), " ");
    new->mime = strtok(NULL, " ");
    new->next = list;
    list = new;
}


char *mimetype_find(char *path)
{
	char *extension;
    int n = strlen(path) - 1;
    mimetype_list *head;
	while (path[n] != '.' && n >= 0)
		n--;

    if (n < 0)
		return "text/plain";
    n++;
	
    extension = malloc((strlen(path) - n + 1) * sizeof(*extension));
    strncpy(extension, &(path[n]), strlen(path) - n);
    head = list;
    while (head != NULL)
    {
		if (strcmp(head->extension, extension) == 0)
			return head->mime;
		head = head->next;
    }
    return "text/plain";
}

int main(){
	mimetype_new_rule("jpg image/jpeg");
	mimetype_new_rule("pdf application/jpg");
	printf("%s",mimetype_find("a.jpg"));
}
