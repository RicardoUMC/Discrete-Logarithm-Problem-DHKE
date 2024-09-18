#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int mod(int number, int modular);
int mod_exp(int base, int exp, int modular);
int brute_force_logarithm(int g, int beta, int p);

int main(void) {
    int p[] = {10007, 100003, 1000000003, 500000009, 500000009};
    int g[] = {5, 2, 2, 3, 3};
    int beta[] = {9012, 100002, 1922556950, 406870124, 187776257};
    
    for (int i = 0; i < 5; i++) {
        int x = brute_force_logarithm(g[i], beta[i], p[i]);
        if (x != -1) {
            printf("Solution for %d^x ≡ %d (mod %d): x = %d\n", g[i], beta[i], p[i], x);
        } else {
            printf("No solution found for %d^x ≡ %d (mod %d)\n", g[i], beta[i], p[i]);
        }
    }

    return 0;
}

int mod(int number, int modular) {
    return (number % modular + modular) % modular;
}

int mod_exp(int base, int exp, int modular) {
    base = mod(base, modular);
    int result = base;
    int pow = 2;
    while (pow <= exp) {
        result = mod(result * base, modular);
        pow++;
    }
    return result;
}

int brute_force_logarithm(int g, int beta, int p) {
    for (int i = 0; i < p; i++) {
        if (mod_exp(g, i, p) == beta) return i; 
    }
    return -1;
}
