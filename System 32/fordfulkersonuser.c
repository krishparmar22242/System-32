#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX_V 100

int dfs(int graph[MAX_V][MAX_V], int V, int s, int t, int parent[], int visited[]) {
    visited[s] = 1;
    if (s == t) return 1;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && graph[s][v] > 0) {
            parent[v] = s;
            if (dfs(graph, V, v, t, parent, visited))
                return 1;
        }
    }
    return 0;
}

int fordFulkerson(int graph[MAX_V][MAX_V], int V, int s, int t) {
    int parent[MAX_V];
    int maxFlow = 0;
    int step = 1;

    while (1) {
        int visited[MAX_V] = {0};
        if (!dfs(graph, V, s, t, parent, visited))
            break;

        int bottleneck = INT_MAX;
        printf("Step %d: Augmenting path found: ", step);
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (graph[u][v] < bottleneck)
                bottleneck = graph[u][v];
            printf("%d <- ", v);
        }
        printf("%d\n", s);
        printf("Minimum capacity along the path: %d\n", bottleneck);

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            graph[u][v] -= bottleneck;
            graph[v][u] += bottleneck;
        }

        maxFlow += bottleneck;
        step++;
    }

    return maxFlow;
}

int main() {
    int V, E;
    int graph[MAX_V][MAX_V] = {0};

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (from to capacity):\n");
    for (int i = 0; i < E; i++) {
        int u, v, cap;
        scanf("%d %d %d", &u, &v, &cap);
        graph[u][v] = cap;
    }

    int source, sink;
    printf("Enter source vertex: ");
    scanf("%d", &source);
    printf("Enter sink vertex: ");
    scanf("%d", &sink);

    clock_t start = clock();

    printf("Initial Residual Graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int maxFlow = fordFulkerson(graph, V, source, sink);

    clock_t end = clock();
    printf("\nThe maximum possible flow is: %d\n", maxFlow);
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}



// Enter number of vertices: 6 
// Enter number of edges: 9
// Enter edges (from to capacity):
// 0 1 16
// 0 2 13
// 1 2 10
// 1 3 12
// 2 1 4
// 2 4 14
// 3 2 9
// 4 3 7
// 3 5 20
// Enter source vertex: 0
// Enter sink vertex: 5
// Initial Residual Graph:
//  0 16 13  0  0  0
//  0  0 10 12  0  0
//  0  4  0  0 14  0
//  0  0  9  0  0 20
//  0  0  0  7  0  0
//  0  0  0  0  0  0

// Step 1: Augmenting path found: 5 <- 3 <- 4 <- 2 <- 1 <- 0
// Minimum capacity along the path: 7
// Step 2: Augmenting path found: 5 <- 3 <- 1 <- 0
// Minimum capacity along the path: 9
// Step 3: Augmenting path found: 5 <- 3 <- 1 <- 2 <- 0
// Minimum capacity along the path: 3

// The maximum possible flow is: 19