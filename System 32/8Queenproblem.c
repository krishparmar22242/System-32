#include <stdio.h>
#include <stdbool.h>
#include<time.h>

#define N 4

int count = 0;

void print(int board[N][N]) 
{
    printf("Solution %d:\n", ++count);
    for (int i = 0; i < N; i++) {                   
        for (int j = 0; j < N; j++) {               
            printf(" %c ", board[i][j] ? 'Q' : '.'); 
        }
        printf("\n");                               
    }
    puts("--------------------------\n");
}

bool isSafe(int board[N][N], int row, int col) {
    for (int i = 0; i < col; i++)
    {
        if (board[row][i]) 
        {
            return false;
        }

    }
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j]) 
        {
            return false;
        }
    }
    for (int i = row, j = col; i < N && j >= 0; i++, j--)
    {
        if (board[i][j]) 
        {
            return false;
        }
    }
    return true;
}

bool solve(int board[N][N], int col) 
{
    if (col == N) 
    { 
        print(board); 
        return true; 
    }

    bool res = false;
    for (int i = 0; i < N; i++) 
    {
        if (isSafe(board, i, col)) 
        {
            board[i][col] = 1;
            res = solve(board, col + 1);
            board[i][col] = 0;
        }
    }
    return res;
    
}

int main() {
    int board[N][N] = {0};
    clock_t start=clock();
    printf("Solving %d-Queens Problem...\n\n", N);
    solve(board, 0);
    if (!count) 
    {
        puts("No solution exists.");
    }
    else 
    {
        printf("Found %d solution(s).\n", count);
    }
    clock_t end=clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);
    return 0;
}
