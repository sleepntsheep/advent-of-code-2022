#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <inttypes.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define MAX_MONKEYS 10
#define MAX_ITEMS 10000

struct Monkey {
    int64_t activity;
    int id;
    int64_t items[MAX_ITEMS];
    size_t nitem;
    size_t sitem;
    int64_t divisor;
    char lop[1024], rop[1024];
    char operator;
    int iftrue, iffalse;
};

int monkey_cmpr_descend_activity(const void *a, const void *b) {
    return ((struct Monkey *)b)->activity - ((struct Monkey *)a)->activity;
}

int64_t lcm = 1;
size_t monkey_count = 0;

SDL_Window *win = NULL;
SDL_Renderer *rend = NULL;
TTF_Font *font = NULL;

// make draw text helper function for sdl_ttf
void draw_text(int x, int y, const char *text, SDL_Color color) {
    SDL_Surface *surf = TTF_RenderText_Blended(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(rend, surf);
    SDL_Rect rect = {x, y, surf->w, surf->h};
    SDL_RenderCopy(rend, texture, NULL, &rect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

void parse(struct Monkey *monkeys) {
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
}

void frame(struct Monkey *ma, int round, int focused_monkey) {
    char buf[1024];
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    for (size_t j = 0; j < monkey_count; j++) {
        SDL_Color color = { 255, 255, 0, 255 };
        if (j != focused_monkey) color = (SDL_Color){ 255, 255, 255, 255 };
        struct Monkey *m = ma + j;
        for (size_t k = m->sitem, cn = 0; k < m->nitem; k++, cn++) {
            int64_t item = m->items[k];
            int x = 400 + cn * 80;
            int y = j * 50;
            snprintf(buf, sizeof buf, "%"PRIi64, item);
            draw_text(x, y, buf, color);
        }
        snprintf(buf, sizeof buf, "%d (%"PRIi64") (%%%2"PRIi64") (%s %c %s)", m->id, m->activity, m->divisor, m->lop, m->operator, m->rop);
        draw_text(0, j * 50, buf, color);
    }

    snprintf(buf, sizeof buf, "Round: %d", round);
    draw_text(0, 400, buf, (SDL_Color){255,255,255,255});

    SDL_Event e;
    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT) exit(0);

    SDL_RenderPresent(rend);
    SDL_Delay(200);
}

void do_round(struct Monkey *monkeys, bool do_divide, int round) {
    for (size_t i = 0; i < monkey_count; i++) {
        struct Monkey *m = monkeys + i;
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
            m->sitem++;
            m->activity++;
            frame(monkeys, round, i);
        }
        m->nitem = 0;
        m->sitem = 0;
    }
}

int main(void) {
    struct Monkey part1[MAX_MONKEYS];
    parse(part1);
    struct Monkey part2[MAX_MONKEYS];
    memcpy(part2, part1, sizeof part1);

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    win = SDL_CreateWindow("Monkey Business", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1800, 600, SDL_WINDOW_SHOWN);
    rend = SDL_CreateRenderer(win, -1, 0);
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    SDL_RenderPresent(rend);
    font = TTF_OpenFont("ubuntu_mono.ttf", 24);

    // wait for window keypress any key before starting
    SDL_Event e;
    while (SDL_WaitEvent(&e))
        if (e.type == SDL_KEYDOWN && /* key is e */ 
            e.key.keysym.sym == SDLK_e) break;

#if 1
    for (int i = 1; i <= 20; i++) do_round(part1, true, i);
    qsort(part1, monkey_count, sizeof part1[0], monkey_cmpr_descend_activity);
    printf("%"PRIi64 " ", part1[0].activity * part1[1].activity);
#endif

#if 0
    for (int i = 1; i <= 10000; i++) do_round(part2, false, i);
    qsort(part2, monkey_count, sizeof part2[0], monkey_cmpr_descend_activity);
#endif
    printf("%"PRIi64, part2[0].activity * part2[1].activity);

    // wait for window keypress input before closing window
    while (SDL_WaitEvent(&e))
        if (e.type == SDL_QUIT) break;

    // SDL Cleanup
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

