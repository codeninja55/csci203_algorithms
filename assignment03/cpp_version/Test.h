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

#define MAX_SIZE 100
#define nodes 20

void dijkstra2(float graph[MAX_SIZE][MAX_SIZE], int src);
int shortest_distance(const float *D, const bool *visited);
void print_dijkstra(float dist[], int n);

void dijkstra2(float graph[MAX_SIZE][MAX_SIZE], int src)
{
    int i;
    float distance[MAX_SIZE];
    bool visited[MAX_SIZE];  // visited[i] will be true if vertex i is included in the shortest visited

    // Initialize all distances as INFINITE and visited to be false
    for (i = 0; i < MAX_SIZE; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    // distance of source vertex from itself is always 0
    distance[src] = 0;

    // find the shortest visited for all vertices
    int count;
    for (count = 0; count < MAX_SIZE - 1; count++) {
        // pick the min distance vertex from the set of vertices not yet processed.
        int u = shortest_distance(distance, visited);

        // mark the picked vertex as processed
        visited[u] = true;

        // update distance values of the adjacent vertices of the picked vertex
        int v;
        for (v = 0; v < MAX_SIZE; v++) {
            // update distance[v] only if it is not in the visited, there is an edge from u to v,
            // and total weight of visited from src to v through u is smaller than current value
            // of distance[v]
            if (!visited[v] && graph[u][v] && distance[u] != INT_MAX && distance[u] + graph[u][v] < distance[v])
                distance[v] = distance[u] + graph[u][v];
        }
    }
    print_dijkstra(distance, MAX_SIZE);
}

int shortest_distance(const float *D, const bool *visited)
{
    int idx, min_idx = 0;
    float min = INT_MAX;
    for (idx = 0; idx < MAX_SIZE; idx++) {
        if (D[idx] <= min && !visited[idx]) {
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
