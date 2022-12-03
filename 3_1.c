#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int priority(char item)
{
    if (item <= 'Z') return item - 'A' + 27;
    return item - 'a' + 1;
}

int main(void)
{
    int sum = 0;
    char buf[1<<12] = { 0 }, *p;
    int c1[1<<8] = { 0 };
    while (fgets(buf, sizeof buf, stdin)) {
        memset(c1, 0, sizeof c1);
        if (!(p = strchr(buf, '\n'))) continue;
        *p = 0;
        size_t l = (p - buf) / 2;
        for (size_t i = 0; i < l; i++)
            c1[buf[i]] = 1;
        for (size_t j = l; buf[j]; j++)
            if (c1[buf[j]])
                sum += priority(buf[j]), c1[buf[j]] = 0;
    }
    printf("%d", sum);
    return EXIT_SUCCESS;
}

