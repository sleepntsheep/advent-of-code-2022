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

int maxi(int a, int b) {
    return a > b ? a : b;
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
    initscr();
    keypad(stdscr, 1);
    noecho();
    assert(has_colors());
    start_color();
    //raw();

    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_RED, COLOR_RED);
    init_pair(3, COLOR_BLUE, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_BLACK);

    WINDOW *crtwin = newwin(CRT_HEIGHT + 2, CRT_WIDTH + 2, 1, 1);
    WINDOW *statwin = newwin(CRT_HEIGHT + 2, 20, 1, CRT_WIDTH + 4);

    while (fgets(buf, sizeof buf, stdin)) {
        erase();
        werase(crtwin);
        werase(statwin);

        mvwprintw(statwin, 1, 1, "X    : %d", X);
        mvwprintw(statwin, 2, 1, "Cycle: %d", cycle);
        mvwprintw(statwin, 3, 1, "OP   : %s", buf);
        box(statwin, 0, 0);

        refresh();
        wrefresh(statwin);

        if (buf[0] == 'n') {
            do_cycle();
        } else if (buf[0] == 'a') {
            do_cycle(); do_cycle();
            int dx = 0;
            assert(sscanf(buf, "addx %d", &dx));
            X += dx;
        }

        for (int i = 0; i < CRT_HEIGHT; i++) {
            for (int j = 0; j < CRT_WIDTH; j++) {
                int color = crt[i * CRT_WIDTH + j] == '#' ? 1 : 2;
                wattron(crtwin, COLOR_PAIR(color));
                mvwprintw(crtwin, i+1, j+1, " ");
                wattroff(crtwin, COLOR_PAIR(color));
            }
        }

        int crtIrow = crtI / CRT_WIDTH;
        int crtIcol = crtI % CRT_WIDTH;

        wattron(crtwin, COLOR_PAIR(3));
        mvwprintw(crtwin, crtIrow + 1, maxi(1, X), "   ");
        wattroff(crtwin, COLOR_PAIR(3));
        wattron(crtwin, COLOR_PAIR(4));
        mvwprintw(crtwin, crtIrow + 1, crtIcol + 1, " ");
        wattroff(crtwin, COLOR_PAIR(4));

        box(crtwin, 0, 0);

        wrefresh(crtwin);
        napms(300);
    }

    delwin(crtwin);
    delwin(statwin);
    napms(1000);
    endwin();
    return EXIT_SUCCESS;
}

