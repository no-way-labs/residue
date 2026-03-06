/*
 * verify_fast.c — Fast Hamiltonian decomposition verifier for Z_m^3.
 *
 * Round-map verification: for each color c, compose the m layer
 * permutations on Z_m^2 and check that the result is a single m^2-cycle.
 *
 * Usage:
 *   cc -O2 -o verify_fast verify_fast.c
 *   ./verify_fast              # verify m=3..2001
 *   ./verify_fast 5000         # verify m=3..5000
 *   ./verify_fast -m 42        # verify single m
 *
 * Ports odd_construction.py and even_construction.py to C with
 * repeated-squaring permutation composition.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* --- Permutation utilities on Z_m^2 (encoded as x*m+y) --- */

static int *perm_alloc(int n) {
    return (int *)malloc(n * sizeof(int));
}

/* dst[i] = b[a[i]] */
static void perm_compose(int *dst, const int *a, const int *b, int n) {
    for (int i = 0; i < n; i++)
        dst[i] = b[a[i]];
}

/* dst = src^exp via repeated squaring */
static void perm_power(int *dst, const int *src, int exp, int n) {
    /* identity */
    for (int i = 0; i < n; i++) dst[i] = i;
    int *base = perm_alloc(n);
    int *tmp = perm_alloc(n);
    memcpy(base, src, n * sizeof(int));
    while (exp > 0) {
        if (exp & 1) {
            perm_compose(tmp, dst, base, n);
            memcpy(dst, tmp, n * sizeof(int));
        }
        perm_compose(tmp, base, base, n);
        memcpy(base, tmp, n * sizeof(int));
        exp >>= 1;
    }
    free(base);
    free(tmp);
}

/* Check if perm is a single n-cycle */
static int is_single_cycle(const int *perm, int n) {
    int v = 0;
    for (int i = 1; i < n; i++) {
        v = perm[v];
        if (v == 0) return 0;  /* returned early */
    }
    return (perm[v] == 0);
}

/* --- GCD --- */
static int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

/* --- Direction enum --- */
enum { D_I = 0, D_X = 1, D_Y = 2 };

/* Build matching A on Z_m^2: X off diagonal, Y on diagonal */
static void build_match_A(int *perm, int m) {
    for (int x = 0; x < m; x++)
        for (int y = 0; y < m; y++) {
            int on_diag = ((x + y) % m == 0);
            if (on_diag)
                perm[x * m + y] = x * m + ((y + 1) % m);       /* Y */
            else
                perm[x * m + y] = ((x + 1) % m) * m + y;       /* X */
        }
}

/* Build matching B on Z_m^2: Y off diagonal, X on diagonal */
static void build_match_B(int *perm, int m) {
    for (int x = 0; x < m; x++)
        for (int y = 0; y < m; y++) {
            int on_diag = ((x + y) % m == 0);
            if (on_diag)
                perm[x * m + y] = ((x + 1) % m) * m + y;       /* X */
            else
                perm[x * m + y] = x * m + ((y + 1) % m);       /* Y */
        }
}

/* Build identity matching I: (x,y)->(x,y) — but actually I means
   the k-coordinate advances, so in the round map, I is the identity
   on (x,y) */
static void build_match_I(int *perm, int m) {
    for (int i = 0; i < m * m; i++) perm[i] = i;
}

/* --- Odd case verification --- */

static int choose_s_odd(int m) {
    for (int s = 1; s < m; s += 2)
        if (gcd(s, m) == 1 && gcd(s + 2, m) == 1)
            return s;
    return -1;
}

/* m=3 exceptional: layer0=(I,X,Y), layer1 rows 0,1=(I,Y,X) row2=(Y,I,X),
   layer2 row0=(X,I,Y) rows1,2=(X,Y,I) */
