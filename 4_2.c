#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct { int a, b; } Pair;

int maxi(int a, int b) {
    return a > b ? a : b;
}

int Pair_overlap(const Pair *a, const Pair *b) {
    const Pair *c = a->a < b->a ? a : b;
    const Pair *d = c == a ? b : a;
    return maxi(0, c->b - d->a + 1);
}

int main(void) {
    Pair a, b;
    int c = 0;
    while (scanf(" %d-%d,%d-%d", &a.a, &a.b, &b.a, &b.b) == 4)
        c += !!Pair_overlap(&a, &b);
    printf("%d", c);
    return EXIT_SUCCESS;
}

