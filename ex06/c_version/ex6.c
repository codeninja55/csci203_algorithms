/*********************************************************************
* CSCI203 - Exercise 6
* ex6.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.03
*********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

#define BUFFER_SZ 100


int main(int argc, const char * argv[])
{
    printf("|==========| CSCI203 Exercise 05 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ], pwd[BUFFER_SZ];

    if (argc == 2)  // arg passed
        strncpy(buffer, argv[1], BUFFER_SZ);
    else {  // no arg passed
        printf("Input file name >> ");
        fgets(filename, BUFFER_SZ, stdin);  // safer read from stdin than scanf()
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("\"[!!] Error: Failed to open file\\nExit(1)...\\n\"");
        return -1;
    }

    // while (fscanf(fd, "%s", &something) == 1)
    fclose(fd);
}
