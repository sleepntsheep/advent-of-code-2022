
Rock = 1
Paper = 2
Scissor = 3
Lose = 0
Draw = 3
Win = 6

WinLoseTable = {
    [Rock] = {
        [Rock] = Draw,
        [Paper] = Lose,
        [Scissor] = Win,
    }, [Paper] = {
        [Rock] = Win,
        [Paper] = Draw,
        [Scissor] = Lose,
    }, [Scissor] = {
        [Rock] = Lose,
        [Paper] = Win,
        [Scissor] = Draw,
    }
}

OppoResultTable = {
    [Rock] = {
        [Win] = Paper,
        [Draw] = Rock,
        [Lose] = Scissor,
    }, [Paper] = {
        [Win] = Scissor,
        [Draw] = Paper,
        [Lose] = Rock,
    }, [Scissor] = {
        [Win] = Rock,
        [Draw] = Scissor,
        [Lose] = Paper,
    }
}

local score1 = 0
local score2 = 0

for line in io.lines()
do
    repeat
        if line == '' then break end
        op, j = string.find("ABC", string.sub(line, 1, 1))
        me, k = string.find("XYZ", string.sub(line, 3, 3))
        needed_result, k = string.find("X..Y..Z", string.sub(line, 3, 3)) - 1
        score1 = score1 + WinLoseTable[me][op] + me
        score2 = score2 + OppoResultTable[op][needed_result] + needed_result
    until true
end

print(score1, score2)

