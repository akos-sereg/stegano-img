/*
    $Id: src/std_encode.c,v 0.2 2005-05-08 20:56:00 sigterm Exp $
*/

#include "../include/herbivore.h"


int setty, dec, perc, byema;

int hstdenc(char *codfile, char *keyfile, char *outfile, int chan)
{
    FILE *code, *key, *out;
    FILE *tmp;
    char betu, header[HDRLEN], hdrfile[256];
    int size, setx, n[8], d, dot, colors, hist_red=0, 
	hist_green=0, hist_blue=0, hist_alpha=0, bit_mode, row_cntr = 0, 
	maradek, i_place, hdrfile_i, datawrite[4];
    float sety, percent, pre_percent;
    gdImagePtr im;
    
    bit_mode = 8;    
    rgb = chan;
    pre_percent = 0;
    
    rgb_use.red = 0;
    rgb_use.green = 0;
    rgb_use.blue = 0;
    rgb_use.alpha = 0;
    
    fresh_rgbdb(chan);
    
    datawrite[0] = 0;
    datawrite[1] = 0;
    datawrite[2] = 0;
    datawrite[3] = 0;
        
    code = fopen(codfile, "rb");
    im = gdImageCreateFromPng(code);
    fclose(code);       

    
    end_x = gdImageSX(im);
    end_y = gdImageSY(im);
    
    printf("Image size: %dx%d\n", end_x, end_y);
    
    byema = end_x * end_y;
    
    byema = (int) floor(byema / 8);
    
    printf("Capacity/channel: %d bytes\n", byema);


    key = fopen(keyfile, "rb");
    
    rewind(key);
    size=0;
    while(!feof(key)){
	betu = fgetc(key);
	size++;
    }
    size--;
    printf("File length(%s): %d byte(s) ... checking: ", keyfile, size-1);
    
    if(SLIDE)
    {
	if((size+HDRLEN+5) > (byema*4))
	{
	    printf("Not enough (max: %d*4 = %d/%d/)\n", byema, byema*4, size+HDRLEN-1);
	    return 0;
	} else 
	{
	    printf("OK (enough)\n");
	}
	
    } else 
    {
	printf("Operation not supported.\nRecompile herbivore with #define SLIDE=1\n");
	return 0;
    }
    
    if(SLIDE) 
    {
	if(rgb == 1) hist_red = 1;
	if(rgb == 2) hist_green = 1;
	if(rgb == 3) hist_blue = 1;	
	if(rgb == 4) hist_alpha = 1;	
    }
    
    
    sprintf(hdrfile, "%s", keyfile);
    if(strlen(hdrfile) > 32) hdrfile[32]='\0';
    else if(strlen(hdrfile) == 32) { }
    else
    {
	hdrfile_i = strlen(hdrfile);
	while(hdrfile_i != 32)
	{
	    hdrfile_i++;
	    sprintf(hdrfile, "%s ", hdrfile);
	}
    }
    sprintf(header, "%s%8d", hdrfile, size);
    printf("Header: '%s' char(%d)\n", header, strlen(header));
    
    fprintf(stdout, "%s => %s (Out: %s)\n", keyfile, codfile, outfile);
    for(i=0; i!=size+strlen(header); i++)
    {
	if(i < strlen(header))
	{
	    betu = header[i];
	} else
	{
	    rewind(key);
	    fseek(key, i-strlen(header), 1);
	    betu = fgetc(key);
	}
	
	if(SLIDE) {
	    if(i>=(byema*3))
	    {
		rgb=4;
		i_place = i-(3*byema);
		datawrite[3]++;
	    } else if(i>=(byema*2))
	    {
		rgb=3;
		i_place = i-(2*byema);
		datawrite[2]++;
	    } else if(i>=byema)
	    {
		rgb=2;
		i_place = i-byema;
		datawrite[1]++;
	    } else
	    {
		rgb=1;
		i_place = i;
		datawrite[0]++;
	    }
	    
	    
	} else 
	{
	    rgb=1;
	    i_place = i;
	}
	
	if(bit_mode == 6) betu = char_transform(betu);
	
	if(bit_mode == 6) dec = inchars(betu);
	if(bit_mode == 8)
	{
	    if(!USEASCII)  dec=get_char(betu);
	    else dec = betu;
	}

	percent = i * 100;
	percent = percent / size;

	if(percent > (pre_percent+10))
	{
	    fprintf(stdout, "\t%d/%d bytes, %f%% done, channel: ", i, size-1+strlen(header), percent);
	    switch(rgb)
	    {
		case 1: printf("red"); break;
		case 2: printf("green"); break;
		case 3: printf("blue"); break;	    
		case 4: printf("alpha"); break;	    
	    }
	    printf("\n");
	    pre_percent = percent;
	}

	maradek = dec;
	
	if(bit_mode == 8)
	{
	    if(maradek > 127){ n[0] = 1; maradek = maradek % 128; } else n[0] = 0;
	    if(maradek > 63){ n[1] = 1; maradek = maradek % 64; } else n[1] = 0;
	    if(maradek > 31){ n[2] = 1; maradek = maradek % 32; } else n[2] = 0;
	    if(maradek > 15){ n[3] = 1; maradek = maradek % 16; } else n[3] = 0;
	    if(maradek > 7){ n[4] = 1; maradek = maradek % 8; } else n[4] = 0;
	    if(maradek > 3){ n[5] = 1; maradek = maradek % 4; } else n[5] = 0;
	    if(maradek > 1){ n[6] = 1; maradek = maradek % 2; } else n[6] = 0;
	    if(maradek > 0){ n[7] = 1; } else n[7] = 0;
	}

	if(bit_mode == 6)
	{
	    if(maradek > 31){ n[0] = 1; maradek = maradek % 32; } else n[0] = 0;
	    if(maradek > 15){ n[1] = 1; maradek = maradek % 16; } else n[1] = 0;
	    if(maradek > 7){ n[2] = 1; maradek = maradek % 8; } else n[2] = 0;
	    if(maradek > 3){ n[3] = 1; maradek = maradek % 4; } else n[3] = 0;
	    if(maradek > 1){ n[4] = 1; maradek = maradek % 2; } else n[4] = 0;
	    if(maradek > 0){ n[5] = 1; } else n[5] = 0;
	}
	
	for(k=0; k!=bit_mode; k++)
	{

	    d = i_place * bit_mode;
	    d = d + k;
	    sety = d / end_x;
	    setx = d % end_x;
	    
	    for(j=0; j!=end_y; j++)
	    {
	        if((int)sety == j){ setty = j; }
	    }
		
		
	    dot = gdImageGetPixel(im, setx, setty);

	    grnext = gdImageGreen(im, dot);
	    renext = gdImageRed(im, dot);
	    blnext = gdImageBlue(im, dot);
	    alnext = gdImageAlpha(im, dot);
		
	    if(n[k] == 1)
	    {
	        if(rgb == 1)
		{
	    	    if(renext == 0) renext++;
		    else if(renext % 2 == 0) renext--;
		} else if(rgb == 2) 
		{
		    if(grnext == 0) grnext++;
		    else if(grnext % 2 == 0) grnext--;
		} else if(rgb == 3) 
		{
		    if(blnext == 0) blnext++;
		    else if(blnext % 2 == 0) blnext--;
		} else if(rgb == 4) 
		{
		    if(alnext == 0) alnext++;
		    else if(alnext % 2 == 0) alnext--;
		}
		    
	    } else 
	    {
	        if(rgb == 1){ if(renext % 2 != 0) renext--; }
	        else if(rgb == 2){ if(grnext % 2 != 0) grnext--; }
	        else if(rgb == 3){ if(blnext % 2 != 0) blnext--; }
		else if(rgb == 4){ if(alnext % 2 != 0) alnext--; }
	    }
		
    	    colors = gdImageColorResolveAlpha(im, renext, grnext, blnext, alnext);		
	    gdImageSetPixel(im, setx, setty, colors);
	
	}
	    
    }
    
    fprintf(stdout, "\t%d/%d bytes, %f%% done\n", i, size-1+strlen(header), percent);
    printf("Save as %s...\n", outfile);
    
    out = fopen(outfile, "ab");
    if(strcmp(PTYPE, "jpeg") == 0) gdImageJpeg(im, out, RANGE);
    else gdImagePng(im, out);
    
    gdImageDestroy(im);
    fclose(key);
    fclose(out);
    
    percent = ((size - 1)*100) / byema;
    for(i=0; i!=300; i++)
    {
	if(percent == i){ perc = i; }
    }
    printf("Used channel(s):\n");
    if(rgb_use.red == 1){ printf("\t- red\n"); }
    if(rgb_use.green == 1){ printf("\t- green\n"); }
    if(rgb_use.blue == 1){ printf("\t- blue\n"); }
    if(rgb_use.blue == 1){ printf("\t- alpha\n"); }
    if(perc == 0){ perc = 1; }
    //printf("Use: %d%%\n", perc);
    printf("Red  : %d/%d\n", datawrite[0], byema);
    printf("Green: %d/%d\n", datawrite[1], byema);
    printf("Blue : %d/%d\n", datawrite[2], byema);
    printf("Alpha: %d/%d\n", datawrite[3], byema);
    
    if(USEASCII) ascii_warn();
    
    return 1;
}


void fresh_rgbdb(int chan)
{
    switch(chan)
    {
	case 1:
	    rgb_use.red = 1;
	    break;
	case 2:
	    rgb_use.green = 1;
	    break;
	case 3:
	    rgb_use.blue = 1;
	    break;
	case 4:
	    rgb_use.alpha = 1;
	    break;
    }
}
