/*********************************************************************************
 * CSCI203 Algorithms and Data Structures - Assignment 03
 * Assignment03 ass3.cpp
 * Purpose:
 *
 * @version 0.1.dev
 * @date 23/10/18
 *
 * @author Andrew Dinh Che (codeninja) <andrew@codeninja55.me>
 * @UOW dbac496 (5721970) <dbac496@uowmail.edu.au>
 *
 *********************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

#define BUFFER_SZ 200

typedef struct {
    int id;
    float X;
    float Y;
} Node;

/* PROTOTYPES */
void set_edge(int f, int t, float c);
void print_matrix();

/* GLOBALS */
int n_nodes, n_edges;
float MATRIX[100][100];

int main(int argc, char * argv[])
{
    cout << "|==========| CSCI203 Assignment 03 |==========|\nAuthor: Dinh Che (dbac496)\n\n";
    char filename[BUFFER_SZ];
    int i;

    if (argc == 2)
        strncpy(filename, argv[1], BUFFER_SZ);
    else {
        cout << "Input file name >> ";
        cin.getline(filename, BUFFER_SZ);
    }

    ifstream fin(filename, ios::in);

    if (!fin.good()) {
        perror("Unable to open file");
        exit(1);
    }

    // number of nodes in graph
    fin >> n_nodes;

    for (i = 0; i < n_nodes; i++) {
        Node new_node;
        fin >> new_node.id;
        fin >> new_node.X;
        fin >> new_node.Y;

        cout << new_node.id << " ==> (" << new_node.X << new_node.Y << ")" << endl;
    }

    // number of edges in graph
    fin >> n_edges;

    int from, to;
    float cost;

    for (i = 0; i < n_edges; i++) {
        fin >> from >> to >> cost;
        set_edge(from, to, cost);
    }

    print_matrix();
}


void set_edge(int f, int t, float c)
{
    MATRIX[f][t] = c;
    MATRIX[t][f] = c;
}

/*
 * A quick method to print the adjacency matrix
 */
void print_matrix()
{
    int i, j;
    cout << "     ";
    for (i = 0; i <= n_nodes; i++) cout << std::setw(6) << i;
    cout << "\n";
    for (i = 0; i <= n_nodes; i++) {
        cout << std::setw(2) << i << "  [";
        for (j = 0; j <= n_nodes; j++) cout << std::setw(6) << MATRIX[i][j];
        cout << "     ]\n";
    }
    cout << endl;
}
