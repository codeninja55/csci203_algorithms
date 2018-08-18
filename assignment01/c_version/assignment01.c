/*********************************************************************
* CSCI203 - Assignment 1
* assignment01.c - main() driver for assignment 1 implementation
* Dinh Che | dbac496 | Last modified 2018.08.18
* Author: codeninja55
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "helper.h"

#define BUFFER_SZ 200
#define SIZE 50000
#define WORD_SZ 50
#define IN 1  /* inside a word */
#define OUT 0  /* outside a word */
typedef struct Word Word;

struct Word {
  int start_idx;
  int end_idx;
  int length;
  int count;
};

// struct Node {
//   char word[50];
//   int count;
// };

/* Global Vars */
char POOL[SIZE * 10];
Word WORDS[SIZE];
int next = 0;

/* Function prototypes */
char to_lower(int);
void append(char *, int, char);
char * build_word();
// insert_word();
// find_word();

int main( int argc, const char* argv[] )
{
    printf("[DEBUG] Testing at: %s\n\n", get_current_time());

    FILE *fd;
    char buffer[BUFFER_SZ], filename[BUFFER_SZ];

    // 1. Read the name of the text file from the console
    /* Implementation: if console params from console, read into filename.
     * else display a prompt for the file name and print to stdout file to open. */
    if ( argc == 2 )
        strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        strcpy(filename, buffer);
    }

    if ( (fd = fopen(filename, "r")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    int ch, nl, nw, word_idx, cursor;
    int state = OUT;
    nl = nw = word_idx = cursor = 0;
    char * new_word;
    new_word = (char *) ec_malloc(sizeof(char) * WORD_SZ);

    // 2. Read in a text file, not all at once. (This can be line by line, word by word, or char by char).
    while ( (ch = fgetc(fd) ) != EOF ) {
        if ( ferror(fd) )
            break;

        if ( isalpha(ch) )
            fprintf(stdout, "[%c]", to_lower(ch));

        // 3. The file content must be converted to a sequence of words, discarding punctuation and
        // folding all letters into lower case
        if ( ch == '\n' ) {
            state = OUT;
            ++nl;
        }

        if ( ch == ' ' || ch == '\n' || ch == '\t' )
            state = OUT;

        if ( isalpha(ch) ) {
            state = IN;
            new_word[word_idx++] = to_lower(ch);
        }

        if ( state == OUT ) { // end of word
            new_word[word_idx] = '\0';
            ++nw;
            // insert_word()
            printf(" | %s \n", new_word);
            free(new_word);
            new_word = (char *) ec_malloc(sizeof(char) * WORD_SZ);
            state = OUT;
            word_idx = 0;
        }

        // 4. Store the unique words and maintain a count of each different word.
    }

    fclose(fd);

    // 5. The words should be ordered by decreasing count and, if there are multiple words with the same count,
    // alphabetically. (This ordering may be achieved as the words are read in, partially as the words are read,
    // or at the end of all input processing.

    // 6. Output the first ten words in the sorted list, along with their counts.

    // 7. Output the last ten words in the list, along with their counts.

}

/* PRIVATE FUNCTIONS */

char* build_word()
{

}

/****************************************************************************
 * Title: The C Programming Language, 2nd edition
 * Author: Kernighan, B.W. & Ritchie, D.M.
 * Year: 1988
 * Type: Example code.
 ****************************************************************************/
 // Wrapper function to convert a a char and coerce it from an int to a char
// char * to_lower(char ch)
char to_lower(int ch)
{
    return (char) tolower(ch);
}