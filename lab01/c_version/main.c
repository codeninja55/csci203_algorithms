/*********************************************************************
 * CSCI203 - Exercise 1
 * main.c - main() for exercise 1 execution
 * Dinh Che | dbac496 | Last modified 2018.07.29
 * Author: codeninja55
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define STACK_SIZE 50
#define WORD_SIZE 20

/* Stack implementation */
char STACK[WORD_SIZE][STACK_SIZE];
int CTR = 0;

void push(char*);
char* pop();
bool isEmpty();
char* top();
void fatal(char*); // Display an error message and then exit

int main()
{
    /* Change the directory back one where the text file is */
    chdir("/mnt/c/Users/codeninja/Dropbox/uow_csci203/csci203_algorithms/lab01/");
    /* FILE IO */
    FILE *fptr;
    char file_buffer[200], word[WORD_SIZE];



    // display a prompt for the file name and print to stdout file to open
    // printf("Input file name: ");
    // scanf("%s", file_buffer);
    // TODO: Testing
    strcpy(file_buffer, "Ex1.txt");
    printf("Opening file: %s\n\n", file_buffer);

    // try to open file and exit if it fails
    if((fptr = fopen(file_buffer, "r")) == NULL) {
        fatal("[DEBUG] Error opening file.");
        exit(1);
    }

    // Read in a word from the file until EOF and then put in stack
    do {
      fscanf(fptr, "%s", word);
      push(word);
    } while(fscanf(fptr, "%s", word) != EOF);

    fclose(fptr);

    while(!isEmpty()) printf("Popping top word: %s\n", pop());

    return 0;
}

void push(char* word) { strcpy(STACK[CTR++], word); }

char* pop()
{
  if(isEmpty()) return NULL;
  else {
    CTR--;
    return STACK[CTR];
  }
}

// Returns the top word in the STACK
char* top() { return STACK[CTR-1]; }

// Returns true if the CTR is 0
bool isEmpty() { return (CTR==0); }

// A function to display an error message and then exit
void fatal(char *message)
{
    char error_message[200];

    strcpy(error_message, "[!!] Fatal Error ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
/*
void *ec_malloc(unsigned int size)
{
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}*/
