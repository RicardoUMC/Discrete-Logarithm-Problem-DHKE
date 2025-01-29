#include "../ecop/EC.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void mod_exp(mpz_t result, mpz_t base, mpz_t exp, mpz_t modular);
void brute_force_logarithm(mpz_t result, mpz_t g, mpz_t beta, mpz_t p);
void ec_brute_force_logarithm(mpz_t result, ec_point G, ec_point P, mpz_t p, mpz_t a, mpz_t b);

int main(void) {
    mpz_t p1[5], g[5], beta[5], x;
    mpz_inits(p1[0], p1[1], p1[2], p1[3], p1[4], g[0], g[1], g[2], g[3], g[4], beta[0], beta[1], beta[2], beta[3], beta[4], x, NULL);

    // Initialize values
    mpz_set_ui(p1[0], 10007);
    mpz_set_ui(p1[1], 100003);
    mpz_set_ui(p1[2], 100000000003);
    mpz_set_ui(p1[3], 500000009);
    mpz_set_ui(p1[4], 500000009);
    mpz_set_ui(g[0], 5);
    mpz_set_ui(g[1], 2);
    mpz_set_ui(g[2], 2);
    mpz_set_ui(g[3], 3);
    mpz_set_ui(g[4], 3);
    mpz_set_ui(beta[0], 9012);
    mpz_set_ui(beta[1], 100002);
    mpz_set_ui(beta[2], 1922556950);
    mpz_set_ui(beta[3], 406870124);
    mpz_set_ui(beta[4], 187776257);

    char* out_str;
    clock_t start, end;
    double cpu_time_used;
    for (int i = 0; i < 5; i++) {
        printf("Searching...\n");
        start = clock();
        brute_force_logarithm(x, g[i], beta[i], p1[i]);
        end = clock();
        cpu_time_used = (double) (end - start) / CLOCKS_PER_SEC;
        if (mpz_cmp_si(x, -1) != 0) {
            out_str = mpz_get_str(NULL, 10, x);
            printf("Solution for %s^x ≡ %s (mod %s): x = %s\n", mpz_get_str(NULL, 10, g[i]), mpz_get_str(NULL, 10, beta[i]), mpz_get_str(NULL, 10, p1[i]), out_str);
            printf("Logarithm found in %f seconds\n", cpu_time_used);
            free(out_str);
        } else {
            printf("No solution found for %s^x ≡ %s (mod %s)\n", mpz_get_str(NULL, 10, g[i]), mpz_get_str(NULL, 10, beta[i]), mpz_get_str(NULL, 10, p1[i]));
        }
        printf("\n");
    }

    // Clean up
    for (int i = 0; i < 5; i++) {
        mpz_clears(p1[i], g[i], beta[i], NULL);
    }
    mpz_clear(x);

    mpz_t p[5], a[5], b[5];
    ec_point G[5], P[5];

    // Inicializa los valores de p, a, b, G y P según los ejemplos proporcionados
    const char *p_vals[] = {"113", "503", "5009", "1000003", "500000009"};
    const char *a_vals[] = {"1", "11", "1", "1000", "1"};
    const char *b_vals[] = {"9", "1", "1", "1", "9"};
    const char *g_vals[][3] = {{"47", "22", "1"}, {"457", "404", "1"}, {"359", "1928", "1"}, {"917459", "678095", "1"}, {"377863415", "222914743", "1"}};
    const char *p_vals_points[][3] = {{"52", "53", "1"}, {"459", "58", "1"}, {"1942", "2938", "1"}, {"798677", "191330", "1"}, {"477613302", "314579681", "1"}};

    // Inicializa valores de p, a, b, y los puntos G y P
    for (int i = 0; i < 5; i++) {
        mpz_inits(p[i], a[i], b[i], NULL);
        mpz_set_str(p[i], p_vals[i], 10);
        mpz_set_str(a[i], a_vals[i], 10);
        mpz_set_str(b[i], b_vals[i], 10);

        // Inicializa el punto generador G
        mpz_inits(G[i].x, G[i].y, NULL);
        mpz_set_str(G[i].x, g_vals[i][0], 10);
        mpz_set_str(G[i].y, g_vals[i][1], 10);
        G[i].z = atoi(g_vals[i][2]);

        // Inicializa el punto P
        mpz_inits(P[i].x, P[i].y, NULL);
        mpz_set_str(P[i].x, p_vals_points[i][0], 10);
        mpz_set_str(P[i].y, p_vals_points[i][1], 10);
        P[i].z = atoi(p_vals_points[i][2]);
    }

    // Realiza la búsqueda de logaritmos discretos para cada curva
    for (int i = 0; i < 5; i++) {
        printf("Searching in curve E(%s, %s) over GF(%s)...\n", mpz_get_str(NULL, 10, a[i]), mpz_get_str(NULL, 10, b[i]), mpz_get_str(NULL, 10, p[i]));

        start = clock();
        ec_brute_force_logarithm(x, G[i], P[i], p[i], a[i], b[i]);  // Buscar el logaritmo discreto
        end = clock();

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

        if (mpz_cmp_si(x, -1) != 0) {
            gmp_printf("Solution for xG(%Zd:%Zd:%d) = P(%Zd:%Zd:%d): x = %Zd\n", G[i].x, G[i].y, G[i].z, P[i].x, P[i].y, P[i].z, x, cpu_time_used);
            gmp_printf("Logarithm found in %f seconds\n", x, cpu_time_used);
        } else {
            printf("No solution found.\n");
        }
        printf("\n");
    }

    // Limpieza de memoria
    for (int i = 0; i < 5; i++) {
        mpz_clears(p[i], a[i], b[i], G[i].x, G[i].y, P[i].x, P[i].y, NULL);
    }
    mpz_clear(x);

    return 0;
}

