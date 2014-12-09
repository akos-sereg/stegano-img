/*
    $Id: src/hcore.c,v 0.1 2005-05-08 20:51:28 sigterm Exp $
*/

#include "../include/herbivore.h"

int hcore()
{
    int chan;
    if(usr_defs.text && (!usr_defs.encode))
    {
	help();
	return 0;
    }
    
    if(strlen(channel))
    {
	if(strcmp(channel, "red") == 0) chan = 1;
	else if(strcmp(channel, "green") == 0) chan = 2;
	else if(strcmp(channel, "blue") == 0) chan = 3;
	else if(strcmp(channel, "alpha") == 0) chan = 4;
	else 
	{
	    printf("%s: Channel '%s' does not exists\n", herbivore, channel);
	    help();
	    return 0;
	}
    } else chan = DEFAULT_CHANNEL;
    
    if(strlen(herbfiles.encode) > 0)
    {
	if(strlen(herbfiles.text) > 0)
	{
	    if(check_valid_file(herbfiles.encode) &&
		check_valid_file(herbfiles.text))
	    {
		if(!strlen(herbfiles.outfile)) sprintf(herbfiles.outfile, "%s", houtname(herbfiles.encode, ".png", "_"));
		if(load_keys()) hstdenc(herbfiles.encode, herbfiles.text, herbfiles.outfile, chan);
		
	    } else
	    {
		printf("%s: File not found/not readable: ", herbivore);
		if(!check_valid_file(herbfiles.encode)) printf("%s ", herbfiles.encode);
		if(!check_valid_file(herbfiles.text)) printf("%s ", herbfiles.text);
		printf("\n");
		return 0;
	    }
	
	} else
	{
	    printf("%s: Missing args -t <text>\n", herbivore);
	    return 0;
	}
    } else 
    if(strlen(herbfiles.decode) > 0)
    {
	if(check_valid_file(herbfiles.decode))
	{
	    if(!strlen(herbfiles.outfile)) sprintf(herbfiles.outfile, "_%s", herbfiles.decode);	
	    if(load_keys()) hstddec(herbfiles.decode, herbfiles.outfile, chan);
	} else 
	{
	    printf("%s: File not found/not readable: %s\n", herbivore, herbfiles.decode);    
	    return 0;
	}
    }
}


void herb_init(void)
{
    usr_defs.encode = 0;
    usr_defs.decode = 0;
    usr_defs.outfile = 0;
    usr_defs.text = 0;    
    usr_defs.channel = 0;
    usr_defs.huffman = 0;
    usr_defs.stdout = 0;
}
