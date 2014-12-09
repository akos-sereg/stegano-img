/*
    $Id: src/herbivore.c,v 0.1 2005-05-08 19:56:02 sigterm Exp $

*/

#include "../include/herbivore.h"

int main(int argc, char **argv)
{
    int c;
            
    sprintf(herbivore, "%s", argv[0]);        
    if(argc < 2)
    {    
	help();
	return 0;
    }
    
    herb_init();
    
    while((c = getopt(argc, argv, "d:e:t:o:hs")) != EOF)
    {
	switch(c)
	{
	    case 'd':
		sprintf(herbfiles.decode, "%s", optarg);
		usr_defs.decode = 1;
		break;
	    case 'e':
		sprintf(herbfiles.encode, "%s", optarg);
		usr_defs.encode = 1;
		break;
	    case 'o':
		sprintf(herbfiles.outfile, "%s", optarg);
		usr_defs.outfile = 1;
		break;
	    case 't':
		sprintf(herbfiles.text, "%s", optarg);	
		usr_defs.text = 1;
		break;
	    case 's':
		usr_defs.stdout = 1;
		break;
	}
    }    
    hcore();    
    return 1;
}
