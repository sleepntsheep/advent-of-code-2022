
Time = 30

local g = {}
local flow = {}
local adj = {}

for line in io.lines() do
    local u, f = line:match('Valve (%u%u) has flow rate=(-?%d+);')
    if u and f then
        flow[u] = tonumber(f)
        for v in line:sub(10, #line):gmatch('(%u%u)') do
            if g[u] == nil then g[u] = {v}
            else g[u][#g[u]+1] = v end
        end
    end
end

for u, _ in pairs(flow) do
    adj[u] = {}
    for v, _ in pairs(flow) do
        adj[u][v] = 1e9
    end
    for _, v in pairs(g[u]) do
        adj[u][v] = 1
    end
    adj[u][u] = 0
end

for i, _ in pairs(flow) do
    for j, _ in pairs(flow) do
        for k, _ in pairs(flow) do
            if adj[i][k] + adj[k][j] < adj[i][j] then
                adj[i][j] = adj[i][k] + adj[k][j]
            end
        end
    end
end

--local dp = {}
--for i = 0, Time do dp[i] = 0 end
local visit = {}
for u, _ in pairs(flow) do visit[u] = false end

--[[
for u, _ in pairs(flow) do
    g[u] = {}
    for v, _ in pairs(flow) do
        if adj[u][v] < 1e9 then
            table.insert(g[u], v)
        end
    end
end
--]]

local function dfs(u, t)
    if t <= 0 then return 0 end
    --if dp[t] > cf then return 0 end
    --dp[t] = cf
    local max = 0
    for _, v in pairs(g[u]) do
        if not visit[v] then
            local tl = t - adj[u][v] - 1
            local f = flow[v] * tl
            visit[v] = true
            f = f + dfs(v, tl)
            visit[v] = false
            max = math.max(f, max)
        end
    end
    return max
end

print(dfs('AA', Time))


