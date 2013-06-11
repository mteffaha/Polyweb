#include "config.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

extern struct optio_action options[];

// Ajouter les nouvelles options contenues dans le tableau "actions".
// Ces actions s'ajoutent aux actions déjà connues du système.
void config_register(struct option_action *actions){
	//ajouter dans options les nouvelles options (cf main) 
	//parcourt du tableau options jusqu'a NULL
	int cpt=0;
	while(options[cpt].command != NULL){
		cpt++;
	}
	//ici options[cpt].command = NULL
	//c'est donc ici qu'il faut rajouter nos actions
	int i=0
	//parcourt des actions a ajouter
	while(!(actions[i].command == NULL)){
		options[cpt].command = actions[i].command;
		options[cpt].func = actions[i].func;

		//incrémentation des compteurs
		i++;
		cpt++;

	}

	//rajout de NULL, NULL a la fin du tableau options
	cpt++;
	options[cpt].command = NULL;
	options[cpt].func = NULL;



}



// Lecture du fichier de configuration du serveur. La liste d'actions
// passée en paramètre permet de définir complètement le traitement
// associé à chacune des options du serveur. La syntaxe d'un fichier
// d'options est simple:
//    - les commentaires commencent par un "#" et se poursuivent
//      jusqu'à la fin de la ligne
//    - Une option de configuration est formée de 2 "mots":
//         - le nom de l'option (placé en début de ligne)
//         - la valeur de l'option (texte qui suit le nom de l'option).
// Exemple de ligne du fichier d'options
//
// opt       abc def gh         # une exemple
//
// Ici le nome de l'option est 'opt' et sa valeur est 'abc def gh'.
// Noter que les espaces avant et après la valeur de l'option ne font
// pas partie de la valeur de l'option
void config_read_file(const char* pathname, struct option_action *actions){
	char *fichier_configuration;
	if(pathname == NULL){
		fichier_configuration = DFLT_CONFIG_FILE;
	}else{
		fichier_configuration = pathname;
	}
	char buff[CONFIG_MAX_LENGTH];
	int fd,n;

	//ouverture du fichier de configuration.
  	if ((fd=open(fichier_configuration, O_RDONLY)) == -1){
    		perror("Ouverture fichier de configuration.");
    		exit(1);
  	}
	while ((n = read(fd, buff, CONFIG_MAX_LENGTH)) > 0) {
		if (n < 0) {
      			perror("Lecture dans le fichier de config.");
      			exit(1);
    		}
		//on separe la ligne en 2 (avant et apres commentaire
		char *ligne_sans_commentaire = strtok(buff, "#");


		//1er appel de strtok -> commande, tous les autres = arguments
		//tableau de taille nombre d'option +1 pour la commande        
        	char *nom_commande;
		char *arguments;
		char *temp;
		int continuer=0;
		nom_commande = strtok(ligne_sans_commentaire, " ");
		
		//recuperation des arguments dans la chaine arguments.
        	while(continuer == 0){
			if((temp = strcat(strtok(NULL, " ")," "))==NULL){
				arguments = strcat(arguments,temp);
				continuer=1;
			}
		}

		//parcourt du tableau d'options
		int i=0;
		int trouve=1;
		while(!(actions[i].command == NULL) && (trouve==1)){
			if(strcmp(actions[i].command, nom_commande) == 0){
				trouve=0;
				(*actions[i].func)(arguments);
			}	
			i++;
		}
	}
	close(fd);
}
