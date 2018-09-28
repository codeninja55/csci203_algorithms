/*********************************************************************
* CSCI203 - Exercise 7
* ex7.c - main() driver for implementation of Karp-Rabin string search algorithm
* Author: Dinh Che (codeninja55) | andrew at codeninja55.me
* UOW Details: Dinh Che (5721970) | dbac496 at uowmail.edu.au
* Last modified: 2018.09.24
*********************************************************************/

#include "ex7.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define BUFFER_SZ 100
#define GRAPH_SZ 25

int graph_size;

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
    int G[graph_size][graph_size];
    int visited[graph_size];

    fin.close();

}
