#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 6 

int dfs(int graph[V][V], int s, int t, int parent[], int visited[]) {
    visited[s] = 1;

    if (s == t) 
    {
        return 1; 
    }
    for (int v = 0; v < V; v++) {
        if (!visited[v] && graph[s][v] > 0) {
            parent[v] = s;
            if (dfs(graph, v, t, parent, visited)) 
            {
                return 1;
            }
        }
    }
    return 0; 
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int parent[V];
    int maxFlow = 0;

    int step = 1;
    while (1) {
        int visited[V] = {0}; 
        if (!dfs(graph, s, t, parent, visited))
            break; 

        int bottleneck = INT_MAX;
        printf("Step %d: Augmenting path found: ", step);
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (graph[u][v] < bottleneck)
            {
                bottleneck = graph[u][v];
            }
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
    int graph[V][V] = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0}
    };
    int source = 0, sink = 5;
    clock_t start = clock();
    printf("Initial Residual Graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%2d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int maxFlow = fordFulkerson(graph, source, sink);
    clock_t end = clock();
    printf("\nThe maximum possible flow is: %d\n", maxFlow);
    printf("Time taken: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
