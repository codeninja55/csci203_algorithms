#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
/*********************************************************************
 * CSCI203 - Exercise 2
 * main.c - main() for exercise 1 execution
 * Dinh Che | dbac496 | Last modified 2018.08.01
 * Author: codeninja55
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "helper.h"

void makeheap();
void siftup(int*, int);
void siftdown(int*, int);
void swap(int*, int*);

/* Heap implementation */
int HEAP[100];
int N_CTR = 0;


int main()
{
    FILE *fd;
    char filename[200];
    int *node;
    node = (int *) ec_malloc(sizeof(int));

    char pwd[100];
    // Set config directory to lab02 folder and chdir() not needed
    getcwd(pwd, sizeof(pwd));
    printf("PWD: %s\n\n", pwd);

    // TODO: TESTING ONLY
    strcpy(filename, "Ex2.txt");
    printf("Opening file: %s/%s\n\n", pwd, filename);

    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    printf("\n==========| PRINTING READ ELEMENTS (FIRST 5) |==========\n");

    while(fscanf(fd, "%d", node) == 1) {
        if (ferror(fd)) break; // if the read fails, break the loop
        if (N_CTR <= 5) printf("[%d]: %d ", N_CTR, *node);

        // TODO: Testing Ian's pseudocode version
        // HEAP[N_CTR++] = *node;

        // TODO: codeninja55 version
        HEAP[N_CTR] = *node;
        siftup(HEAP, N_CTR);
        N_CTR++;
    }
    fclose(fd);

    // TODO: Testing Ian's pseudocode version
    printf("\n==========| N_CTR |==========| %d\n\n", N_CTR);
    // makeheap();

    printf("\n==========| PRINTING HEAP ELEMENTS (FIRST 5) |==========\n");
    for (int i = 0; i <= 5; i++) printf("[%d]: %d ", i, HEAP[i]);

    return 0;
}

void makeheap()
{
    // TODO: This is not correct from following pseudocode
    for (int i = N_CTR / 2; i <= 1; i--) {
        siftdown(HEAP, i);
    }
}

void siftup(int *heap, int i)
{
     // move element i up to its correct position
     if (i==0) return;  // no children
     int parent = i/2;  // integer division
     if (heap[parent] > heap[i]) return;
     else {
         swap(&heap[i], &heap[parent]);
         siftup(heap, parent);
     }
}

void siftdown(int *heap, int i)
{
    // move element i down to its correct position
    int child = i * 2;
    if (heap[child] < heap[child + 1]) child += 1;  // Look for larger of 2 children
    if (heap[i] < heap[child]) {
        swap(&heap[i], &heap[child]);
        siftdown(heap, child);
    }
}

void swap(int *v1, int *v2)
{
     int temp = *v1;
     *v1 = *v2;
     *v2 = temp;
}

#pragma clang diagnostic pop