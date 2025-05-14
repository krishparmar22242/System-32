#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct {
    int weight;
    int profit;
    float ratio;
} Item;

typedef struct {
    int level;
    int profit;
    int weight;
    float bound;
    int taken[MAX]; 
} Node;

int n, capacity;
Item items[MAX];
int bestItems[MAX]; 
int cmp(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    return (item2->ratio > item1->ratio) ? 1 : -1;
}

float bound(Node u) {
    if (u.weight >= capacity) return 0;

    float profit_bound = u.profit;
    int j = u.level + 1, totweight = u.weight;

    while (j < n && totweight + items[j].weight <= capacity) {
        totweight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n){
        profit_bound += (capacity - totweight) * items[j].ratio;
    }
    return profit_bound;
}

void knapsack() {
    Node u, v;
    int maxProfit = 0;

    v.level = -1;
    v.profit = 0;
    v.weight = 0;
    v.bound = bound(v);
    for (int i = 0; i < n; i++) v.taken[i] = 0;

    Node queue[MAX];
    int front = 0, rear = 0;
    queue[rear++] = v;

    while (front < rear) {
        v = queue[front++];

        if (v.level == n - 1) continue;

        u = v;
        u.level = v.level + 1;
        u.weight += items[u.level].weight;
        u.profit += items[u.level].profit;
        u.taken[u.level] = 1;

        if (u.weight <= capacity && u.profit > maxProfit) 
        {
            maxProfit = u.profit;
            for (int i = 0; i < n; i++) 
            {
                bestItems[i] = u.taken[i];
            }
        }

        u.bound = bound(u);
        if (u.bound > maxProfit) 
        {
            queue[rear++] = u;
        }

        u = v;
        u.level = v.level + 1;
        u.taken[u.level] = 0;
        u.bound = bound(u);
        if (u.bound > maxProfit) 
        {
            queue[rear++] = u;
        }
    }
    printf("\nMaximum Profit = %d\n", maxProfit);
    printf("Items included (1 = Yes, 0 = No):\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d (Weight = %d, Profit = %d): %d\n",
               i + 1, items[i].weight, items[i].profit, bestItems[i]);
    }
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter knapsack capacity: ");
    scanf("%d", &capacity);

    printf("Enter weight and profit of each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &items[i].weight, &items[i].profit);
        items[i].ratio = (float)items[i].profit / items[i].weight;
    }

    clock_t start=clock();
    qsort(items, n, sizeof(Item), cmp);

    knapsack();
    clock_t end=clock();
    double time_spent=(double)(end-start)/CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}


// Enter number of items and knapsack capacity: 4 15
// Enter weight and profit of each item:
// 2 40
// 3 50
// 5 100
// 7 60