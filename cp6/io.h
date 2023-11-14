#ifndef _io_h_
#define _io_h_

#include "computer.h"
#include <string.h>

int  computerReadTxt(Computer *s, FILE *in);
int  computerReadBin(Computer *s, FILE *in);
void computerWriteBin(Computer *s, FILE *out);
void computerPrint(Computer *s);

#endif
