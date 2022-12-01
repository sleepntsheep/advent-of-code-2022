#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BFSIZE (1 << 14)

int maxi(int a, int b)
{
    return a > b ? a : b;
}

int main(void)
{
    static char buf[BFSIZE];
    int c1 = 0, c2 = 0, c3 = 0, cur = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        *strchr(buf, '\n') = 0;
        if (!buf[0]) {
            if (cur > c1) {
                c3 = c2;
                c2 = c1;
                c1 = cur;
            } else if (cur > c2) {
                c3 = c2;
                c2 = cur;
            } else if (cur > c3) {
                c3 = cur;
            }
            cur = 0;
        } else {
            cur += strtol(buf, NULL, 10);
        }
    }
    printf("%d", c1 + c2 + c3);
    return EXIT_SUCCESS;
}

