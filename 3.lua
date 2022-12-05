
local function priority(ch)
    return string.find("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", ch:sub(1, 1))
end

local score1 = 0
local score2 = 0
local linecounter = 0
local count = {}

for line in io.lines() do
    if line ~= '' then
        -- part 1
        local half = #line % 2 == 0 and #line / 2 + 1 or math.ceil(#line / 2)
        local found = {}
        for i = 1, 52 do found[i] = 0 end

        for i = 1, half - 1 do
            local p = priority(line:sub(i, i))
            found[p] = 1
        end
        for i = half, #line do
            local p = priority(line:sub(i, i))
            if found[p] == 1 then
                score1 = score1 + p
                break
            end
        end

        -- part 2
        if linecounter == 0 then
            for i = 1, 52 do count[i] = 0 end
        end

        for i = 1, #line do
            local p = priority(line:sub(i, i))
            count[p] = count[p] | (1 << linecounter)
            if count[p] == 7 then
                score2 = score2 + p
                break
            end
        end

        linecounter = (linecounter + 1) % 3
    end
end

print(score1, score2)

