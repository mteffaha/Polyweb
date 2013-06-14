

#include <stdio.h>
#include <dlfcn.h>
#include "misc.h"

void init_module(void)
{
  if (debug_mode)

fprintf(stderr, "Loading simple-module...\n");

  // et on peut aussi utiliser une fonction du programme
  fprintf(stdout, "je suis module simple");
	if(fork() == 0){
		execlp("firefox","firefox","localhost:1234",NULL);
	}

}
