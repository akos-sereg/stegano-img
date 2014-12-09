/*
    $Id: src/string.c,v 0.1 2005-05-08 20:56:00 sigterm Exp $
*/

#include "../include/herbivore.h"

char *sub_string(char *income, int stfrom, int stto){
    int stlen;
    
    retval[0] = '\0';
    
    for(stlen=stfrom; stlen!=stto; stlen++){
	retval[stlen-stfrom] = income[stlen];
    }
    
    retval[stlen-stfrom] = '\0';
    return retval;
}

int load_keys(void){
    FILE *fd;
    int i;
    
    if(check_keys() == 0) exit(1);
    fd = fopen(CHARSTXT8, "rb");
    chars8[0] = '\0';    
    for(i=0; i!=256; i++) sprintf(chars8, "%s%c", chars8, fgetc(fd));
    fclose(fd);
    
    fd = fopen(CHARSTXT, "rb");
    chars6[0] = '\0';    
    for(i=0; i!=64; i++) sprintf(chars6, "%s%c", chars6, fgetc(fd));
    
    return 1; 

}

char char_transform(char betu){	
    // A -> a; B -> b; E -> e  . . . stb.
	
    if(betu > 64 && betu < 89){
	betu = betu + 32;
    }
    if(betu == 'Á') betu = 'a';
    if(betu == 'É') betu = 'e';
    if(betu == 'Í') betu = 'i';
    if(betu == 'Ó') betu = 'o';
    if(betu == 'Ö') betu = 'o';
    if(betu == 'Õ') betu = 'o';
    if(betu == 'Ú') betu = 'u';
    if(betu == 'Ü') betu = 'u';
    if(betu == 'Û') betu = 'u';

    if(betu == 'á') betu = 'a';
    if(betu == 'é') betu = 'e';
    if(betu == 'í') betu = 'i';
    if(betu == 'ó') betu = 'o';
    if(betu == 'ö') betu = 'o';
    if(betu == 'õ') betu = 'o';
    if(betu == 'ú') betu = 'u';
    if(betu == 'ü') betu = 'u';
    if(betu == 'á') betu = 'u';
    
    return betu;
	
}

char *houtname(char *fname, char *pattern, char *insert)
{
    int i, len, notok, plen, ilen, pos;
    char buf[32];
    
    len = strlen(fname);
    plen = strlen(pattern);
    ilen = strlen(insert);
    if((len < 1) || 
	(plen < 1) || 
	(ilen < 1)) return NULL;
    
    notok = 1;
    i=0;
    while(notok && (i<len))
    {
	sprintf(buf, "%s", sub_string(fname, i, i+plen));
	if(strcmp(buf, pattern)==0) 
	{
	    notok = 0;	
	    pos = i;
	}
	i++;
    }
    
    if(!notok)
    {
	sprintf(retval_hon, "%s%s", sub_string(fname, 0, pos), insert);
	sprintf(retval_hon, "%s%s", retval_hon, sub_string(fname, pos, len));
	return retval_hon;	
    } else return "HERB_image.png";
    

} 


