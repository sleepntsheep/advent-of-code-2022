#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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

int main(void)
{
    char opponent, response;

    int score = 0;
    while (scanf(" %c %c", &opponent, &response) == 2)
    {
        assert(opponent >= 'A' && opponent <= 'C'
                && response >= 'X' && response <= 'Z');
        score += get_result(response - 'X', opponent - 'A') + (response - 'X' + 1);
    }

    printf("%d", score);

    return EXIT_SUCCESS;
}

