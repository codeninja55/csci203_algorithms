/*********************************************************************************
*  * PROGRAM TITLE
* Assignment03 Test.h
* Purpose:
*
* @version {MAJOR}.{MINOR}.{STATUS}
* @date 24/10/18
*
* @author Andrew Dinh Che (codeninja) <andrew@codeninja55.me>
* @UOW dbac496 (5721970) <dbac496@uowmail.edu.au>
* LICENSE
*********************************************************************************/

#ifndef ASSIGNMENT03_TEST_H
#define ASSIGNMENT03_TEST_H

#include <climits>
#include <cstdio>

#define SIZE 100
#define nodes 20

void dijkstra2(float graph[SIZE][SIZE], int src);
int shortest_distance(const float *D, const bool *path);
void print_dijkstra(float dist[], int n);

void dijkstra2(float graph[SIZE][SIZE], int src)
{
    int i;
    float distance[SIZE];
    bool path[SIZE];  // path[i] will be true if vertex i is included in the shortest path

    // Initialize all distances as INFINITE and path to be false
    for (i = 0; i < SIZE; i++) {
        distance[i] = INT_MAX;
        path[i] = false;
    }

    // distance of source vertex from itself is always 0
    distance[src] = 0;

    // find the shortest path for all vertices
    int count;
    for (count = 0; count < SIZE - 1; count++) {
        // pick the min distance vertex from the set of vertices not yet processed.
        int u = shortest_distance(distance, path);

        // mark the picked vertex as processed
        path[u] = true;

        // update distance values of the adjacent vertices of the picked vertex
        int v;
        for (v = 0; v < SIZE; v++) {
            // update distance[v] only if it is not in the path, there is an edge from u to v,
            // and total weight of path from src to v through u is smaller than current value
            // of distance[v]
            if (!path[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                distance[v] = distance[u] + graph[u][v];
        }
    }
    print_dijkstra(distance, SIZE);
}

int shortest_distance(const float *D, const bool *path)
{
    int idx, min_idx = 0;
    float min = INT_MAX;
    for (idx = 0; idx < SIZE; idx++) {
        if (D[idx] <= min && !path[idx]) {
            min = D[idx];
            min_idx = idx;
        }
    }
    return min_idx;
}

// A utility function to print the constructed distance array
void print_dijkstra(float dist[], int n)
{
    printf("%-8s %-20s\n", "Vertex", "Distance from Source");
    for (int i = 1; i <= nodes; i++)
        printf("%-8d %-20.3f\n", i, dist[i]);
}

#endif //ASSIGNMENT03_TEST_H
