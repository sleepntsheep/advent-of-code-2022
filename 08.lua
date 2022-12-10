local trees = {}
local nrow = 0

for line in io.lines() do
    if line ~= '' then
        trees[#trees + 1] = {}
        for i = 1, #line do
            if line:sub(i, i) ~= '' then
                local n = tonumber(line:sub(i, i))
                trees[#trees][i] = {
                    v = n, u = n, r = n, l = n, d = n,
                }
            end
        end
        nrow = math.max(nrow, #trees[#trees])
    end
end

local ncol = #trees

-- part 1
for i = 2, nrow do
    for j = 2, ncol do
        trees[i][j].l = math.max(trees[i][j].v, trees[i][j-1].l)
        trees[i][j].u = math.max(trees[i][j].v, trees[i-1][j].u)
    end
end

for i = nrow - 1, 1, -1 do
    for j = ncol - 1, 1, -1 do
        trees[i][j].r = math.max(trees[i][j].v, trees[i][j+1].r)
        trees[i][j].d = math.max(trees[i][j].v, trees[i+1][j].d)
    end
end

local visible_count = 2 * (nrow + ncol) - 4

for i = 2, nrow - 1 do
    for j = 2, ncol - 1 do
        if math.min(trees[i][j].v, trees[i-1][j].u, trees[i][j-1].l, trees[i][j+1].r, trees[i+1][j].d) ~= trees[i][j].v then
            visible_count = visible_count + 1
        end
    end
end

-- part 2

local highest_scenic_score = 0
for i = 2, nrow - 1 do
    for j = 2, ncol - 1 do
        ADJ4 = { {x = -1, y = 0}, {x = 1, y = 0}, {x = 0, y = -1}, {x = 0, y = 1} }
        local score = 1
        for _, d in ipairs(ADJ4) do
            for k = 1, math.max(nrow, ncol) do
                local ni = i + d.y * k
                local nj = j + d.x * k
                if ni < 1 or nj < 1 or ni > ncol or nj > nrow then
                    score = score * (k - 1)
                    break
                elseif trees[ni][nj].v >= trees[i][j].v then
                    score = score * k
                    break
                end
            end
        end
        highest_scenic_score = math.max(highest_scenic_score, score)
    end
end

print(visible_count, highest_scenic_score)


