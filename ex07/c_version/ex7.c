/*********************************************************************
* CSCI203 - Exercise 7
* ex7.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.24
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"

#define BUFFER_SZ 100

int main(int argc, const char * argv[])
{
    printf("|==========| CSCI203 Exercise 07 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char filename[BUFFER_SZ];

    if (argc == 2)
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        printf("Input file name >> ");
        fgets(filename, BUFFER_SZ, stdin);  // safe read
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("[!!] Error: Failed to open file\nExit(1)...\n");
        return -1;
    }


    fclose(fd);

    return 0;
}
