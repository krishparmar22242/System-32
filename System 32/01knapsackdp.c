#include <stdio.h>
#include <time.h>

#define MAX 100

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Dynamic Programming implementation of 0/1 Knapsack
int knapsack(int W, int wt[], int val[], int n)
{
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int main()
{
    int n, W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    int val[n], wt[n];

    printf("Enter the values of the %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &val[i]);

    printf("Enter the weights of the %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &wt[i]);

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &W);

    clock_t start = clock();  // Start timing

    printf("\nItems (value, weight):\n");
    for (int i = 0; i < n; i++)
        printf("Item %d: (%d, %d)\n", i + 1, val[i], wt[i]);

    int maxVal = knapsack(W, wt, val, n);

    printf("\nMaximum value that can be taken = %d\n", maxVal);
    clock_t end = clock();    // End timing

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken to compute: %f seconds\n", time_taken);

    return 0;
}



// 4

// 60 10
// 100 20
// 120 30
// 80 40

// 50