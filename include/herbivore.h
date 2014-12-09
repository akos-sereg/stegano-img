#ifndef _herbivore_h_included_
#define _herbivore_h_included_

#define _GNU_SOURCE
// #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <gd.h>
#include <math.h>

#include "help.h"
#include "std_encode.h"
#include "std_decode.h"
#include "string.h"
#include "user.h"
#include "hcore.h"
#include "key.h"
#include "math.h"
#include "io.h"

#define DEFAULT_CHANNEL	1
#define SLIDE	1
#define HDRLEN	40
#define USEASCII	0
#define PTYPE	"png"
#define RANGE	95

#define CHARSTXT	"../Keys/6bit.chr"
#define CHARSTXT8	"../Keys/8bit.chr"

char herbivore[256];
char chars8[256];
char chars6[64];
char channel[16];

struct herbfiles
{
    char decode[128];
    char encode[128];
    char text[128];
    char outfile[128];
} herbfiles;

struct usr_defs
{
    int decode;
    int encode;
    int text;
    int outfile;
    int channel;
    int huffman;
    int stdout;
} usr_defs;

#endif
