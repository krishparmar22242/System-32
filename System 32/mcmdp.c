#include <stdio.h>  
#include <limits.h> 
#include<time.h>
void printOptimalParenthesis(int i, int j, int n, int s[n + 1][n + 1]) {
    if (i == j) {  
        printf("A%d", i);
    } else {
        printf("(");  

        printOptimalParenthesis(i, s[i][j], n, s);

        printOptimalParenthesis(s[i][j] + 1, j, n, s);
        printf(")");  
    }
}

void matrixChainOrder(int p[], int n, int m[n + 1][n + 1], int s[n + 1][n + 1]) {

    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; l++) {
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;  
            m[i][j] = INT_MAX;  

            for (int k = i; k < j; k++) {

                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k; 
                }
            }
        }
    }
}

void printMatrix(int n, int m[n + 1][n + 1]) {
    printf("Matrix Multiplication Cost Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i <= j) 
                printf("%d\t", m[i][j]);
            else 
                printf("0\t");
        }
        printf("\n"); 
    }
}

void printKTable(int n, int s[n + 1][n + 1]) {
    printf("Optimal Split Points (k) Table:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i < j) 
                printf("%d\t", s[i][j]);
            else 
                printf("0\t");
        }
        printf("\n"); 
    }
}

void printMatrixChainOrder(int p[], int n) {
    int m[n + 1][n + 1]; 
    int s[n + 1][n + 1]; 

    matrixChainOrder(p, n, m, s); 

    
    printf("Optimal Parenthesization is: ");
    printOptimalParenthesis(1, n, n, s); 
    printf("\n");
    
    printMatrix(n, m); 
    printKTable(n, s); 
    printf("Minimum number of multiplications is %d\n", m[1][n]); 
}

int main() {
    int n; 
    printf("Enter the number of matrices: ");
    scanf("%d", &n); 

    int p[n + 1]; 
    printf("Enter the dimensions of the matrices (p[0] to p[%d]):\n", n);
    for (int i = 0; i <= n; i++) {
        scanf("%d", &p[i]); 
    }
    clock_t start = clock();  // Start timing
    printMatrixChainOrder(p, n); 
    clock_t end = clock();    // End timing
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}


//  4

// 40
// 20
// 30
// 10
// 30
