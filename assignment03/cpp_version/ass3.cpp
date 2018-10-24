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
#include <climits>
#include "MinHeap.h"
#include "HashMap.h"
#include "Test.h"
using namespace std;

#define BUFFER_SZ 200
#define SIZE 100

typedef struct Node {
    int id;
    float X;
    float Y;

    /*friend bool operator>(const Node &lhs, const Node &rhs) {

    }*/

    friend ostream& operator<<(ostream& os, Node const &node) {
        return os << node.id << ": " << "(" << node.X << ", " << node.Y << ")";
    }
} Node;

/* PROTOTYPES */
void set_edge(int f, int t, float c);
void print_matrix();
int* dijkstra(int (*G)[SIZE]);

/* GLOBALS */
int n_nodes, n_edges;
float MATRIX[SIZE][SIZE];
// MinHeap<Node> Candidate;

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
        perror("[*****FILE ERROR*****] Unable to open file");
        exit(1);
    }

    /*
     * Input consists of the following data:
     *  1) The number of nodes in the graph
     *  2) A set of triples containing the node number, its X-coordinate and its Y-coordinate -
     *     one triple for each node in the graph.
     *  3) The number of edges in the graph.
     *  4) A set of triples consisting of two node numbers and a cost - one triple for each edge
     *     in the graph.
     *  5) A pair of node numbers representing the start and end nodes between which a path
     *     must be found.
     *
     * */

    // number of nodes in graph
    fin >> n_nodes;
    // MinHeap<Node> Candidate_Q = MinHeap<Node>(n_nodes);
    // HashMap<int, Node> Nodes_Map = HashMap<int, Node>(n_nodes);
    Node Nodes_Arr[n_nodes + 1];

    for (i = 1; i <= n_nodes; i++) {
        Node new_node;
        fin >> new_node.id;
        fin >> new_node.X;
        fin >> new_node.Y;
        Nodes_Arr[new_node.id] = new_node;
        // Nodes_Map.insert_node(new_node.id, new_node);
    }

    // Nodes_Map.display();

    // number of edges in graph
    fin >> n_edges;

    int from, to;
    float cost;

    for (i = 1; i <= n_edges; i++) {
        fin >> from >> to >> cost;
        set_edge(from, to, cost);
    }

    print_matrix();

    // Paths from each
    dijkstra2(MATRIX, 19);

    /*
     * Your task is to:
     *  1. Code the modified Dijkstra's algorithm to search from the start node out.
     *  2. Code the A* variant.
     *  3. Code the proposed improved algorithm.
     *
     * */
}

/*int* dijkstra(int (*G)[SIZE])
{
    int Parents[SIZE], Selected[SIZE], *Distance;
    int i, vertex;

    Distance = new int[SIZE];  // avoiding local scope issue of Distance

    for (i = 1; i < SIZE; i++) {
        Distance[i] = G[1][i];
        Parents[i] = 1;
    }

    // vertex = shortest_distance(Distance[])

    // while(Candidate[ctr]) {

        // vertex = the index of the minimum D[v] not yet selected
        // remove v from C
        // and implicitly add v to S

        *//*
         * for each w in C do:
         *      if D[w] > D[w] + G[v][w] then:
         *          D[w] = min(D[w], D[v] + G[v][w]
         *          P[w] = v
         * *//*

        // ctr++;
    // }
    return Distance;
}*/

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
    std::cout << "     ";
    for (i = 1; i <= n_nodes; i++) std::cout << std::setw(6) << i;
    std::cout << "\n";
    for (i = 1; i <= n_nodes; i++) {
        std::cout << std::setw(2) << i << "  [";
        for (j = 1; j <= n_nodes; j++) std::cout << std::setw(6) << MATRIX[i][j];
        std::cout << "     ]\n";
    }
    std::cout << std::endl;
}
