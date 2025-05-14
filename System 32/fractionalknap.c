#include <stdio.h>
#include <time.h>

#define MAX_ITEMS 1000

void sortByRatio(float values[], int weights[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            float ratio1 = values[j] / weights[j];
            float ratio2 = values[j + 1] / weights[j + 1];
            if (ratio1 < ratio2)
            {
                float tempVal = values[j];
                values[j] = values[j + 1];
                values[j + 1] = tempVal;

                int tempWt = weights[j];
                weights[j] = weights[j + 1];
                weights[j + 1] = tempWt;
            }
        }
    }
}

void displayItems(float values[], int weights[], int n)
{
    printf("\nSorted Items by Value/Weight Ratio:\n");
    printf("Item\tValue\tWeight\tValue/Weight\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%.2f\t%d\t%.2f\n", i + 1, values[i], weights[i], values[i] / weights[i]);
    }
}

float fractionalKnapsack(float values[], int weights[], int n, int capacity)
{
    float totalProfit = 0.0;

    for (int i = 0; i < n; i++)
    {
        if (weights[i] <= capacity)
        {
            totalProfit += values[i];
            capacity -= weights[i];
        }
        else
        {
            totalProfit += values[i] * ((float)capacity / weights[i]);
            break;
        }
    }
    return totalProfit;
}

int main()
{
    int n, capacity;
    float values[MAX_ITEMS];
    int weights[MAX_ITEMS];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter the values of %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%f", &values[i]);

    printf("Enter the weights of %d items:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);

    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &capacity);

    clock_t start = clock();
    sortByRatio(values, weights, n);               
    displayItems(values, weights, n);              
    float profit = fractionalKnapsack(values, weights, n, capacity);  
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTotal Profit: %.2f\n", profit);
    printf("Time taken to compute: %f seconds\n", time_taken);

    return 0;
}



// 60 100 120 70 90
// 10 20 30 15 18
// 50
