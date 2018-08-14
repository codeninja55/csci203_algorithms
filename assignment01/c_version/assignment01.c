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

/* Function prototypes */
unsigned char to_lower(char);

int main( int argc, const char* argv[] )
{
    FILE *fd;
    char buffer[200], filename[200];
    char ch;

    // 1. Read the name of the text file from the console
    /* Implementation: if console params from console, read into filename.
     * else display a prompt for the file name and print to stdout file to open. */
    if ( argc == 2 ) strcpy(filename, argv[1]);
    else {
        printf("Input file name: ");
        scanf("%s", buffer);
        strcpy(filename, buffer);
    }

    if ( (fd = fopen(filename, "r")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    // 2. Read in a text file, not all at once. (This can be line by line, word by word, or char by char).
    while ( (ch = (char) fgetc(fd) ) != EOF ) {
        fprintf(stdout, "%c", to_lower(ch));
    }

    fclose(fd);

    // 3. The file content must be converted to a sequence of words, discarding punctuation and
    // folding all letters into lower case

    // 4. Store the unique words and maintain a count of each different word.

    // 5. The words should be ordered by decreasing count and, if there are multiple words with the same count,
    // alphabetically. (This ordering may be achieved as the words are read in, partially as the words are read,
    // or at the end of all input processing.

    // 6. Output the first ten words in the sorted list, along with their counts.

    // 7. Output the last ten words in the list, along with their counts.

}

/****************************************************************************
 * Title: The C Programming Language, 2nd edition
 * Author: Kernighan, B.W. & Ritchie, D.M.
 * Year: 1988
 * Type: Example code.
 ****************************************************************************/
 // Wrapper function to convert a a char and coerce it from an int to a char
unsigned char to_lower(char ch)
{
    return (unsigned char) tolower(ch);
}