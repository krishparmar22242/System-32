#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int universe[MAX];          
int covered[MAX];            
int subsets[MAX][MAX];       
int subsetSize[MAX];         
int selected[MAX];        

int n, m; 
int countUncovered(int set[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (!covered[set[i]]) {
            count++;
        }
    }
    return count;
}

void markCovered(int set[], int size) {
    for (int i = 0; i < size; i++) {
        covered[set[i]] = 1;
    }
}

int allCovered() {
    for (int i = 0; i < n; i++) {
        if (!covered[universe[i]]) {
            return 0;
        }
    }
    return 1;
}

void greedySetCover() {
    int setsUsed = 0;

    while (!allCovered()) {
        int bestSet = -1;
        int maxCover = -1;

        for (int i = 0; i < m; i++) {
            if (!selected[i]) {
                int count = countUncovered(subsets[i], subsetSize[i]);
                if (count > maxCover) {
                    maxCover = count;
                    bestSet = i;
                }
            }
        }

        if (bestSet == -1) break; 

        selected[bestSet] = 1;
        markCovered(subsets[bestSet], subsetSize[bestSet]);
        setsUsed++;

        printf("Selected Subset %d: { ", bestSet + 1);
        for (int i = 0; i < subsetSize[bestSet]; i++) {
            printf("%d ", subsets[bestSet][i]);
        }
        printf("}\n");
    }

    printf("Total subsets used in approximation: %d\n", setsUsed);
}

int main() {
    printf("Enter size of universal set: ");
    scanf("%d", &n);

    printf("Enter elements of universal set:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &universe[i]);
        covered[universe[i]] = 0;
    }

    printf("Enter number of subsets: ");
    scanf("%d", &m);

    for (int i = 0; i < m; i++) {
        printf("Enter size of subset %d: ", i + 1);
        scanf("%d", &subsetSize[i]);
        printf("Enter elements of subset %d:\n", i + 1);
        for (int j = 0; j < subsetSize[i]; j++) {
            scanf("%d", &subsets[i][j]);
        }
        selected[i] = 0;
    }

    clock_t start = clock();
    greedySetCover();
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}






// Enter size of universal set: 6 
// Enter elements of universal set:
// 0 1 2 3 4 5
// Enter number of subsets: 4
// Enter size of subset 1: 3
// Enter elements of subset 1:
// 0 1 2
// Enter size of subset 2: 2
// Enter elements of subset 2:
// 3 4 
// Enter size of subset 3: 2
// Enter elements of subset 3:
// 2 5
// Enter size of subset 4: 3
// Enter elements of subset 4:
// 4 5 1
// Selected Subset 1: { 0 1 2 }
// Selected Subset 2: { 3 4 }
// Selected Subset 3: { 2 5 }
// Total subsets used in approximation: 3
