#include <stdio.h>
#include <stdbool.h>
#include<time.h>

#define N 5 

bool bpm(bool bpGraph[N][N], int u, bool seen[], int matchTo[]) {
    for (int v = 0; v < N; v++) {
        if (bpGraph[u][v] && !seen[v]) {
            seen[v] = true;
            if (matchTo[v] == -1 || bpm(bpGraph, matchTo[v], seen, matchTo)) {
                matchTo[v] = u; 
                return true;
            }
        }
    }
    return false;
}

int maxBPM(bool bpGraph[N][N]) {
    int matchTo[N]; 
    for (int i = 0; i < N; i++) {
        matchTo[i] = -1; 
    }

    int result = 0; 

    for (int u = 0; u < N; u++) 
    {
        bool seen[N]; 
        for (int i = 0; i < N; i++) 
        {
            seen[i] = false; 
        }
        if (bpm(bpGraph, u, seen, matchTo)) {
            result++; 
            printf("Intermediate Matching after vertex U%d:\n", u + 1);
            for (int i = 0; i < N; i++) 
            {
                if (matchTo[i] != -1) 
                {
                    printf("U%d -> V%d\n", matchTo[i] + 1, i + 1);
                }
            }
            printf("\n");
        }
    }

    printf("Final Maximum Matching:\n");
    for (int i = 0; i < N; i++) {
        if (matchTo[i] != -1) {
            printf("U%d -> V%d\n", matchTo[i] + 1, i + 1);
        }
    }
    return result;
}

int main() {
    bool bpGraph[N][N] = {
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1}
    };
    clock_t start=clock();
    int maxMatches = maxBPM(bpGraph);
    clock_t end=clock();
    double time_spent=(double)(end-start)/CLOCKS_PER_SEC;
    printf("\nMaximum number of matching: %d\n", maxMatches);
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}
