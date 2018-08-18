/*********************************************************************
 * CSCI203 - Exercise 3
 * ex3.c - main() for exercise 3 execution
 * Dinh Che | dbac496 | Last modified 2018.08.13
 * Author: codeninja55
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int DATA[100], FORWARD[100], BACKWARD[100];
int VALID_COUNT = 0;

// Function prototypes
void insert(int, int);
bool check(int);

int main( int argc, const char* argv[] )
{
    FILE *fd;
    char buffer[200], filename[200];
    int what, where, probe;

    // get filename from argv or display a prompt for the file name to open file
    if ( argc == 2 ) strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        strcpy(filename, buffer);
    }

    if ( (fd = fopen(filename, "r")) == NULL ) {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    while ( fscanf(fd, "%d %d", &what, &where) == 2 ) {
        if (ferror(fd)) break; // if the read fails, break the loop
        if (what < 0 || where < 0) break;
        // printf("%d : %d\n", what, where);
        insert(what, where);
    }
    while( fscanf(fd, "%d", &probe) == 1 ) {
        if (ferror(fd) || probe < 0) break;
        printf("%6s : %d\n", check(probe) ? "TRUE" : "FALSE", DATA[probe]);
    }
    fclose(fd);
}

void insert(int what, int where)
{
    VALID_COUNT++;
    DATA[where] = what;
    FORWARD[VALID_COUNT] = where;
    BACKWARD[where] = VALID_COUNT;
}

bool check(int probe)
{
    return BACKWARD[probe] > 0 &&
            BACKWARD[probe] <= VALID_COUNT &&
            FORWARD[BACKWARD[probe]] == probe ?
                true : false;
}
