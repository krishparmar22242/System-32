#include <stdio.h>
#include <limits.h>
#include<time.h>

#define MAX_VERTICES 20

void bellmanFord(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices, int source)
{
    int dist[MAX_VERTICES], parent[MAX_VERTICES];
    int i, j, k;

    for (i = 0; i < numVertices; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (k = 0; k < numVertices - 1; k++)
    {
        for (i = 0; i < numVertices; i++)
        {
            for (j = 0; j < numVertices; j++)
            {
                if (graph[i][j] != 0 && dist[i] != INT_MAX && dist[i] + graph[i][j] < dist[j])
                {
                    dist[j] = dist[i] + graph[i][j];
                    parent[j] = i; 
                }
            }
        }
    }

    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
        {
            if (graph[i][j] != 0 && dist[i] != INT_MAX && dist[i] + graph[i][j] < dist[j])
            {
                printf("Graph contains a negative-weight cycle!\n");
                return;
            }
        }
    }

    printf("\nVertex \tDistance from Source %d\n", source);
    for (int i = 0; i < numVertices; i++)
    {
        printf("%d \t%d\n", i, dist[i]);
    }

    printf("\nShortest paths:\n");
    for (i = 0; i < numVertices; i++)
    {
        if (dist[i] != INT_MAX)
        {
            printf("Path to vertex %d: ", i);
            int current = i;
            while (current != -1)
            {
                printf("%d ", current);
                current = parent[current];
            }
            printf("\n");
        }
    }
}

int main()
{
    int graph[MAX_VERTICES][MAX_VERTICES];
    int numVertices, source, i, j;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter the adjacency matrix (use 0 for no edge):\n");
    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the source vertex: ");
    scanf("%d", &source);

    clock_t start = clock();
    bellmanFord(graph, numVertices, source);
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}



// 0 10 0 0 0
// 10 0 20 0 0
// 0 20 0 10 0
// 0 0 10 0 5
// 0 0 0 5 0