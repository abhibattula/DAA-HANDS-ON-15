#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct AdjListNode 
{
    int dest;
    int weight;
    struct AdjListNode* next;
};


struct AdjList {
    struct AdjListNode* head;
};


struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}


struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));
    for (int i = 0; i < numVertices; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}


void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}


int minDistance(int dist[], int visited[], int numVertices) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < numVertices; ++v) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}


void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        return;
    }
    printPath(parent, parent[j]);
    printf("%d ", j);
}


void printSolution(int dist[], int parent[], int src, int numVertices) {
    printf("Vertex   Distance from Source   Path\n");
    for (int i = 0; i < numVertices; ++i) {
        printf("%d -> %d \t\t %d \t\t\t %d ", src, i, dist[i], src);
        printPath(parent, i);
        printf("\n");
    }
}


void dijkstra(struct Graph* graph, int src) {
    int numVertices = graph->numVertices;
    int dist[numVertices];
    int parent[numVertices];
    int visited[numVertices];

    // Initialize distances and parent array
    for (int i = 0; i < numVertices; ++i) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < numVertices - 1; ++count) {
        int u = minDistance(dist, visited, numVertices);
        visited[u] = 1;

        // Update distances of adjacent vertices of the picked vertex
        struct AdjListNode* temp = graph->array[u].head;
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;
            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    printSolution(dist, parent, src, numVertices);
}

int main() {
    int numVertices, numEdges;
    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter the edges (source destination weight):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest, weight;
        scanf("%d %d %d", &src, &dest, &weight);
        addEdge(graph, src, dest, weight);
    }

    int sourceVertex;
    printf("Enter the source vertex for Dijkstra's algorithm: ");
    scanf("%d", &sourceVertex);

    dijkstra(graph, sourceVertex);

}
