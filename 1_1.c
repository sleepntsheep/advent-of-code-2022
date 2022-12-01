#include <string.h>
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
    int ans = 0, cur = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        *strchr(buf, '\n') = 0;
        if (!buf[0]) {
            ans = maxi(ans, cur);
            cur = 0;
        } else {
            cur += strtol(buf, NULL, 10);
        }
    }
    printf("%d", ans);
    return EXIT_SUCCESS;
}