void mod_exp(mpz_t result, mpz_t base, mpz_t exp, mpz_t modular) {
    mpz_t temp_result;
    mpz_init(temp_result);
    mpz_mod(base, base, modular);
    mpz_set(temp_result, base);

    mpz_t pow;
    mpz_init_set_ui(pow, 1);

    while (mpz_cmp(pow, exp) < 0) {
        mpz_mul(temp_result, temp_result, base);
        mpz_mod(temp_result, temp_result, modular);
        mpz_add_ui(pow, pow, 1);
    }

    mpz_set(result, temp_result);

    mpz_clears(temp_result, pow, NULL);
}

void brute_force_logarithm(mpz_t result, mpz_t g, mpz_t beta, mpz_t p) {
    mpz_t i;
    mpz_t temp_result;
    mpz_inits(i, temp_result, NULL);
    mpz_set_ui(result, 0);
    mpz_set_ui(i, 1);

    mpz_mod(g, g, p);
    mpz_set_ui(temp_result, 1);

    while (mpz_cmp(i, p) < 0) {
        mpz_mul(temp_result, temp_result, g);
        mpz_mod(temp_result, temp_result, p);

        gmp_printf("exp = %Zd\n", temp_result);
        if (mpz_cmp(temp_result, beta) == 0) {
            mpz_set(result, i);
            mpz_clears(i, temp_result, NULL);
            return;
        }
        mpz_add_ui(i, i, 1);
    }

    mpz_set_si(result, -1);
    mpz_clears(i, temp_result, NULL);
}

void ec_brute_force_logarithm(mpz_t result, ec_point G, ec_point P, mpz_t p, mpz_t a, mpz_t b) {
    ec_point R;
    mpz_t i;
    mpz_init_set_ui(i, 1);
    R = G;
    
    while (mpz_cmp(i, p) <= 0) {
        if (mpz_cmp_si(R.x, -1) == 0) break;
        if (mpz_cmp(R.x, P.x) == 0 && mpz_cmp(R.y, P.y) == 0) {
            mpz_set(result, i);
            mpz_clear(i);
            return;
        }
        R = point_addition(a, b, p, R, G);
        mpz_add_ui(i, i, 1);
    }

    mpz_set_si(result, -1);
    mpz_clear(i);
}

