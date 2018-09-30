/*********************************************************************
* CSCI203 - Exercise 7
* ex7.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.24
*********************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "ex7.h"
#include "queue.h"

using namespace std;

#define BUFFER_SZ 100
#define GRAPH_SZ 25


/* FUNCTION PROTOTYPES */
void BFS(int);
void set_edge(int, int);
void print_matrix();

int graph_size;
int **G;
int *visited;

int main(int argc, const char * argv[])
{
    cout << "|==========| CSCI203 Exercise 07 |==========|\nAuthor: Dinh Che (dbac496)\n\n";
    ifstream fin;
    char filename[BUFFER_SZ];

    if (argc == 2)
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    fin.open(filename);
    if(!fin.good()) {
        cout << "[!!] Error: Failed to open file: " << filename << "\nExiting...\n";
        return -1;
    }

    fin >> graph_size;
    // int G[graph_size][graph_size];
    G = new int*[graph_size];
    int i;
    for (i = 0; i < graph_size; i++)
        G[i] = new int[graph_size];

    // int visited[graph_size];
    visited = new int[graph_size];
    int from, to;

    while(!fin.eof()) {
        fin >> from >> to;
        set_edge(from, to);
    }

    fin.close();
    print_matrix();
    BFS(0);
    cout << "Visited: " << endl;
    for (i = 0; i < graph_size; i++) cout << visited[i] << " ";
}

void BFS(int s)
{
    int current, ctr, i, j;
    ctr = 0;
    Queue<int> Q = Queue<int>(graph_size);

    Q.enqueue(s);

    while (Q.is_empty() == 0) {
        Q.print_queue();

        current = Q.dequeue();
        visited[ctr++] = current;

        for (i = 0; i < graph_size; i++) {
            if (G[current][i] == 1) {
                bool found = false;

                for (j = 0; j < graph_size; j++)
                    if (i == visited[j]) found = true;

                if (found) Q.enqueue(i);
            }
        }
    }
}

void set_edge(int f, int t)
{
    G[f][t] = 1;
    G[t][f] = 1;
}

void print_matrix()
{
    int i, j;
    cout << "     ";
    for (i = 0; i < graph_size; i++) cout << setw(3) << i;
    cout << "\n";
    for (i = 0; i < graph_size; i++) {
        cout << setw(2) << i << "  [";
        for (j = 0; j < graph_size; j++) cout << setw(3) << G[i][j];
        cout << "  ]\n";
    }
    cout << endl;
}

