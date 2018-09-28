/*********************************************************************
* CSCI203 - Exercise 7
* ex7.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.24
*********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "helper.h"

#define BUFFER_SZ 100
#define G_SZ 25

typedef struct {
    int head, tail, capacity;
    int items[G_SZ];
} queue;

int n_size;

void print_matrix(int G[n_size][n_size]);
// Queue prototypes
queue* create_queue(int);
int is_full(queue*);
int is_empty(queue*);
void enqueue(int, queue*);
int dequeue(queue*);
void print_queue(queue *q);
// Graph prototypes
void init_matrix(int M[n_size][n_size]);
void set_edge(int G[n_size][n_size], int f, int t);
void BFS(int s, int adj[n_size][n_size], int v[]);


int main(int argc, const char * argv[])
{
    printf("|==========| CSCI203 Exercise 07 |==========|\n"
           "Author: Dinh Che (dbac496)\nRun at: %s", get_current_time());
    FILE *fd;
    char filename[BUFFER_SZ];

    if (argc == 2)
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        printf("Input file name >> ");
        fgets(filename, BUFFER_SZ, stdin);  // safe read
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("[!!] Error: Failed to open file\nExit(1)...\n");
        return -1;
    }

    fscanf(fd, "%d", &n_size);

    int G[n_size][n_size];
    int visited[G_SZ] = {0};  // TODO: Remember to remove variable size object
    init_matrix(G);

    int from, to;

    while (fscanf(fd, "%d %d", &from, &to) == 2)
        set_edge(G, from, to);

    fclose(fd);
    print_matrix(G);

    BFS(0, G, visited);

    int i;
    printf("Visited: ");
    for (i = 0; i < n_size; i++)
        printf("%d ", visited[i]);

    return 0;
}

void BFS(int s, int adj[n_size][n_size], int *v)
{
    int current, ctr, j, k;
    ctr = 0;
    queue *q = create_queue(n_size);

    enqueue(s, q);

    while (is_empty(q)) {
        print_queue(q);
        current = dequeue(q);
        printf("C: %d \n", current);
        v[ctr++] = current;

        for (j = 0; j < n_size; j++) {
            if (adj[current][j] == 1) {
                printf("G[%d][%d]: %d \n", current, j, adj[current][j]);
                bool found = false;
                for (k = 0; k < n_size; k++) {
                    if (j == v[k])
                        found = true;
                }
                if (found)
                    enqueue(j, q);
            }
        }
    }
}

queue* create_queue(int size)
{
    queue* q = ec_malloc(sizeof(queue));
    q->head = -1;
    q->tail = -1;
    q->capacity = size;
    return q;
}

int is_full(queue *q) { return (q->tail == q->capacity - 1) ? 1 : 0; }

int is_empty(queue* q) { return (q->tail == -1) ? 1 : 0; }

void enqueue(int elem, queue *q)
{
    if (is_full(q) == 1) {
        printf("Queue is full");
        return;
    } else {
        if (q->head == -1)
            q->head = 0;

        q->tail++;
        q->items[q->tail] = elem;
    }
}

int dequeue(queue *q)
{
    int ret;
    if (is_empty(q)) {
        printf("Queue is empty");
        ret = -1;
    } else {
        ret = q->items[q->head];
        q->head++;
        if (q->head > q->tail)
            q->head = q->tail = -1;
    }
    return ret;
}

void print_queue(queue *q)
{
    int i;
    if (is_empty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->head; i < q->tail + 1; i++)
            printf("%d ", q->items[i]);
        printf("\n");
    }
}

void set_edge(int G[n_size][n_size], int f, int t)
{
    G[f][t] = 1;
    G[t][f] = 1;
}

void init_matrix(int M[n_size][n_size])
{
    int i, j;
    for (i = 0; i < n_size; i++) {
        for (j = 0; j < n_size; j++)
            M[i][j] = 0;
    }
}

void print_matrix(int G[n_size][n_size])
{
    int i, j;
    printf("     ");
    for (i = 0; i < n_size; i++) printf("%3d,", i);
    printf("\n");
    for (i = 0; i < n_size; i++) {
        printf("%2d  [", i);
        for (j = 0; j < n_size; j++) printf("%3d,", G[i][j]);
        printf("  ]\n");
    }
    printf("\n");
}
