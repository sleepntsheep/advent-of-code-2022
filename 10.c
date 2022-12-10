#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <curses.h>

int absi(int a) {
    return a > 0 ? a : -a;
}

#define CRT_WIDTH 40
#define CRT_HEIGHT 6
#define NCYCLE 240

int X = 1;
int Xs[NCYCLE + 2] = { 0 };
int cycle = 1;
size_t crtI = 0;
char crt[CRT_WIDTH * CRT_HEIGHT];

char buf[1<<12];

void do_cycle(void) {
    Xs[cycle++] = X;
    crt[crtI] = absi(X - (crtI % CRT_WIDTH)) <= 1 ? '#' : '.';
    crtI++;
}

int main(void) {
    while (fgets(buf, sizeof buf, stdin)) {
        if (buf[0] == 'n') {
            do_cycle();
        } else if (buf[0] == 'a') {
            do_cycle(); do_cycle();
            int dx = 0;
            assert(sscanf(buf, "addx %d", &dx));
            X += dx;
        }
    }

    int sum = 0;
    for (int i = 20; i <= 220; i += 40)
        sum += i * Xs[i];
    printf("%d\n", sum);

    for (int i = 0; i < CRT_HEIGHT; i++)
        printf("%.*s\n", CRT_WIDTH, crt + i * CRT_WIDTH);

    return EXIT_SUCCESS;
}

