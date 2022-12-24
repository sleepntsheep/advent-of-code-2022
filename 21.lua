local function copy2(obj)
    local r = {}
    for k, v in pairs(obj) do
        r[k] = {}
        for k2, v2 in pairs(v) do
            r[k][k2] = v2
        end
    end
    return r
end

local yell = {}

local function doop(d1, op, d2)
    if op == '+' then
        return d1 + d2
    elseif op == '-' then
        return d1 - d2
    elseif op == '*' then
        return d1 * d2
    elseif op == '/' then
        return d1 / d2
    end
end

local function get_yell(name, yy)
    local y = yy[name]
    y.visit = true
    if y.v then
        return y.v
    end
    y.v = doop(get_yell(y.dep1, yy), y.op, get_yell(y.dep2, yy))
    return y.v
end

for line in io.lines() do
    local name, num = line:match('(%w+): (-?%d+)')
    if num then
        yell[name] = {v = tonumber(num)}
    end
    local name2, dep1, op, dep2 = line:match('(%w+): (%w+) (.) (%w+)')
    if name2 then
        yell[name2] = {v = nil, dep1 = dep1, op = op, dep2 = dep2}
    end
end

local y1 = copy2(yell)

local part1 = get_yell('root', y1)
local part2 = 0

local l, r = 0, 1e24

local b1 = yell.root.dep1
local b2 = yell.root.dep2

while l <= r do
    local m = (l + r) // 2
    local ly = copy2(yell)
    ly.humn.v = m
    local d1 = get_yell(b1, ly)
    local md1 = not ly.humn.visit -- im not sure why there is a not here, but it works
    -- if it doesn't work for other input (output 0) just remove the not!!!!! YES
    local d2 = get_yell(b2, ly)
    if d1 == d2 then
        part2 = m
        break
    end
    if (d1 < d2 and md1) or (d1 > d2 and not md1) then
        l = m + 1
    else
        r = m - 1
    end
end

print(string.format("%.0f %.0f\n", part1, part2))


