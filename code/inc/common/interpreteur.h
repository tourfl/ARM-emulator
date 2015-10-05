#ifndef  INTERPRETEUR_H
#define INTERPRETEUR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* la librairie readline */
#include <readline/readline.h>
#include <readline/history.h>

/* macros de DEBUG_MSG fournies , etc */
#include "common/notify.h"

 /* commandes */

 #include "common/command.h"


/* prompt du mode shell interactif */
#define PROMPT_STRING "ARMShell> "

/* taille max pour nos chaines de char */
#define MAX_STR 1024


/*************************************************************\
Valeur de retour speciales pour la fonction
	int execute_cmd(interpreteur inter) ;
Toute autre valeur signifie qu'une erreur est survenue
 \*************************************************************/
#define CMD_OK_RETURN_VALUE 0
#define CMD_EXIT_RETURN_VALUE -1
#define CMD_UNKOWN_RETURN_VALUE -2


/* type de token (exemple) */
enum {HEXA,UNKNOWN};

/* mode d'interaction avec l'interpreteur (exemple)*/
typedef enum {INTERACTIF,SCRIPT,DEBUG_MODE} inter_mode;

/* structure passée en parametre qui contient la connaissance de l'état de
 * l'interpréteur
 */
typedef struct {
    inter_mode mode;
    char input[MAX_STR];
    char * from;
    char first_token;
} *interpreteur;

/*
 *	Fonctions
 */

 char* get_next_token(interpreteur inter);

 int get_type(char* chaine);

#endif
