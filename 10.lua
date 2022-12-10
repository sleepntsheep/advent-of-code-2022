
local X = 1
local cycle = 1
local Xmem = {}
local crt = {}
local crt_pointer = 0

local function do_cycle()
    Xmem[cycle] = X
    cycle = cycle + 1
    local crt_hori = crt_pointer % 40
    crt[crt_pointer] = math.abs(X - crt_hori) <= 1 and '#' or '.'
    crt_pointer = (crt_pointer + 1) % 240
end

for line in io.lines() do
    if line == 'noop' then
        do_cycle()
    elseif line:sub(1,4) == 'addx' then
        do_cycle()
        do_cycle()
        X = X + tonumber(line:match("addx (-?%d+)"))
    end
end

local sum = 0
for i = 20, 220, 40 do
    assert(Xmem[i])
    sum = sum + Xmem[i] * i
end

print(sum)

for row = 0, 5 do
    for col = 0, 39 do
        io.write(crt[row * 40 + col])
    end
    io.write('\n')
end

