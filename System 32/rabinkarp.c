#include <stdio.h>
#include <string.h>
#include <time.h>

#define d 256 
#define q 101 

void rabinKarp(char *text, char *pattern)
{
    int M = strlen(pattern);
    int N = strlen(text);
    int i, j;
    int patternHash = 0; 
    int textHash = 0;    
    int h = 1;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++)
    {
        patternHash = (d * patternHash + pattern[i]) % q;
        textHash = (d * textHash + text[i]) % q;
    }

    for (i = 0; i <= N - M; i++)
    {
        if (patternHash == textHash)
        {
            for (j = 0; j < M; j++)
            {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == M)
                printf("Pattern found at index %d\n", i);
        }

        if (i < N - M)
        {
            textHash = (d * (textHash - text[i] * h) + text[i + M]) % q;

            if (textHash < 0)
                textHash = (textHash + q);
        }
    }
}

int main()
{
    char text[] = "ABABABACDABABCABAB";
    char pattern[] = "ABABCABAB";
    clock_t start=clock();
    rabinKarp(text, pattern);
    clock_t end=clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_spent);
    return 0;
}