Equal = 0
Less = -1
More = 1

local function parse(line)
    line = line:gsub('%[', '{'):gsub('%]', '}')
    return load('return ' .. line)()
end

local function sorted(a, b)
    if type(a) == 'number' and type(b) == 'number' then
        if a == b then return Equal elseif a < b then return Less else return More end
    elseif type(a) == 'table' and type(b) == 'table' then
        for i = 1, math.min(#a, #b) do
            local h = sorted(a[i], b[i])
            if h ~= Equal then return h end
        end
        if #a > #b then return More
        elseif #a == #b then return Equal
        else return Less end
    elseif type(a) == 'number' then
        return sorted({a},b)
    else
        return sorted(a, {b})
    end
end

local lines = {}
for line in io.lines() do table.insert(lines, line) end
local li = 1
local counter = 1
local score1 = 0
local packets = {}

while li < #lines do
    if lines[li] ~= '' and lines[li+1] ~= '' then
        local a = parse(lines[li])
        local b = parse(lines[li+1])
        table.insert(packets, a)
        table.insert(packets, b)
        if sorted(a, b) == Less then
            score1 = score1 + counter
        end
        counter = counter + 1
        li = li + 1
    end
    li = li + 1
end

local decoder1 = {{2}}
local decoder2 = {{6}}
local score2 = 1
table.insert(packets, decoder1)
table.insert(packets, decoder2)

table.sort(packets, function(a, b) return sorted(a, b) == Less end)

for i, p in ipairs(packets) do
    if p == decoder1 or p == decoder2 then
        score2 = score2 * i
    end
end

print(score1, score2)