static int verify_odd_m3(void) {
    int n = 9;
    int *layers[3][3];  /* layers[s][c] = permutation for layer s, color c */
    for (int s = 0; s < 3; s++)
        for (int c = 0; c < 3; c++)
            layers[s][c] = perm_alloc(n);

    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++) {
            int idx = x * 3 + y;
            int d[3][3];

            d[0][0] = D_I; d[0][1] = D_X; d[0][2] = D_Y;

            if (x < 2) { d[1][0] = D_I; d[1][1] = D_Y; d[1][2] = D_X; }
            else        { d[1][0] = D_Y; d[1][1] = D_I; d[1][2] = D_X; }

            if (x == 0) { d[2][0] = D_X; d[2][1] = D_I; d[2][2] = D_Y; }
            else        { d[2][0] = D_X; d[2][1] = D_Y; d[2][2] = D_I; }

            for (int s = 0; s < 3; s++)
                for (int c = 0; c < 3; c++) {
                    int nx = x, ny = y;
                    if (d[s][c] == D_X) nx = (x + 1) % 3;
                    else if (d[s][c] == D_Y) ny = (y + 1) % 3;
                    layers[s][c][idx] = nx * 3 + ny;
                }
        }

    int *round = perm_alloc(n);
    int *tmp = perm_alloc(n);
    int ok = 1;

    for (int c = 0; c < 3 && ok; c++) {
        for (int i = 0; i < n; i++) round[i] = i;
        for (int s = 0; s < 3; s++) {
            perm_compose(tmp, round, layers[s][c], n);
            memcpy(round, tmp, n * sizeof(int));
        }
        if (!is_single_cycle(round, n)) ok = 0;
    }

    for (int s = 0; s < 3; s++)
        for (int c = 0; c < 3; c++)
            free(layers[s][c]);
    free(round); free(tmp);
    return ok;
}

/*
 * Layer types for odd case:
 *   P0 = (I, B, A)   color0=I, color1=B, color2=A
 *   P1 = (B, I, A)
 *   P2 = (A, B, I)
 *   Q2 = (B, A, I)
 *
 * Schedule: P0, P1, P2^t, Q2^(m-2-t)  where t = (s-1)/2
 */
static int verify_odd(int m) {
    if (m == 3) return verify_odd_m3();

    int n = m * m;
    int s = choose_s_odd(m);
    if (s < 0) return 0;
    int t = (s - 1) / 2;

    int *A = perm_alloc(n);
    int *B = perm_alloc(n);
    int *I = perm_alloc(n);
    build_match_A(A, m);
    build_match_B(B, m);
    build_match_I(I, m);

    int *tmp = perm_alloc(n);
    int *round_map = perm_alloc(n);
    int *pow_buf = perm_alloc(n);
    int ok = 1;

    /* For each color c, compute the round map */
    for (int c = 0; c < 3 && ok; c++) {
        /* Determine what each layer type gives this color */
        /* P0[c]: c0=I, c1=B, c2=A */
        /* P1[c]: c0=B, c1=I, c2=A */
        /* P2[c]: c0=A, c1=B, c2=I */
        /* Q2[c]: c0=B, c1=A, c2=I */
        const int *p0_c, *p1_c, *p2_c, *q2_c;
        if (c == 0)      { p0_c = I; p1_c = B; p2_c = A; q2_c = B; }
        else if (c == 1)  { p0_c = B; p1_c = I; p2_c = B; q2_c = A; }
        else              { p0_c = A; p1_c = A; p2_c = I; q2_c = I; }

        /* round = p0_c * p1_c * p2_c^t * q2_c^(m-2-t) */
        /* Start with identity */
        for (int i = 0; i < n; i++) round_map[i] = i;

        /* Compose p0_c */
        perm_compose(tmp, round_map, p0_c, n);
        memcpy(round_map, tmp, n * sizeof(int));

        /* Compose p1_c */
        perm_compose(tmp, round_map, p1_c, n);
        memcpy(round_map, tmp, n * sizeof(int));

        /* Compose p2_c^t */
        if (t > 0) {
            perm_power(pow_buf, p2_c, t, n);
            perm_compose(tmp, round_map, pow_buf, n);
            memcpy(round_map, tmp, n * sizeof(int));
        }

        /* Compose q2_c^(m-2-t) */
        int q_exp = m - 2 - t;
        if (q_exp > 0) {
            perm_power(pow_buf, q2_c, q_exp, n);
            perm_compose(tmp, round_map, pow_buf, n);
            memcpy(round_map, tmp, n * sizeof(int));
        }

        if (!is_single_cycle(round_map, n)) ok = 0;
    }

    free(A); free(B); free(I);
    free(tmp); free(round_map); free(pow_buf);
    return ok;
}

