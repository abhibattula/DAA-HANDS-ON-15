#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct Edge {
    int src, dest, weight;
};

struct Graph {
    int numVertices, numEdges;
    struct Edge* edges;
};

struct Graph* createGraph(int numVertices, int numEdges) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    graph->edges = (struct Edge*)malloc(numEdges * sizeof(struct Edge));
    return graph;
}


void bellmanFord(struct Graph* graph, int src) {
    int numVertices = graph->numVertices;
    int numEdges = graph->numEdges;
    int dist[numVertices];

    // Initialize distances
    for (int i = 0; i < numVertices; ++i) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

  
    for (int i = 1; i <= numVertices - 1; ++i) 
    {
        for (int j = 0; j < numEdges; ++j) 
        {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
            }
        }
    }


    for (int i = 0; i < numEdges; ++i) 
    {
        int u = graph->edges[i].src;
        int v = graph->edges[i].dest;
        int weight = graph->edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
        {
            printf("Graph contains negative-weight cycle\n");
            return;
        }
    }


    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < numVertices; ++i) 
    {
        printf("%d -> %d\n", i, dist[i]);
    }
}

int main() 
{
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    struct Graph* graph = createGraph(numVertices, numEdges);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) 
    {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        graph->edges[i].src = src;
        graph->edges[i].dest = dest;
        graph->edges[i].weight = weight;
    }

    int sourceVertex;
    printf("Enter the source vertex for Bellman-Ford algorithm: ");
    scanf("%d", &sourceVertex);

    bellmanFord(graph, sourceVertex);

    return 0;
}
