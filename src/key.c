/*
    $Id: src/key.c,v 0.1 2005-05-08 20:51:00 sigterm Exp $
*/


#include "../include/herbivore.h"

int inchars(int into){
    int fd_chars;
    char l = into;
    
    for(fd_chars=0; fd_chars!=64; fd_chars++){
	if(chars6[fd_chars] == l) return fd_chars;
    }
    
    return 1;
}

int get_char(int into){
    int fd_chars;
    char l = into;

    for(fd_chars=0; fd_chars!=256; fd_chars++){
	if(chars8[fd_chars] == l) return fd_chars;
    }

    return 1;
}

