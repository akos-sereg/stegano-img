/*
    $Id: src/user.c,v 0.1 2005-05-08 20:57:00 sigterm Exp $
*/


#include "../include/herbivore.h"

void ascii_warn(void){
    printf("You are in normal ASCII mode (we are not using keytable)\n");
    printf("\n");
}

int check_keys(void){
    if(check_valid_file(CHARSTXT) &&
	check_valid_file(CHARSTXT8)) return 1;
    else {
	printf("Error while opening keytable\n");
	printf("Keytables:\n\t%s\n\t%s\n", CHARSTXT8, CHARSTXT);
        return 0;
    }

}

int check_valid_file(char *file)
{        
    FILE *test;

    if(strlen(file) == 0) return 0;
        
    test = fopen(file, "rb");
    if(test) 
    {
	fclose(test);
	return 1;
    } else return 0;    
}