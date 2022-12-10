-- overlap, contain

local function isnotoverlap(p1, p2)
    return p1.a > p2.b or p1.b < p2.a
end

local function iscontain(p1, p2)
    return (p1.a <= p2.a and p1.b >= p2.b)
end

local score1 = 0
local score2 = 0
for line in io.lines() do
    for a, b, c, d in string.gmatch(line, "(%d+)-(%d+),(%d+)-(%d+)") do
        a = tonumber(a)
        b = tonumber(b)
        c = tonumber(c)
        d = tonumber(d)
        local p1 = {a = a, b = b}
        local p2 = {a = c, b = d}
        if iscontain(p1, p2) or iscontain(p2, p1) then
            score1 = score1 + 1
        end
        if not isnotoverlap(p1, p2) then
            score2 = score2 + 1
        end
    end
end

print(score1, score2)
