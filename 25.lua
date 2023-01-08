
local function snafu_to_dec(s)
    local dec = 0

    for i = 1, #s do
        dec = dec * 5
        local c = s:sub(i, i)
        if c == '1' then
            dec = dec + 1
        elseif c == '2' then
            dec = dec + 2
        elseif c == '0' then
        elseif c == '-' then
            dec = dec - 1
        elseif c == '=' then
            dec = dec - 2
        end
    end

    return dec
end

local function dec_to_snafu(n)
    if n == 0 then return '' end
    local s = ''
    local i = n % 5 + 1
    s = s..dec_to_snafu((n + 2) // 5)
    s = s..("012=-"):sub(i, i)
    return s
end

local w = 0
for line in io.lines() do
    if line ~= '' then
        w = w + snafu_to_dec(line)
    end
end

print(w)
print(dec_to_snafu(w))