/* --- Even case --- */

/* Direction triple encoding */
enum {
    T_XYI = 0, T_YIX = 1, T_IYX = 2, T_YXI = 3,
    T_IXY = 4, T_XIY = 5
};

/* color c direction from triple type */
static const int triple_dirs[6][3] = {
    /* XYI */ {D_X, D_Y, D_I},
    /* YIX */ {D_Y, D_I, D_X},
    /* IYX */ {D_I, D_Y, D_X},
    /* YXI */ {D_Y, D_X, D_I},
    /* IXY */ {D_I, D_X, D_Y},
    /* XIY */ {D_X, D_I, D_Y},
};

/* Build a permutation from a direction grid */
static void dirs_to_perm(int *perm, const int *dirs, int m, int color) {
    for (int x = 0; x < m; x++)
        for (int y = 0; y < m; y++) {
            int idx = x * m + y;
            int d = triple_dirs[dirs[idx]][color];
            int nx = x, ny = y;
            if (d == D_X) nx = (x + 1) % m;
            else if (d == D_Y) ny = (y + 1) % m;
            perm[idx] = nx * m + ny;
        }
}

/* XYI bulk: color 0 = X, color 1 = Y, color 2 = I.
   Bulk^k: color0 = shift x by k, color1 = shift y by k, color2 = identity */
static void build_bulk_power(int *perm, int m, int k, int color) {
    k = k % m;
    for (int x = 0; x < m; x++)
        for (int y = 0; y < m; y++) {
            int nx = x, ny = y;
            if (color == 0) nx = (x + k) % m;
            else if (color == 1) ny = (y + k) % m;
            /* color 2: identity */
            perm[x * m + y] = nx * m + ny;
        }
}

/* Exceptional tables for m=4,6,8 */
/* Each is m layers of m*m triples. We store layer indices m-2 and m-1 only
   (layers 0..m-3 are all XYI). */

/* m=4: layers 2 and 3 */
static const int m4_layer2[16] = {
    T_XYI, T_XYI, T_YXI, T_YIX,
    T_XIY, T_XIY, T_IYX, T_IXY,
    T_XIY, T_YIX, T_XIY, T_IXY,
    T_YXI, T_XIY, T_XIY, T_IYX,
};
static const int m4_layer3[16] = {
    T_IXY, T_IXY, T_IXY, T_IXY,
    T_YXI, T_YXI, T_YXI, T_YXI,
    T_YXI, T_YXI, T_YXI, T_YXI,
    T_IXY, T_IXY, T_IXY, T_IXY,
};

/* m=6: layers 4 and 5 */
static const int m6_layer4[36] = {
    T_XYI, T_XYI, T_XYI, T_XYI, T_IYX, T_YXI,
    T_XYI, T_XYI, T_XYI, T_XYI, T_IXY, T_IYX,
    T_XIY, T_XIY, T_XIY, T_YIX, T_YXI, T_XIY,
    T_XIY, T_XIY, T_YIX, T_XIY, T_IXY, T_XIY,
    T_XYI, T_YXI, T_XIY, T_XIY, T_IYX, T_XYI,
    T_YXI, T_XYI, T_XYI, T_XYI, T_IYX, T_XYI,
};
static const int m6_layer5[36] = {
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX,
    T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
};

