#ifndef _MYMALLOC_H
#define _MYMALLOC_H

#include <stdlib.h>
#include <stdio.h>

// define the malloc and free functions to be replaced by our own
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)



#endif
