#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>

#define MAX_MONKEYS 10
#define MAX_ITEMS 10000

struct Monkey {
    int64_t activity;
    int id;
    int64_t items[MAX_ITEMS];
    size_t nitem;
    int64_t divisor;
    char lop[1024], rop[1024];
    char operator;
    int iftrue, iffalse;
};

struct Monkey monkeys[MAX_MONKEYS];
int64_t lcm = 1;
size_t monkey_count = 0;

int monkey_cmpr_descend_activity(const void *a, const void *b) {
    return ((struct Monkey *)b)->activity - ((struct Monkey *)a)->activity;
}

void do_round(struct Monkey *monkeys, bool do_divide) {
    for (size_t i = 0; i < monkey_count; i++) {
        struct Monkey *m = monkeys + i;
        m->activity += m->nitem;
        for (size_t j = 0; j < m->nitem; j++) {
            int64_t item = m->items[j];
            int64_t lop, rop;
            if (m->lop[0] == 'o') lop = item;
            else lop = strtoll(m->lop, NULL, 10);
            if (m->rop[0] == 'o') rop = item;
            else rop = strtoll(m->rop, NULL, 10);
            switch (m->operator) {
                case '+': item = lop + rop; break;
                case '-': item = lop - rop; break;
                case '*': item = lop * rop; break;
                case '/': item = lop / rop; break;
            }
            if (do_divide) item /= 3;
            item %= lcm;
            struct Monkey *recipient = monkeys + ((item % m->divisor) ? m->iffalse : m->iftrue);
            recipient->items[recipient->nitem++] = item;
        }
        m->nitem = 0;
    }
}

int main(void) {
    char buf[2048];
    while (fgets(buf, sizeof buf, stdin)) {
        if (buf[0] == '\n') continue;
        struct Monkey m = { 0 };
        assert(sscanf(buf, "Monkey %d", &m.id) == 1);
        fgets(buf, sizeof buf, stdin);
        char *p = buf + sizeof "  Starting items: " - 1;
        while (p) {
            int64_t item;
            char *q = strchr(p, ',');
            if (q) *q = '\0';
            assert(sscanf(p, "%"SCNi64, &item) == 1);
            m.items[m.nitem++] = item;
            if (q) p = q + 1;
            else p = NULL;
        }
        fgets(buf, sizeof buf, stdin);
        assert(sscanf(buf, " Operation: new = %s %c %s", m.lop, &m.operator, m.rop) == 3);
        fgets(buf, sizeof buf, stdin);
        assert(sscanf(buf, " Test: divisible by %"SCNi64, &m.divisor) == 1);
        fgets(buf, sizeof buf, stdin);
        assert(sscanf(buf, " If true: throw to monkey %d", &m.iftrue) == 1);
        fgets(buf, sizeof buf, stdin);
        assert(sscanf(buf, " If false: throw to monkey %d", &m.iffalse) == 1);
        monkeys[m.id] = m;
        if (m.id + 1 > monkey_count) monkey_count = m.id + 1;
        lcm *= m.divisor;
    }

    struct Monkey part1[MAX_MONKEYS];
    memcpy(part1, monkeys, sizeof monkeys);
    struct Monkey part2[MAX_MONKEYS];
    memcpy(part2, monkeys, sizeof monkeys);

    for (int i = 1; i <= 20; i++) do_round(part1, true);
    qsort(part1, monkey_count, sizeof part1[0], monkey_cmpr_descend_activity);
    printf("%"PRIi64 " ", part1[0].activity * part1[1].activity);

    for (int i = 1; i <= 10000; i++) do_round(part2, false);
    qsort(part2, monkey_count, sizeof part2[0], monkey_cmpr_descend_activity);
    printf("%"PRIi64, part2[0].activity * part2[1].activity);

    return 0;
}

