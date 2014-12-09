#ifndef _std_encode_h_included_
#define _std_encode_h_included_

#define TMPFILE	"/tmp/herbivore-cipher"

int renext, grnext, alnext, blnext, i, j, k, end_x, end_y, rgb;

struct rgb_use 
{
    int red;
    int green;
    int blue;
    int alpha;
} rgb_use;

extern int hstdenc(char *input_png_file, 
		    char *input_text_file, 
		    char *output_png_file, 
		    int chan);
extern void fresh_rgbdb(int chan);

#endif