/* m=8: layers 6 and 7 */
static const int m8_layer6[64] = {
    T_XYI, T_XYI, T_XYI, T_XYI, T_XYI, T_XYI, T_IYX, T_YXI,
    T_XYI, T_XYI, T_XYI, T_XYI, T_XYI, T_XYI, T_IXY, T_IYX,
    T_XIY, T_XIY, T_XIY, T_XIY, T_XIY, T_YIX, T_XYI, T_IXY,
    T_XIY, T_XIY, T_XIY, T_XIY, T_YIX, T_XIY, T_XIY, T_IXY,
    T_XIY, T_XIY, T_XIY, T_YIX, T_XIY, T_XIY, T_XIY, T_IXY,
    T_XYI, T_XYI, T_YXI, T_XIY, T_XIY, T_XIY, T_YIX, T_XYI,
    T_XYI, T_YXI, T_XYI, T_XYI, T_XYI, T_XYI, T_IYX, T_XYI,
    T_YXI, T_XYI, T_XYI, T_XYI, T_XYI, T_XYI, T_IYX, T_XYI,
};
static const int m8_layer7[64] = {
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX,
    T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX, T_IYX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
    T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX, T_YIX,
};

/* Build staircase (penultimate) layer direction grid for even m >= 10 */
static void build_staircase(int *dirs, int m) {
    int h = m / 2;
    /* Default: XYI everywhere */
    for (int i = 0; i < m * m; i++) dirs[i] = T_XYI;

    /* Top half */
    /* Row 0 */
    dirs[0 * m + (m - 2)] = T_IYX;
    dirs[0 * m + (m - 1)] = T_YXI;
    /* Row 1 */
    dirs[1 * m + (m - 2)] = T_IXY;
    dirs[1 * m + (m - 1)] = T_IYX;
    /* Rows 2..h */
    for (int x = 2; x <= h; x++) {
        dirs[x * m + (m - 1 - x)] = T_YXI;
        dirs[x * m + (m - 1)] = T_IYX;
    }

    /* Bottom half: rows h+1 .. m-1 */
    for (int x = h + 1; x < m; x++) {
        int d = m - 1 - x;  /* 0 <= d <= h-2 */
        int *row = &dirs[x * m];

        if (h % 2 == 0) {
            if (d == h - 2) {
                for (int y = 0; y < d; y++) row[y] = T_XIY;
                row[d] = T_YIX;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XYI;
                row[m - 2] = T_YXI;
                row[m - 1] = T_XIY;
            } else if (d == h - 3 || d == h - 4) {
                for (int y = 0; y < d; y++) row[y] = T_XIY;
                row[d] = T_YIX;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XIY;
                row[m - 2] = T_IXY;
                row[m - 1] = T_XIY;
            } else if (d == h - 5) {
                for (int y = 0; y < d; y++) row[y] = T_XYI;
                row[d] = T_YXI;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XIY;
                row[m - 2] = T_IYX;
                row[m - 1] = T_XYI;
            } else {
                for (int y = 0; y < d; y++) row[y] = T_XYI;
                row[d] = T_YXI;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XYI;
                row[m - 2] = T_IYX;
                row[m - 1] = T_XYI;
            }
        } else {
            if (d == h - 2) {
                for (int y = 0; y < d; y++) row[y] = T_XIY;
                row[d] = T_YIX;
                for (int y = d + 1; y < m - 1; y++) row[y] = T_XYI;
                row[m - 1] = T_IXY;
            } else if (d == h - 3 || d == h - 4) {
                for (int y = 0; y < d; y++) row[y] = T_XIY;
                row[d] = T_YIX;
                for (int y = d + 1; y < m - 1; y++) row[y] = T_XIY;
                row[m - 1] = T_IXY;
            } else if (d == h - 5) {
                for (int y = 0; y < d; y++) row[y] = T_XYI;
                row[d] = T_YXI;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XIY;
                row[m - 2] = T_YIX;
                row[m - 1] = T_XYI;
            } else {
                for (int y = 0; y < d; y++) row[y] = T_XYI;
                row[d] = T_YXI;
                for (int y = d + 1; y < m - 2; y++) row[y] = T_XYI;
                row[m - 2] = T_IYX;
                row[m - 1] = T_XYI;
            }
        }
    }
}

