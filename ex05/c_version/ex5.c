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

#define MAX(a,b) ( (a > b) ? a : b )
#define BUFFER_SZ 200
#define BUCKET 100
#define M 100

typedef struct HashNode {
    unsigned int key, hashed_key;
    struct HashNode *next;
} HashNode;
typedef HashNode *HashNodePtr;

/* GLOBAL VARIABLES */
HashNode HASH_TABLE[BUCKET];
int longest_chain = 0;
int chain_length = 0;

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


    memset(HASH_TABLE, '\0', sizeof(HASH_TABLE));
    unsigned int read_int;

    while ( fscanf(fd, "%d", &read_int) == 1 ) {
        if ( ferror(fd) ) break;

        insert(read_int);
    }
    fclose(fd);

    int empty_entries = 0;
    for (int i = 0; i < BUCKET; i++) {
        if ( HASH_TABLE[i].key != 0 ) {
            printf("%-3d <== [ %4d ]", HASH_TABLE[i].hashed_key, HASH_TABLE[i].key);
            HashNodePtr temp = HASH_TABLE[i].next;
            while ( temp != NULL ) {
                printf(" --> [ %4d ]", temp->key);
                temp = temp->next;
            }
            printf("\n");
        } else
            empty_entries++;
    }

    printf("\nEmpty entries: %d\n", empty_entries);
    printf("\nLongest chain: %d\n", longest_chain);
}

void insert(unsigned int key)
{
    unsigned int index = simple_hash(key);

    if ( HASH_TABLE[index].key == 0 ) {
        // No previous HashNode in position
        HashNode new_node = { .key = key, .hashed_key = index, .next = NULL };
        HASH_TABLE[index] = new_node;
        chain_length = 1;
    } else {
        HashNodePtr head = &HASH_TABLE[index];
        HashNodePtr temp = ec_malloc(sizeof(HashNode));
        memcpy(temp, head, sizeof(HashNode));

        HashNode new_node = { .key = key, .hashed_key = index, .next = temp };
        HASH_TABLE[index] = new_node;
        chain_length++;
        longest_chain = MAX(longest_chain, chain_length);

        /*HashNodePtr prev = NULL;
        HashNodePtr curr = &HASH_TABLE[index];

        while ( curr != NULL ) {
            prev = curr;
            curr = curr->next;
        }

        curr = ec_malloc(sizeof(HashNode));
        curr->hashed_key = index;
        curr->key = key;
        curr->next = NULL;
        prev->next = curr;*/
    }
}

unsigned int simple_hash(unsigned int key)
{
    return (key % M);
}

