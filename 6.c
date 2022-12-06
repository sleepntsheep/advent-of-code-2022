#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <string.h>

char b[1<<18];

char *marker_find(char *line, int marker_len) {
    char *p = line + marker_len - 1;
    for (; *p; p++) {
        bool found[1<<8] = { 0 };
        bool is_marker = true;
        for (int j = 0; j < marker_len; j++) {
            if (found[*(p-j)]) {
                is_marker = false;
                break;
            }
            found[*(p-j)] = true;
        }
        if (is_marker) {
            return p;
        }
    }
    return NULL;
}

int main(void) {
    while (fgets(b, sizeof b, stdin)) {
        char *p = strchr(b, '\n');
        assert(p && "buffer too small");
        *p = 0;
        if (!strcmp(b, "")) continue;
        printf("%ld %ld", marker_find(b, 4) - b + 1, marker_find(b, 14) - b + 1);
    }

    return EXIT_SUCCESS;
}

