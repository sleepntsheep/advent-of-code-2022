#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define NSTK 10
#define NCRATE 10000

char a[NSTK+1][NCRATE];
char a2[NSTK+1][NCRATE];
size_t ap[NSTK+1];

void s_strrev(char *s, size_t len) {
    for (size_t i = 0; i * 2 < len; i++) {
        char t = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = t;
    }
}

int main(void) {
    char buf[1 << 14];
    while (fgets(buf, sizeof buf, stdin)) {
        char *p = strchr(buf, '\n');
        assert(p && "Buffer too small");
        *p = 0;

        if (buf[0] == '\0') {
        } if (buf[1] == '1') {
            for (size_t c = 1; c <= NSTK; c++) {
                s_strrev(a[c], ap[c]);
                strcpy(a2[c], a[c]);
            }
        } else if (strchr(buf, '[')) {
            char *x = buf + 1;
            for (size_t c = 1; x < p; c++) {
                assert(c <= NSTK && "NSTK too small");
                if (*x != ' ')
                    a[c][ap[c]++] = *x;
                x += 4;
            }
        } else {
            int nm, from, to;
            if (sscanf(buf, " move %d from %d to %d", &nm, &from, &to) != 3)
                continue;
            assert(ap[from] >= nm && "Moving from empty stack, wrong input?");
            for (int i = 0; i < nm; i++) {
                a[to][ap[to]++] = a[from][--ap[from]];
            }
            memcpy(a2[to] + ap[to] - nm, a2[from] + ap[from], nm);
        }
    }

    for (size_t c = 1; c <= NSTK; c++) {
        printf("%c", a[c][ap[c]-1]);
    }

    printf(" ");
    for (size_t c = 1; c <= NSTK; c++) {
        printf("%c", a2[c][ap[c]-1]);
    }

    return EXIT_SUCCESS;
}

