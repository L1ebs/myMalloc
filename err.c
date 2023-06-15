#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.c"


int main(int argc, char **argv)
{
    int x, *p;
    int test = argc > 1 ? atoi(argv[1]) : 0;
    
    switch (test) {
    default:
        puts("Missing or invalid test number");
        return EXIT_FAILURE;
    
    case 1:
        free(x);
        break;

    case 2:
        p = (int *) malloc(sizeof(int) * 10);
        free(p + 1);
        break;
    
    case 3:
        p = (int *) malloc(sizeof(int) * 10);
        free(p);
        free(p);
        break;
    case 4: // Attempt to free a null pointer
        int *r = NULL;
        free(r);
        break;
    case 5:
        /* Allocate memory for an array of 10 integers */
        int *s = malloc(sizeof(int) * 10);
        /* Use the array... */
        /* Attempt to free a different pointer that points to the same memory block */
        int *t = s + 1;
        free(t);
        /* Free the memory for the array */
        free(s);
        break;
    }
    check_memory();
    print_memory();
    return EXIT_SUCCESS;
}
