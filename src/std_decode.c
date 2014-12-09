/*
    $Id: src/std_decode.c,v 0.2 2005-05-08 20:51:00 sigterm Exp $
    
*/

#include "../include/herbivore.h"

#define HEADER_MAXLEN	40

int hstddec(char *codfile, char *outfile, int chan)
{
    FILE *code, *foutf;
    FILE *tmp;
    int diff_area[2], header_stop, header_len, body_len;
    int current, channel=0, thisd;
    int db, len, c, hdri, hdrfleni, dpl;
    float f;
    char fout[200], header[HEADER_MAXLEN], hdrfile[40], hdrflen[8];
    gdImagePtr im;
    
    rgb = chan;
    sprintf(fout, "%s", outfile);

    code = fopen(codfile, "rb");
    if(!code)
    {
	return 0;
    }
    
    if(strcmp(PTYPE, "jpeg") == 0) im = gdImageCreateFromJpeg(code);    
    else im = gdImageCreateFromPng(code);
    
    fclose(code);
        
    end_x = gdImageSX(im);
    end_y = gdImageSY(im);
    dpl = end_x * end_y;
    dpl = (int) floor(dpl / 8);
    if(!usr_defs.stdout) printf("Source image: %s (%dx%d)\n", codfile, end_x, end_y);
    
    num=0;
    len = header_stop = 0;
    header[0] = '\0';

    /* R -> G -> B -> Alpha */
    for(channel=0; channel!=4; channel++)
    {    
	num=0;
	thisd=0;
	dec_value_char=0;
	for(i = 0; i != end_y; i++){ 
	    for(j=0; j != end_x; j++){ 	
		if((num == 8))
		{ 
		    num = 0;  

		    if(USEASCII) 
		    {
			c = dec_value_char;
		    } else 
		    {
			c = chars8[dec_value_char];
		    }

		    if(len <= (HDRLEN) && !header_stop)
		    {
			if(len == (HDRLEN))
			{
			    header_stop = 1;
			    header_len = len;
			    for(hdri=0; hdri!=32; hdri++) hdrfile[hdri] = header[hdri];
			    hdri=0;
			    while(hdrfile[hdri] != ' ')
			    {
				hdri++;
				if(hdri > 32) break;
			    }
			    hdrfile[hdri] = '\0';
			
			    if(!usr_defs.stdout) printf("HDR->FILE '%s'\n", hdrfile);
			
			    if(!usr_defs.stdout)
			    {
				if(file_exists(hdrfile)) sprintf(hdrfile, "%s_2", hdrfile);
				foutf = fopen(hdrfile, "wb");
				if(!foutf)
				{
				    printf("Unable to open file: %s\n", hdrfile);
				    return 0;
				}
			    } else foutf = stdout;
			
			
			    for(hdri=32; hdri!=41; hdri++) {
				hdrflen[hdri-32] = header[hdri];

			    }
			    hdrflen[8] = '\0';
			    if(!usr_defs.stdout) printf("HDR->FILE_LEN '%s' ==> %d bytes\n", hdrflen, atoi(hdrflen));
			    hdrfleni = atoi(hdrflen);
			
			
			
			    if(hdrfleni <= 0)
			    {
				printf("Incorrect header. Did you encode anything into this file: %s?\n", hdrflen);
				return 0;
			    }
			    body_len = hdrfleni;
			
			} 
			else sprintf(header, "%s%c", header, c);
		    } 
		    if(header_stop)
		    {
			fprintf(foutf, "%c", c);
		    }
		
		    if(header_stop && (len > (HDRLEN+body_len-2)))
		    {
			fclose(foutf);
			if(USEASCII) ascii_warn();
		    
			gdImageDestroy(im);    


			return 1;

		    }
		
		    dec_value_char = 0;
		    len++;
		}
	    
		current = gdImageGetPixel(im, j, i);
		if(channel == 0) coldif = gdImageRed(im, current);
		if(channel == 1) coldif = gdImageGreen(im, current);
		if(channel == 2) coldif = gdImageBlue(im, current);
		if(channel == 3) coldif = gdImageAlpha(im, current);
	    
		if(coldif % 2 == 1)
		{
		    value = bit_to_dec(num, 8);
		    dec_value_char = dec_value_char + value;
		}
		num++;
	    }
	}

	thisd++;
    }
    
    fclose(foutf);
    
    printf("\n\n");
    gdImageDestroy(im);    


    
    return 1;
}

