#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4

typedef struct Node {
    int puzzle[N][N];
    int x, y;
    int level;
    int cost;
    struct Node* parent;
} Node;

int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int manhattan(int p[N][N]) {
    int h = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (p[i][j]) {
                int tx = (p[i][j] - 1) / N;
                int ty = (p[i][j] - 1) % N;
                h += abs(i - tx) + abs(j - ty);
            }
    return h;
}

Node* createNode(int p[N][N], int x, int y, int newX, int newY, int lvl, Node* parent) {
    Node* n = malloc(sizeof(Node));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            n->puzzle[i][j] = p[i][j];
    n->puzzle[x][y] = n->puzzle[newX][newY];
    n->puzzle[newX][newY] = 0;
    n->x = newX;
    n->y = newY;
    n->level = lvl;
    n->cost = lvl + manhattan(n->puzzle);
    n->parent = parent;
    return n;
}

int isGoal(int p[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (p[i][j] != goal[i][j]) return 0;
    return 1;
}

void printPuzzle(int p[N][N]) {
    for (int i = 0; i < N; i++, puts(""))
        for (int j = 0; j < N; j++)
            printf("%d ", p[i][j]);
    puts("");
    printf("\n");
}

void printMoves(Node* n) {
    if (!n) return;
    printf("\n");
    printMoves(n->parent);
    printf("\n");
    printPuzzle(n->puzzle);
}

void solve(int initial[N][N], int x, int y) {
    Node* q[10000];
    int front = 0, rear = 0;
    Node* root = createNode(initial, x, y, x, y, 0, NULL);
    q[rear++] = root;
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

    while (front < rear) {
        int best = front;
        for (int i = front + 1; i < rear; i++)
            if (q[i]->cost < q[best]->cost) best = i;
        Node* temp = q[front]; q[front] = q[best]; q[best] = temp;

        Node* curr = q[front++];
        if (isGoal(curr->puzzle)) {
            printMoves(curr);
            printf("No of moves requird are %d\n", curr->level);
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nx = curr->x + dx[i], ny = curr->y + dy[i];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N)
                q[rear++] = createNode(curr->puzzle, curr->x, curr->y, nx, ny, curr->level + 1, curr);
        }
    }

    for (int i = 0; i < rear; i++) free(q[i]);
}

int main() {
    int a[N][N], x, y;
    printf("Enter the matrix\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            scanf("%d", &a[i][j]);
            if (a[i][j] == 0) x = i, y = j;
        }
    solve(a, x, y);
    return 0;
}



// 1 2 3 4
// 5 6 7 0
// 9 10 11 12
// 13 14 8 15