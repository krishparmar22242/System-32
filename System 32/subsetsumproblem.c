#include <stdio.h>
#include<time.h>
#define MAX 100

int subset[MAX], count = 0;

void subsetSum(int arr[], int n, int index, int target, int sum, int pos)
{
    if (sum == target)
    {
        printf("Subset %d: ", ++count);
        for (int i = 0; i < pos; i++)
            printf("%d ", subset[i]);
        printf("\n");
        return;
    }

    for (int i = index; i < n; i++)
    {
        if (sum + arr[i] <= target)
        {
            subset[pos] = arr[i];
            subsetSum(arr, n, i + 1, target, sum + arr[i], pos + 1);
        }
    }
}
int main()
{
    int arr1[] = {10, 7, 5, 18, 12, 20, 15};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    int target = 35;
    clock_t start =clock();
    printf("Subsets with sum %d:\n", target);
    subsetSum(arr1, n, 0, target, 0, 0);
    if (count == 0)
    printf("No subsets found.\n");
    clock_t end=clock();
    double time=((double)(end-start))/CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time);
    
    return 0;
}