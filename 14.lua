N = 1000
Adj = {{x = 0, y = 1}, {x = -1, y = 1}, {x = 1, y = 1}}

local map = {}
local highest_y = 0

for i = 0, N do
    map[i] = {}
    for j = 0, N do
        map[i][j] = '.'
    end
end

local function path(a, b)
    if a.x == b.x then for i = math.min(a.y, b.y), math.max(a.y, b.y) do map[a.x][i] = '#' end end
    if a.y == b.y then for i = math.min(a.x, b.x), math.max(a.x, b.x) do map[i][a.y] = '#' end end
end

for line in io.lines() do
    local last = nil
    for x, y in line:gmatch("(-?%d+),(-?%d+)") do
        local cur = {x = tonumber(x), y = tonumber(y)}
        highest_y = math.max(highest_y, tonumber(y))
        if last then path(last, cur) end
        last = cur
    end
end

local function fall(sand)
    for _, p in pairs(Adj) do
        local x, y = sand.x + p.x, sand.y + p.y
        if map[x][y] == '.' then
            return {x = x, y = y}
        end
    end
    map[sand.x][sand.y] = 'O'
    return nil
end

local current_sand = {x = 500, y = 0}
local part1 = 0
local part2 = 0

while current_sand.y < N do
    local next_sand = fall(current_sand)
    if next_sand then
        current_sand = next_sand
    else
        part1 = part1 + 1
        current_sand = {x = 500, y = 0}
    end
end

path({x = 0, y = highest_y + 2}, {x = N, y = highest_y + 2})

current_sand = {x = 500, y = 0}
while map[500][0] == '.' do
    local next_sand = fall(current_sand)
    if next_sand then
        current_sand = next_sand
    else
        part2 = part2 + 1
        current_sand = {x = 500, y = 0}
    end
end

print(part1, part2 + part1)


