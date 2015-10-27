/*
 * Fonction assert et fonctions liées
 */

#include "com/types.h"
#include "com/command.h" // inclut interpreteur et mémoire
#include "com/notify.h" // Pour les messages de contrôle, inclut stdlib et stdio
#include <string.h> // pour strcmp notamment



int assert(interpreteur inter, Memory *mem)
{	
	char* what= NULL;
	char* va = NULL;
	char *value = NULL;
	unsigned int val = 0; // value en unsigned int
	char usage[] = "Usage : assert reg <registre> <valeur>\n\tassert word <adresse> <valeur>\n\tassert byte <adresse> <valeur>\n";

	what = get_next_token (inter); // récupère reg, word ou byte
	va = get_next_token(inter); // registre ou adresse
	value = get_next_token(inter); // valeur

	if(what == NULL
	|| va == NULL
	|| value == NULL 
	|| get_next_token(inter) != NULL) // pas assez ou trop de tokens
	{
		WARNING_MSG("Problem with tokens");
		printf("%s", usage);
		return 1;
	}

	/* On commence par tester la valeur car elle est commune au 3 commandes
	*/

	if(is_hexa(value) != 0
	&& is_dec(value) != 0
	&& is_oct(value) != 0) // La valeur n'est pas correcte
	{
		WARNING_MSG("Value must be decimal, hexadecimal or octodecimal");
		return 2;
	}

	val = strtoul(value, NULL, 0);

	if(strcmp(what, "reg") == 0)
	{
		return assert_reg(va, val, mem->reg);
	}
	else if(strcmp(what, "word") == 0)
	{
		return assert_wrd(strtoul(va, NULL, 0), val, mem);
	}
	else if(strcmp(what, "byte") == 0)
	{
		return assert_bte(strtoul(va, NULL, 0), val, mem);
	}
	else {
		WARNING_MSG("Bad value for second token");
		printf("%s", usage);
		return 3;
	}
}

int assert_reg(char *name, word val, Registre reg[NB_REG])
{
	word val_reg;

	if(get_reg(name, &val_reg, reg) != 0)
	{
    	WARNING_MSG ("No '%s' registre\n", name);
    	return 2;
    }

    if(val_reg == val)
    {
    	INFO_MSG("True");
    	return 0;
    }
    else {
    	INFO_MSG("False");
    	return 1;
    }
}

int assert_wrd(vaddr32 va, word val, Memory *mem)
{
    printf("\n0x%08x \n", get_word(va, mem));

	if(get_word(va, mem) == val)
	{
		INFO_MSG("True");
		return 0;
	}
    else {
    	INFO_MSG("False");
    	return 1;
    }
}

int assert_bte(vaddr32 va, unsigned int val, Memory *mem)
{
	if(get_byte(va, mem) == val)
    {
    	INFO_MSG("True");
    	return 0;
    }
    else {
    	INFO_MSG("False");
    	return 1;
    }
}

