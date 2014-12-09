/*
    $Id: src/help.c,v 0.1 2005-05-08 20:52:21 sigterm Exp $
*/

#include "../include/herbivore.h"

void help(void)
{
    printf("Usage: %s [OPTION]...\n", herbivore);
    printf("Options:\n");
    printf("	-o <png file>		Output to <png file>\n");
    printf("	-d <png file>		Decode from <png file>\n");
    printf("	-e <png file>		Encode to <png file>\n");
    printf("	-t <txt file>		Text file to be coded into PNG\n");
    printf("	-s 			Print result to stdout\n\n");
    
    printf("Examples:\n");
    printf("  $ ./herbivore -e image.png -t textfile.txt -o encoded-image.png\n");
    printf("  $ ./herbivore -d encoded-image.png\n");
}
