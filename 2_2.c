#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef enum RPS {
    Rock = 1,
    Paper = 2,
    Scissor = 3,
} RPS;

typedef enum Result {
    Lose = 0,
    Draw = 3,
    Win  = 6,
} Result;

RPS get_rps(const RPS o, const Result need)
{
    if (need == Draw) return o;
    if (need == Lose) return o["0\3\1\2"];
    return o["0\2\3\1"];
}

int main(void)
{
    char opponent, response;
    int score = 0;
    while (scanf(" %c %c", &opponent, &response) == 2)
    {
        assert(opponent >= 'A' && opponent <= 'C' && response >= 'X' && response <= 'Z');
        Result need = strcspn("X..Y..Z", (char[2]){response, 0});
        score += get_rps(opponent - 'A' + 1, need) + need;
    }
    printf("%d", score);
    return EXIT_SUCCESS;
}

