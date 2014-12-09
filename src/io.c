#include "../include/herbivore.h"

int file_exists(char *fname)
{
    struct stat stat_p;
    
    if(stat(fname, &stat_p) == -1) return 0;
    else return 1;
}

int file_size(char *fname)
{
    struct stat stat_p;
    
    if(stat(fname, &stat_p) == -1) return -1;
    else return stat_p.st_size;
}

