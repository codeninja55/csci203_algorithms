/*********************************************************************
* CSCI203 - Exercise 5
* ex5.c - main() driver and data structures for exercise 5 implementation
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.08.28
*********************************************************************/

#include <helper.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ex5.h"

#define BUFFER_SZ 200

/* GLOBAL VARIABLES */


/* FUNCTION PROTOTYPES */
unsigned int simple_hash(unsigned int key);


int main( int argc, const char* argv[] ) {
    printf("|==========| CSCI203 Exercise 05 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ];

    if (argc == 2)
        strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        if (strlen(buffer) < BUFFER_SZ) strcpy(filename, buffer);
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[!!] Error: Failed to open file [ %s ]\nExit(1)...\n", strerror(1));
        exit(1);
    }

    int *read_int;
    while ( fscanf(fd, "%i", read_int) == 1 ) {
        if (ferror(fd)) break;


    }
    fclose(fd);
}

