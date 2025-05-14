#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100

int minDistance(int dist[], int sptSet[], int V)
{
    int min = INT_MAX;
    int min_index = -1;
    for (int v = 0; v < V; v++)
    {
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int V, int src)
{
    int dist[MAX];
    int sptSet[MAX];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet, V);
        if (u == -1) 
        break; 
        sptSet[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nVertex \tDistance from Source %d\n", src);
    for (int i = 0; i < V; i++)
    {
        if (dist[i] == INT_MAX)
            printf("%d \tINF\n", i);
        else
            printf("%d \t%d\n", i, dist[i]);
    }
}

int main()
{
    int V, graph[MAX][MAX], source;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter the adjacency matrix (%d x %d):\n", V, V);
    printf("(Enter 0 if no edge between two vertices)\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter source vertex (0 to %d): ", V - 1);
    scanf("%d", &source);

    clock_t start = clock();

    dijkstra(graph, V, source);

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime taken: %f seconds\n", time_taken);

    return 0;
}



// Enter number of vertices: 5
// Enter the adjacency matrix:
// 0 10 0 0 0
// 10 0 20 0 0
// 0 20 0 10 0
// 0 0 10 0 5
// 0 0 0 5 0
// Enter source vertex: 0