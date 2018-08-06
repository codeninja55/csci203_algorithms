#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err34-c"
/*********************************************************************
 * CSCI203 - Exercise 2
 * ex2.c - main() for exercise 2 execution
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
void recursive_siftup(int*, int);
void siftdown(int*, int);
void recursive_siftdown(int*, int);
void swap(int*, int*);
int get_parent(int);
int get_left(int);
int get_right(int);

/* Heap implementation */
int HEAP[100];
int N_CTR = 0;


int main()
{
    FILE *fd;
    char filename[200];
    unsigned int *node;
    node = (unsigned int *) ec_malloc(sizeof(unsigned int));

    char pwd[100];
    // Set config directory to lab02 folder and chdir() not needed
    getcwd(pwd, sizeof(pwd));
    printf("\nPWD: %s\n", pwd);

    // TODO: TESTING ONLY
    strcpy(filename, "Ex2.txt");
    printf("Opening file: %s/%s\n\n", pwd, filename);

    if ((fd = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    printf("==========| PRINTING READ ELEMENTS (FIRST 5) |==========\n");

    while(fscanf(fd, "%d", node) == 1) {
        if (ferror(fd)) break; // if the read fails, break the loop
        if (N_CTR < 5) printf("[%d]: %d ", N_CTR + 1, *node);

        // TODO: Testing Ian's pseudocode version
        // HEAP[N_CTR++] = *node;

        // TODO: codeninja55 version
        HEAP[N_CTR] = *node;
        recursive_siftup(HEAP, N_CTR);
        // siftup(HEAP, N_CTR);
        N_CTR++;
    }
    fclose(fd);

    // makeheap();

    printf("\n==========| PRINTING HEAP ELEMENTS (FIRST 5) |==========\n");
    for (int i = 0; i < 5; i++) printf("[%d]: %d ", i + 1, HEAP[i]);

    return 0;
}

void makeheap()
{
    // The pseudocode shows this but the impl is inefficient
    for (int i = N_CTR / 2; i >= 0; i--) siftdown(HEAP, i);
}

void siftup(int *T, int i)
{
    if (i == 0) return;
    int parent = get_parent(i);
    if (T[parent] > T[i]) return;
    else {
        while (parent >= 0) {
            if (T[i] > T[parent]) {
                swap(&T[parent], &T[i]);
                parent = get_parent(parent);
            }
            else return;
        }
    }
}

void recursive_siftup(int *heap, int i)
{
     // move element i up to its correct position
     if (i==0) return;  // no children
     int parent = i / 2;  // integer division
     if (heap[parent] > heap[i]) return;
     else {
         swap(&heap[i], &heap[parent]);
         recursive_siftup(heap, parent);
     }
}

void siftdown(int *heap, int i) {  }

void recursive_siftdown(int *heap, int i)
{
    // move element i down to its correct position
    int child = i * 2;
    if (heap[child] < heap[get_right(i)]) child += 1;  // Look for larger of 2 children
    if (heap[i] < heap[child]) {
        swap(&heap[i], &heap[child]);
        recursive_siftdown(heap, child);
    }
}

void swap(int *v1, int *v2)
{
     int temp = *v1;
     *v1 = *v2;
     *v2 = temp;
}

// TODO: Need to fix these to find the right index number
int get_parent(int i) { return ((i+1) / 2) - 1; }
int get_left(int i) { return ((i+1) * 2) - 1; }
int get_right(int i) { return (((i+1) * 2) + 1) - 1; }

#pragma clang diagnostic pop