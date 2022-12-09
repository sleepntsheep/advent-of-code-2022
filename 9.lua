
Direction = { Up = 1, Left = 2, Down = 3, Right = 4 }
Adjacent4 = {
    [Direction.Up] = {x = 0, y = -1},
    [Direction.Left] = {x = -1, y = 0},
    [Direction.Down] = {x = 0, y = 1},
    [Direction.Right] = {x = 1, y = 0}
}

local function need_to_follow(head, tail)
    return math.abs(head.y - tail.y) >= 2 or math.abs(head.x - tail.x) >= 2
end

local function follow(head, tail)
    if need_to_follow(head, tail) then
        if head.x == tail.x then
            tail.y = tail.y + (head.y > tail.y and 1 or -1)
        elseif head.y == tail.y then
            tail.x = tail.x + (head.x > tail.x and 1 or -1)
        elseif head.x > tail.x and head.y > tail.y then
            tail.x = tail.x + 1
            tail.y = tail.y + 1
        elseif head.x < tail.x and head.y > tail.y then
            tail.x = tail.x - 1
            tail.y = tail.y + 1
        elseif head.x > tail.x and head.y < tail.y then
            tail.x = tail.x + 1
            tail.y = tail.y - 1
        else
            tail.x = tail.x - 1
            tail.y = tail.y - 1
        end
    end

    local hh = tostring(tail.x)..'D'..tostring(tail.y)
    if tail.visited[hh] == nil then
        tail.visited[hh] = true
        tail.visit_count = tail.visit_count + 1
    end
    if tail.tail then
        follow(tail, tail.tail)
    end
end

local nknots = 10
local knots = {}

for i = 1, nknots do
    knots[i] = {x = 0, y = 0, visited = {["0D0"] = true}, visit_count = 1}
end
for i = 1, nknots - 1 do
    knots[i].tail = knots[i+1]
end

for line in io.lines() do
    if line ~= '' then
        local char_dir, dist = line:match("(.+) (%d+)%s*")
        dist = tonumber(dist)
        local direction, _ = string.find("ULDR", char_dir)

        knots[1].x = knots[1].x + Adjacent4[direction].x * dist
        knots[1].y = knots[1].y + Adjacent4[direction].y * dist

        while need_to_follow(knots[1], knots[2]) do
            follow(knots[1], knots[2])
        end
    end
end

print(knots[2].visit_count, knots[nknots].visit_count)

