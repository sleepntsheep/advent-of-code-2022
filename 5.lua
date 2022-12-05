
NSTACK = 10

local stk = {}
local vec = {}

for i = 1, NSTACK do
    vec[i] = {}
    stk[i] = {}
end

for line in io.lines()
do
    if line == '' then
    elseif line:sub(2, 2) == '1' then
        for i = 1, NSTACK do
            for j = 1, math.floor(#stk[i] / 2) do
                local x = stk[i][j]
                stk[i][j] = stk[i][#stk[i]-j+1]
                stk[i][#stk[i]-j+1] = x;
            end
            for j = 1, #stk[i] do
                vec[i][j] = stk[i][j]
            end
        end
    elseif line:sub(1, 1) == ' ' or line:sub(1, 1) == '[' then
        local c = 1
        while c < NSTACK do
            local i = c * 4 - 2
            if i > #line then break end
            if line:sub(i, i) ~= ' ' then
                table.insert(stk[c], line:sub(i, i))
            end
            c = c + 1
        end
    elseif line:sub(1, 1) == 'm' then
        for nm, from, to in line:gmatch("move (%d+) from (%d+) to (%d+)") do
            from = tonumber(from)
            to = tonumber(to)
            nm = tonumber(nm)
            local temp = {}
            for _ = 1, nm do
                table.insert(stk[to], table.remove(stk[from]))
                table.insert(temp, table.remove(vec[from]))
            end
            for _ = 1, nm do
                table.insert(vec[to], table.remove(temp))
            end
        end
    end
end

for i = 1, NSTACK do
    local s = stk[i]
    if #s > 0 then
        io.write(s[#s])
    end
end
io.write(' ')

for i = 1, NSTACK do
    local s = vec[i]
    if #s > 0 then
        io.write(s[#s])
    end
end