/* Build terminal layer direction grid for even m >= 10 */
static void build_terminal(int *dirs, int m) {
    int h = m / 2;
    for (int x = 0; x < m; x++)
        for (int y = 0; y < m; y++) {
            if (x == h + 2 || x == h + 3)
                dirs[x * m + y] = T_IYX;
            else
                dirs[x * m + y] = T_YIX;
        }
}

static int verify_even(int m) {
    int n = m * m;
    int *perm_pen = perm_alloc(n);
    int *perm_term = perm_alloc(n);
    int *bulk_pow = perm_alloc(n);
    int *round_map = perm_alloc(n);
    int *tmp = perm_alloc(n);
    int *dirs = NULL;
    int ok = 1;

    const int *pen_dirs = NULL;
    const int *term_dirs = NULL;

    if (m == 4) { pen_dirs = m4_layer2; term_dirs = m4_layer3; }
    else if (m == 6) { pen_dirs = m6_layer4; term_dirs = m6_layer5; }
    else if (m == 8) { pen_dirs = m8_layer6; term_dirs = m8_layer7; }
    else {
        dirs = (int *)malloc(2 * n * sizeof(int));
        build_staircase(dirs, m);
        build_terminal(dirs + n, m);
        pen_dirs = dirs;
        term_dirs = dirs + n;
    }

    for (int c = 0; c < 3 && ok; c++) {
        /* round = bulk^(m-2) * pen * term */
        build_bulk_power(bulk_pow, m, m - 2, c);
        dirs_to_perm(perm_pen, pen_dirs, m, c);
        dirs_to_perm(perm_term, term_dirs, m, c);

        perm_compose(tmp, bulk_pow, perm_pen, n);
        perm_compose(round_map, tmp, perm_term, n);

        if (!is_single_cycle(round_map, n)) ok = 0;
    }

    free(perm_pen); free(perm_term); free(bulk_pow);
    free(round_map); free(tmp);
    if (dirs) free(dirs);
    return ok;
}

static int verify_m(int m) {
    if (m < 3) return 0;
    if (m % 2 == 1) return verify_odd(m);
    return verify_even(m);
}

int main(int argc, char **argv) {
    int max_m = 2001;
    int single_m = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            single_m = atoi(argv[++i]);
        } else {
            max_m = atoi(argv[i]);
        }
    }

    if (single_m > 0) {
        clock_t t0 = clock();
        int ok = verify_m(single_m);
        double elapsed = (double)(clock() - t0) / CLOCKS_PER_SEC;
        printf("m=%d  n=%lld  %s  (%.4fs)\n",
               single_m, (long long)single_m*single_m*single_m,
               ok ? "PASS" : "FAIL", elapsed);
        return ok ? 0 : 1;
    }

    int total = 0, passed = 0;
    clock_t wall_start = clock();

    for (int m = 3; m <= max_m; m++) {
        clock_t t0 = clock();
        int ok = verify_m(m);
        double elapsed = (double)(clock() - t0) / CLOCKS_PER_SEC;
        total++;
        if (ok) passed++;
        printf("m=%4d  n=%12lld  %s  (%.4fs)\n",
               m, (long long)m*m*m, ok ? "PASS" : "FAIL", elapsed);
        if (!ok) {
            fprintf(stderr, "FAIL at m=%d\n", m);
        }
    }

    double wall = (double)(clock() - wall_start) / CLOCKS_PER_SEC;
    printf("\n%d/%d passed  (%.2fs total)\n", passed, total, wall);
    return (passed == total) ? 0 : 1;
}
