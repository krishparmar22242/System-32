#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int graph[MAX][MAX];   
int visited[MAX];      
int n, e;              

void vertexCoverApprox()
{
    int cover[MAX] = {0}; 

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (int u = 0; u < n; u++)
    {
        if (!visited[u])
        {
            for (int v = 0; v < n; v++)
            {
                if (graph[u][v] && !visited[v])
                {
                    visited[u] = 1;
                    visited[v] = 1;

                    cover[u] = 1;
                    cover[v] = 1;
                    break;  
                }
            }
        }
    }

    int cover_size = 0;
    for (int i = 0; i < n; i++) {
        if (cover[i]) cover_size++;
    }

    printf("Approximate Vertex Cover (Size: %d):\n", cover_size);
    for (int i = 0; i < n; i++)
    {
        if (cover[i])
            printf("%d ", i);
    }
    printf("\n");
}

int main()
{
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
        for (int j = 0; j < MAX; j++) {
            graph[i][j] = 0;
        }
    }
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    printf("Enter the edges (u v):\n");
    for (int i = 0; i < e; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1; 
    }

    clock_t start = clock();
    vertexCoverApprox(); 
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}



// Enter number of vertices and edges: 8 7
// Enter the edges (u v):
// 1 4
// 1 2
// 2 3
// 2 5
// 5 6
// 3 6
// 3 7
// Approximate Vertex Cover (Size: 4):
// 1 2 3 6