#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct { int a, b; } Pair;

bool Pair_contain(const Pair *a, const Pair *b) {
    return b->a >= a->a && b->b <= a->b;
}

int main(void) {
    Pair a, b;
    int c = 0;
    while (scanf(" %d-%d,%d-%d", &a.a, &a.b, &b.a, &b.b) == 4)
        c += Pair_contain(&a, &b) || Pair_contain(&b, &a);
    printf("%d", c);
    return EXIT_SUCCESS;
}

