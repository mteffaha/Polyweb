#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MEM_LINE_SIZE   64

char *mimetype_find(char *path);
char *read_str(FILE **stream, char *str);
void mimetype_new_rule(char* rule);
char type[10000]="html text/html jpg image/jpeg jpeg image/jpeg gif image/gif pdf application/pdf ";
void mimetype_new_rule(char* rule);

void mimetype_new_rule(char* rule)
{
	strcat(type, rule);
}


char *mimetype_find(char *path)
{
   
    char *point_pos = path;
    char *file_name_tail = &path[strlen(path) - 1];
   
    while (*point_pos != '.' && point_pos != file_name_tail)
        point_pos++;
        
   
    if ((*point_pos == '.') && (point_pos != path) && (point_pos != file_name_tail))
    {
        char ext_name[10];
       
        strcpy(ext_name, (point_pos + 1));
        if(!strstr(type,ext_name))
        return "text/plain\n";
        else
        {
			char *c;
			c= strstr(type, ext_name);
			char *end=c;
			while(*end!=' ')
			{
				end++;
				c++;
			}
			c++;
			end++;
			while(*end!=' ')
			{
				end++;
			}
		char *d=strtok(c," ");
		return d;
		}
	}
       
    else   
    return "text/plain\n";
}
