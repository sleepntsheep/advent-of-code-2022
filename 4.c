#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct { int a, b; } Pair;
int maxi(int a, int b) { return a > b ? a : b; }

bool Pair_contain(const Pair *a, const Pair *b) {
    return b->a >= a->a && b->b <= a->b;
}

int Pair_overlap(const Pair *a, const Pair *b) {
    const Pair *c = a->a < b->a ? a : b;
    const Pair *d = c == a ? b : a;
    return maxi(0, c->b - d->a + 1);
}

int main(void) {
    Pair a, b;
    int c = 0, o = 0;
    while (scanf(" %d-%d,%d-%d", &a.a, &a.b, &b.a, &b.b) == 4) {
        c += Pair_contain(&a, &b) || Pair_contain(&b, &a);
        o += !!Pair_overlap(&a, &b);
    }
    printf("%d %d", c, o);

    return EXIT_SUCCESS;
}

