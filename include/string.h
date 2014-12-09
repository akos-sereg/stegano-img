#ifndef _string_h_included_
#define _string_h_included_

char retval[256];
char retval_hon[256];

extern char *sub_string(char *str, int pos_a, int pos_b);
extern int load_keys(void);
extern char *houtname(char *fname, char *pattern, char *insert);

#endif
