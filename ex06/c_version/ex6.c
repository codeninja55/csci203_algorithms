/*********************************************************************
* CSCI203 - Exercise 6
* ex6.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.04
*********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include "helper.h"

#define BUFFER_SZ 100
#define d 4  // universe of chars A, C, G, and T
#define q 7  // prime number to use

// 7 19 24 28 8
//

void rabin_karp_search(char[], char[]);

int main(int argc, const char * argv[])
{
    printf("|==========| CSCI203 Exercise 06 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ], pwd[BUFFER_SZ];

    if (argc == 2)  // arg passed
        strncpy(filename, argv[1], BUFFER_SZ);
    else {  // no arg passed
        printf("Input file name >> ");
        fgets(filename, BUFFER_SZ, stdin);  // safer read from stdin than scanf()
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("[!!] Error: Failed to open file\nExit(1)...\n");
        return -1;
    }

    char T[5000];
    char P[10];
    fscanf(fd, "%s %s", T, P);
    printf("\n|=====| Output |=====|\n\n");
    rabin_karp_search(T, P);

    fclose(fd);
}

/* A string pattern matching search using the Rabin-Karp Algorithm
 * :param T: Char array to search.
 * :param P: Char array pattern to match.
 * :param q: A prime number to use in hashing.
 * */
void rabin_karp_search(char T[], char S[])
{
    int s_len = (int) strlen(S);
    int t_len = (int) strlen(T);
    int i, j;
    int p = 0;  // hash value for pattern
    int t = 0;  // hash value for text string

    // preprocessing the hash value of p
    // the hash function is pow(d, M - 1) mod q
    int h = 1;
    for (i = 0; i < s_len - 1; i++)
        h = (h * d) % q;

    // preprocessing the hash value of pattern and first part of search
    for (i = 0; i < s_len; i++) {
        p = (d * p + S[i]) % q;
        t = (d * t + T[i]) % q;
    }

    // matching
    for (i = 0; i <= t_len; i++) {
        // check the value of the current substr and iterate over chars if they match
        if (p == t) {
            for (j = 0; j < s_len; j++)
                if (T[i+j] != S[j]) break;  // if the next char doesnt match, no match found

            if (j == s_len) printf("%-3d ", i);
        }

        // apply the hash function for the next substr by
        // removing the leading digit and adding trailing digit
        if (i < t_len - s_len) {  // N - M because if the remaining string < M then stop
            t = (d * (t - T[i] * h) + T[i + s_len]) % q;  // rolling update

            if (t < 0) t += q;  // ensure t is always positive
        }
    }
}
