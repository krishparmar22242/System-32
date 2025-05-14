#include <stdio.h>
#include <limits.h>
#include <time.h>

#define V 100  

int minKey(int key[], int mstSet[], int vertices)
{
    int min = INT_MAX;
    int minIndex;

    for (int v = 0; v < vertices; v++)
        if (!mstSet[v] && key[v] < min)
            {
                min = key[v] ;
                minIndex = v;
            }
    return minIndex;
}

int primMST(int graph[V][V], int vertices)
{
    int parent[V];         
    int key[V];            
    int mstSet[V];         

    for (int i = 0; i < vertices; i++)
        {
            key[i] = INT_MAX; 
            mstSet[i] = 0;
        }

    key[0] = 0;             
    parent[0] = -1;         

    for (int count = 0; count < vertices - 1; count++)
    {
        int u = minKey(key, mstSet, vertices); 
        mstSet[u] = 1;                          

        for (int v = 0; v < vertices; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int totalCost = 0;
    printf("\nEdge \tWeight\n");
    for (int i = 1; i < vertices; i++)
    {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }

    return totalCost;
}

int main()
{
    int graph[V][V];
    int vertices;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix (%dx%d):\n", vertices, vertices);
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    clock_t start = clock(); 

    int totalCost = primMST(graph, vertices); 

    clock_t end = clock();   
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTotal Minimum Cost of MST: %d\n", totalCost);
    printf("Time taken to compute MST: %f seconds\n", time_taken);

    return 0;
}


// 5

// 0 2 0 6 0
// 2 0 3 8 5
// 0 3 0 0 7
// 6 8 0 0 9
// 0 5 7 9 0