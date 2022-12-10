#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef enum RPS {
    Rock,
    Paper,
    Scissor,
} RPS;

typedef enum Result {
    Lose = 0,
    Draw = 3,
    Win  = 6,
} Result;

Result get_result(const RPS me, const RPS opponent)
{
    if (me == Rock && opponent == Scissor) return Win;
    if (me == Paper && opponent == Rock) return Win;
    if (me == Scissor && opponent == Paper) return Win;
    if (me == opponent) return Draw;
    return Lose;
}

RPS get_rps(const RPS o, const Result need) {
    if (need == Draw) return o;
    if (need == Lose) return o["0\3\1\2"];
    return o["0\2\3\1"];
}

int main(void)
{
    char opponent, response;

    int score1 = 0, score2 = 0;
    while (scanf(" %c %c", &opponent, &response) == 2)
    {
        assert(opponent >= 'A' && opponent <= 'C'
                && response >= 'X' && response <= 'Z');
        score1 += get_result(response - 'X', opponent - 'A') + (response - 'X' + 1);

        Result need = strcspn("X..Y..Z", (char[]){response, 0});
        score2 += get_rps(opponent - 'A' + 1, need) + need;
    }

    printf("%d %d", score1, score2);

    return EXIT_SUCCESS;
}

