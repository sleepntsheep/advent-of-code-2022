#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BFSIZE (1 << 14)

int int_cmp_descend(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int main(void) {
    int arr[BFSIZE];
    size_t arrp = 0;
    char buf[BFSIZE];
    int cur = 0;
    while (fgets(buf, sizeof buf, stdin)) {
        *strchr(buf, '\n') = 0;
        if (!buf[0]) {
            arr[arrp++] = cur;
            cur = 0;
        } else {
            cur += strtol(buf, NULL, 10);
        }
    }
    qsort(arr, arrp, sizeof *arr, int_cmp_descend);
    printf("%d %d", arr[0], arr[0] + arr[1] + arr[2]);
    return EXIT_SUCCESS;
}

