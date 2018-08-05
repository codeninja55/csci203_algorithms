/*********************************************************************
 * CSCI203 - Exercise 2
 * main.c - main() for exercise 1 execution
 * Dinh Che | dbac496 | Last modified 2018.07.31
 * Author: codeninja55
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "helper.h"

void siftup(int*, int);
void siftdown(int*, int);
void swap(int, int);

/* Heap implementation */
int HEAP[100];
int CTR = 0;


 int main()
{
    FILE *fd;
    char filename[200];
    int *node;
    node = (int *) ec_malloc(sizeof(int));

    char pwd[100];
    // Set config directory to lab02 folder and chdir() not needed
    // chdir("../../lab02");
    getcwd(pwd, sizeof(pwd));
    printf("PWD: %s\n\n", pwd);

    // TODO: TESTING ONLY
    strcpy(filename, "Ex2.txt");
    printf("Opening file: %s/%s\n\n", pwd, filename);

    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "Failed to open file [ %s ]\n", strerror(1));
        exit(1);
     }

    while(fscanf(fd, "%d", node) == 1) {
        if (ferror(fd)) break; // if the read fails, break the loop
        printf("%d\n", *node);
    }

     return 0;
}

void siftup(int *heap, int i)
{
     // Move element i up to its correct position
     if (i==0) return;
     int parent = i/2; // integer division
     if (heap[parent] > heap[i]) return;
     else {
         swap(heap[i], heap[parent]);
         siftup(heap, parent);
     }
}

void siftdown(int * heap, int i)
{
    // move element i down to its correct position
    int child = i * 2;
    if (heap[child] < heap[child + 1]) child += 1;
    if (heap[i] < heap[child]) {
        swap(heap[i], heap[child]);
        siftdown(heap, child);
    }
}

void swap(int i, int p)
{
     int temp = i;
     i = p;
     p = temp;
}
