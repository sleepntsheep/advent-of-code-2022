#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int priority(char item) {
    if (item <= 'Z') return item - 'A' + 27;
    return item - 'a' + 1;
}

int main(void)
{
    int sum = 0, c = 0, d[1<<8], sum2 = 0;
    char buf[1<<12] = { 0 }, *p;
    int c1[1<<8] = { 0 };
    while (fgets(buf, sizeof buf, stdin)) {
        memset(c1, 0, sizeof c1);
        if (!(p = strchr(buf, '\n'))) continue;
        *p = 0;
        if (!*buf) continue;

        size_t l = (p - buf) / 2;
        for (size_t i = 0; i < l; i++)
            c1[buf[i]] = 1;
        for (size_t j = l; buf[j]; j++)
            if (c1[buf[j]])
                sum += priority(buf[j]), c1[buf[j]] = 0;

        if (!c) memset(d, 0, sizeof d);
        for (char *p = buf; *p; p++)
            if (d[*p] & (1 << c)) continue;
            else if ((d[*p] |= (1 << c)) == 7) sum2 += priority(*p);
        c = (c+1)%3;
    }
    printf("%d %d", sum, sum2);
    return EXIT_SUCCESS;
}

