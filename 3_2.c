#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int priority(char item)
{
    return (item <= 'Z') * (item - 'A' + 27) + (item > 'Z') * (item - 'a' + 1);
}

int main(void)
{
    int sum = 0, c = 0, d[1<<8] = { 0 };
    char b[1<<12] = { 0 }, *p;
    for (; fgets(b, sizeof b, stdin); c = (c+1)%3) {
        if (*b == 10) continue;
        if (!c) memset(d, 0, sizeof d);
        for (char *p = b; *p && *p != '\n'; p++)
            if (d[*p] & (1 << c)) continue;
            else if ((d[*p] |= (1 << c)) == 7) sum += priority(*p);
    }
    printf("%d", sum);
    return EXIT_SUCCESS;
}

