
local marker_find = function(line, marker_len)
    for i = marker_len, #line do
        local found = {}
        local is_marker = true
        for j = 0, marker_len - 1 do
            if found[line:byte(i-j)] then
                is_marker = false
            else
                found[line:byte(i-j)] = true
            end
        end
        if is_marker then
            return i
        end
    end
    return nil
end

for line in io.lines() do
    if line ~= '' then
        print(string.format("%d %d", marker_find(line, 4), marker_find(line, 14)))
    end
end

