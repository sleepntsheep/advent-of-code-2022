local sensors = {}
local data = {}
local obs = {}

local function add_obs(x, y)
    if obs[y] == nil then
        obs[y] = {count = 0, x = {}}
    end
    if obs[y].x[x] == nil then
        obs[y].x[x] = true
        obs[y].count = obs[y].count + 1
    end
end

local function get_range(ty, mleft, mright)
    local leftest = 10000000
    local rightest = 0
    local ranges = {}
    for _, p in ipairs(data) do
        local sx, sy, bx, by = p.sx, p.sy, p.bx, p.by
        local md = math.abs(sx - bx) + math.abs(sy - by)
        local x_radius = md - math.abs(sy - ty)
        if x_radius >= 0 then
            local left = sx - x_radius
            local right = sx + x_radius
            left = math.max(left, mleft)
            right = math.min(right, mright)
            rightest = math.max(right, rightest)
            leftest = math.min(left, leftest)
            if left < right then
                table.insert(ranges, {left, 1})
                table.insert(ranges, {right + 1, -1})
            end
        end
    end
    table.sort(ranges, function(a, b) if a[1] ~= b[1] then return a[1] < b[1] else return a[2] > b[2] end end)
    return ranges, leftest, rightest
end

for line in io.lines() do
    local sx, sy, bx, by = line:match("Sensor at x=(-?%d+), y=(-?%d+): closest beacon is at x=(-?%d+), y=(-?%d+)")
    if sx and sy and bx and by then
        sx = tonumber(sx) sy = tonumber(sy) bx = tonumber(bx) by = tonumber(by)
        table.insert(data, {sx = sx, sy = sy, bx = bx, by = by})
        add_obs(bx, by)
        add_obs(sx, sy)
    end
end

local function range_count_impossible(ranges)
    local sum = 0
    local state = 0
    local last
    for _, range in ipairs(ranges) do
        local x, delta = range[1], range[2]
        state = state + delta
        if state == 1 and delta == 1 then
            last = x
        end
        if state == 0 and delta == -1 then
            sum = sum + (x - last)
        end
    end
    return sum
end

local function range_get_possible_spot(ranges)
    local state = 0
    local last2
    for _, range in ipairs(ranges) do
        local x, delta = range[1], range[2]
        state = state + delta
        if state == 0 then
            last2 = x
        end
        if last2 and state == 1 and last2 < x then
            return last2
        end
    end
    return nil
end

local part1, part2

-- part 1
local target_y = 2000000
local delta = 0
if obs[target_y] then delta = - obs[target_y].count end
part1 = range_count_impossible(get_range(target_y, -1e9, 1e9)) + delta

-- part 2

for y = 0, 4000000 do
    local l, r = 0, 4000000
    local range, _, _ = get_range(y, l, r)
    local imp = range_count_impossible(range)
    if imp < r - l + 1 then
        local x = range_get_possible_spot(range)
        part2 = (x * 4000000) + y
        break
    end
end

print(part1, part2)


