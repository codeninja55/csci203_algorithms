/*********************************************************************
* CSCI203 - Exercise 5
* ex5.c - main() driver and data structures for exercise 5 implementation
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.08.28
*********************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include "helper.h"
#include "ex5.h"

#define BUFFER_SZ 200
#define BUCKET 100
#define M 100

typedef struct HashNode {
    unsigned int key, hashed_key;
    struct HashNode *next, *previous;
} HashNode;

/* GLOBAL VARIABLES */
HashNode HASH_TABLE[BUCKET];

/* FUNCTION PROTOTYPES */
unsigned int simple_hash(unsigned int key);
void insert(unsigned int key);


int main( int argc, const char* argv[] ) {
    printf("|==========| CSCI203 Exercise 05 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ], pwd[BUFFER_SZ];

    if (argc == 2)
        strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        if (strlen(buffer) < BUFFER_SZ) strcpy(filename, buffer);
    }
    getcwd(pwd, sizeof(pwd));
    printf("Opening file: %s/%s\n\n", pwd, filename);

    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[!!] Error: Failed to open file [ %s ]\nExit(1)...\n", strerror(1));
        exit(1);
    }

    unsigned int read_int;
    while (fscanf(fd, "%d", &read_int) == 1) {
        if (ferror(fd)) break;

        // printf("key: %d | hash: %d\n", read_int, simple_hash(read_int));
        insert(read_int);
    }
    fclose(fd);

    for (int i = 0; i < BUCKET; i++) {
        if ( HASH_TABLE[i].key != 0 ) {
            printf("%-4i key [ %d ] | hash [ %d ]\n",
                   i, HASH_TABLE[i].key, HASH_TABLE[i].hashed_key);
            if ( HASH_TABLE[i].next != NULL ) {
                printf("%-4s  key [ %d ] | hash [ %d ]\n",
                       "-->", HASH_TABLE[i].next->key, HASH_TABLE[i].next->hashed_key);
            }
        }
    }
}

void insert(unsigned int key)
{
    HashNode *new_node = ec_malloc(sizeof(HashNode));
    new_node->key = key;
    new_node->hashed_key = simple_hash(key);
    new_node->previous = new_node->next = NULL;

    if ( HASH_TABLE[new_node->hashed_key].hashed_key != new_node->hashed_key )
        HASH_TABLE[simple_hash(key)] = *new_node;
    else {
        new_node->previous = &HASH_TABLE[new_node->hashed_key];
        HASH_TABLE[new_node->hashed_key].next = new_node;
    }
}

unsigned int simple_hash(unsigned int key)
{
    return (key % M);
}

