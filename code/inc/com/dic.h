
#ifndef  DIC_H
#define DIC_H

#include <stdio.h>
#include "com/types.h" // word et Strlist

#define TAILLE_MAX 1000

#define NB_INS_32 2
#define NB_INS_16 0

/*
 * Explications & exemples : cf lib/instructions.md
 *
 */

 int to_strlist(char *chaine, Strlist *liste); // fonction ultra sécurisée !

// Ins_disasmd = instruction désassemblée, les Strlist contiennent les valeurs extraites du (demi-)mot lu

typedef struct
{
	Strlist commande; // commande (0) et encoding (1)
	Strlist names; // inside IT (0) et outisde IT (1)
	Strlist opcode; // mask (0), opcode (1)

	// Paramètres :

	Strlist reg;
	Strlist imm;
	Strlist ext;

} Instruction, Ins_disasmd;

void init_ins(Instruction *ins);
void del_ins(Instruction *ins);

int load_ins(Instruction *ins, char *chaine);
void disp_ins(Instruction ins);

Instruction get_ins(word in, Instruction ins[], int taille);

void init_ins_d(Ins_disasmd *ins_d, Instruction *ins);

int parse_params(word mot, Strlist *strl, Strlist *strl_d);
int parse_param(word mot, char *plage, char **value_d);

int get_bounds(char* plage, int *start, int *end);

 typedef struct 
 {
 	Instruction ins32[NB_INS_32];
 	Instruction ins16[NB_INS_16];

 } Dic;


void init_dic(Dic *dic);
void del_dic(Dic *dic);

int disp_dic();

int load_dic(Dic *dic);

// fonctions relatives à Instruction nécessitant Dic (donc déclarée après dic)

Instruction get_ins32(word in, Dic *dic);
Instruction get_ins16(word in, Dic *dic);

int comp_instr(); // TODO


char* int_to_bin(unsigned int n, char taille);

char* bin_x_bin(char bin_1[], char bin_2[], int taille); // TODO

#endif
