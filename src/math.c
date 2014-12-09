/*
    $Id: src/math.c,v 0.1 2005-05-08 20:55:00 sigterm Exp $    
*/


#include "../include/herbivore.h"

int bit_to_dec(int num, int bit_mode){
    if(bit_mode == 6){
	if(num == 0) return 32;
	if(num == 1) return 16;
	if(num == 2) return 8;
	if(num == 3) return 4;
	if(num == 4) return 2;
	if(num == 5) return 1;
    }
    if(bit_mode == 8){
	if(num == 0) return 128;
	if(num == 1) return 64;
	if(num == 2) return 32;
	if(num == 3) return 16;
	if(num == 4) return 8;
	if(num == 5) return 4;
	if(num == 6) return 2;
        if(num == 7) return 1;
    }
    return 0;
}


int convert4(int a, int b){

    if(a == 1){ 
	if(b == 1) return 3;
	else return 2;
	
    } else {
	if(b == 1) return 1;
	else return 0;
    }

    return 0;
}
