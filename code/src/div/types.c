/* Fonctions relatives aux types */

#include "common/types.h"


enum {HEXA,OCT,DEC,UNKNOWN};

int get_type(char* chaine) {

    DEBUG_MSG("get_type entered");

    if (is_hexa(chaine))
        return HEXA;
    else if (is_oct (chaine))
	return OCT;
    else if (is_dec (chaine))
	return DEC;	
    else return UNKNOWN;
}




int is_hexa(char* chaine) {
    DEBUG_MSG("is_hexa entered");

    char* p;
    if (chaine==NULL 
        || strlen(chaine) <= 2 
        || chaine[0]!='0'
        || chaine[1]!='x')
        return 1;

    return 0;
}

int is_oct(char* chaine) {
    DEBUG_MSG("is_oct entered");

    int i;
    long l;
    char* p;
    if (chaine!=NULL && strlen(chaine)> 1 && chaine[0]=='0' && sscanf(chaine,"%x",&i)==1){
	 l = strtol (chaine, &p , 8);
	 if (l!=0) return 1;
	 else return 0;
}
    else return 0;
}

int is_dec (char* chaine){
    DEBUG_MSG("is_dec entered");

    int i;
    long l;
    char* p;
    if (chaine!=NULL && chaine[0] != '0' && sscanf(chaine,"%x",&i)==1){
	 l = strtol (chaine, &p , 10);
	 if (l!=0) return 1;
	 else return 0;
}
    else return 0;
}


