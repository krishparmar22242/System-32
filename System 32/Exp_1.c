#include <stdio.h>
#include <math.h>

// n^3
float ncube(float n) {
    return pow(n, 3);
}

// 2^n
float twopowern(float n) {
    return pow(2, n);
}

// lg n
float logn(float n) {
    if (n > 0) {
        return log(n);
    } else {
        return NAN; 
    }
}

// e^n
float exppowern(float n) {
    return exp(n);
}

// log2n 
float log2n(float n) {
    if (n > 0) {
        return log2(n);
    } else {
        return NAN;
    }
}

// lglg n 
float loglogn(float n) {
    if (n > 1) {
        return log2(log2(n));
    } else {
        return NAN;
    }
}

// n*2^n
float npower2ofn(float n) {
    return n * pow(2, n); 
}

// n^(loglogn)
float npowerloglogn(float n) {
    if (n > 1) {
        return pow(n, log2(log2(n)));
    } else {
        return NAN;
    }
}

// n * log(n)
float nlogn(float n) {
    if (n > 0) {
        return n * log(n);
    } else {
        return NAN;
    }
}

// (3/2)^n
float threebytwopowern(float n) {
    return pow(1.5, n);
}

// n! (factorial)
float nfact(float n) {
    if (n < 0) {
        return NAN; 
    } else if (n == 0 || n == 1) {
        return 1;
    } else {
        float fact = 1;
        for (int i = 1; i <= n; i++) {
            fact *= i;
        }
        return fact;
    }
}

int main() {
    int i;
    printf("%2s %9s %9s %9s %9s %9s %9s %9s %15s %9s %12s %15s\n", 
           "n", "n^3", "2^n", "lg n", "e^n", "log2n", "lglg n", "n*2^n", "npowerloglogn", "nlogn", "(3/2)^n", "n!");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 1; i <= 100; i++) {
        float nValue = i;
        printf("%2d %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %15.2f %9.2f %12.2f %15.2f\n",
               i,
               ncube(nValue),
               twopowern(nValue),
               logn(nValue),
               exppowern(nValue),
               log2n(nValue),
               loglogn(nValue),
               npower2ofn(nValue),
               npowerloglogn(nValue),
               nlogn(nValue),
               threebytwopowern(nValue),
               nfact(nValue));
    }

    return 0;
}




