#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to perform Floyd-Warshall algorithm
void floydWarshall(int numVertices, int graph[][numVertices]) {
    int dist[numVertices][numVertices];

    // Initialize distance matrix
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            dist[i][j] = graph[i][j];
        }
    }

    // Compute shortest paths
    for (int k = 0; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print shortest distances
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (dist[i][j] == INT_MAX) {
                printf("INF ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int numVertices;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    int graph[numVertices][numVertices];

    printf("Enter the adjacency matrix (INF for infinity):\n");
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == -1) {
                graph[i][j] = INT_MAX;
            }
        }
    }

    floydWarshall(numVertices, graph);

    return 0;
}
