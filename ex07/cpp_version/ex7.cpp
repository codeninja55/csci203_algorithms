/*******************************************************************************
* CSCI203 - Exercise 7 | ex7.cpp
*
* Purpose: Main driver for implementation of Breadth First Search. Includes
*          definition and implementation of a Queue template class
*          using an array.
*
* @version: 1.0
* @date: 2018.09.24
*
* @author: Dinh Che (codeninja55) <andrew at codeninja55.me>
* Student Details: Dinh Che (5721970) <dbac496 at uowmail.edu.au>
*******************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
// #include "queue.h"

using namespace std;

#define BUFFER_SZ 100
#define GRAPH_SZ 25

/* CLASS DEFINITION */
template<class T>
class Queue {
    public:
        Queue();
        explicit Queue(int);
        ~Queue();
        int is_full();
        int is_empty();
        void enqueue(T);
        void probe();
        T dequeue();
        void print_queue();
    private:
        T *items;
        int _head, _tail, _capacity, n_items;
};

/* FUNCTION PROTOTYPES */
void BFS(int);
void set_edge(int, int);
void print_matrix();

int graph_size;
int **ADJ;  // ADJ matrix
bool *visited;  // set of verticies visited during BFS
int *parents;  // set of parents of vertices
int *vertices;  // set of vertices

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
    // Generate a multidimension 2d matrix for the graph
    ADJ = new int*[graph_size];
    int i;
    for (i = 0; i < graph_size; i++)
        ADJ[i] = new int[graph_size];

    visited = new bool[graph_size];
    for (i = 0; i < graph_size; i++)
        visited[i] = false;

    parents = new int[graph_size];
    vertices = new int[graph_size];

    int from, to;

    while(!fin.eof()) {
        fin >> from >> to;
        set_edge(from, to);
    }
    fin.close();

    // print_matrix();
    BFS(0);

    // print result
    for (i = 0; i < graph_size; i++)
        cout << parents[vertices[i]] << " " << vertices[i] << endl;
    cout << endl;
}

void BFS(int s)
{
    int current, i, ctr;
    ctr = 0;
    Queue<int> Q = Queue<int>(graph_size);  // queue of vertices

    parents[s] = -1;
    visited[s] = true;

    Q.enqueue(s);

    while (Q.is_empty() == 0) {
        current = Q.dequeue();
        vertices[ctr++] = current;

        for (i = 0; i < graph_size; i++) {
            if (ADJ[current][i] == 1) {
                if (!visited[i]) {
                    Q.enqueue(i);
                    parents[i] = current;
                    visited[i] = true;
                }
            }
        }
    }

}

/*
 * @brief: insert an edge into the matrix.
 * @param f: the vertex from.
 * @param t: the vertex the edge ends at.
 */
void set_edge(int f, int t)
{
    ADJ[f][t] = 1;
    ADJ[t][f] = 1;
}

/*
 * A quick method to print the adjacency matrix 
 */
void print_matrix()
{
    int i, j;
    cout << "     ";
    for (i = 0; i < graph_size; i++) cout << setw(3) << i;
    cout << "\n";
    for (i = 0; i < graph_size; i++) {
        cout << setw(2) << i << "  [";
        for (j = 0; j < graph_size; j++) cout << setw(3) << ADJ[i][j];
        cout << "  ]\n";
    }
    cout << endl;
}

/* QUEUE TEMPLATE CLASS */
template<class T>
Queue<T>::Queue(): _head(-1), _tail(-1), _capacity(2), n_items(0)
{
    items = new T[2];
}

template<class T>
Queue<T>::Queue(int size): _head(-1), _tail(-1), _capacity(size), n_items(0)
{
    items = new T[size];
}

template<class T>
Queue<T>::~Queue()
{
    delete[] items;
}

template<class T>
int Queue<T>::is_full() { return (_head == _capacity - 1) ? 1 : 0; }

template<class T>
int Queue<T>::is_empty() { return (_head == -1) ? 1 : 0; }

template<class T>
void Queue<T>::enqueue(T elem)
{
    if (is_full() == 1) {
        std::cout << "Queue is full.\n";
        return;
    } else {
        if (_head == -1) _head = 0;

        probe();
        _tail++;
        items[_tail] = elem;
    }
}

template<class T>
void Queue<T>::probe()
{
    if (n_items > _capacity / 2) {
        T *tmp = items;
        items = new T[_capacity * 2];
        int i;
        for (i = 0; i < _capacity; i++) items[i] = tmp[i];
        _capacity *= 2;
        delete[] tmp;
    }
}

template<class T>
T Queue<T>::dequeue() {
    T ret;
    if (is_empty() == 1) {
        std::cout << "Queue is empty.\n";
        ret = -1;
    } else {
        ret = items[_head++];
        if (_head > _tail) _head = _tail = -1;
    }
    return ret;
}

template<class T>
void Queue<T>::print_queue() {
    int i;
    std::cout << "Queue ==> ";
    for (i = 0; i < n_items; i++)
        std::cout << items[i] << " ";
    std::cout << std::endl;
}
