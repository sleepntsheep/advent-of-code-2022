
Adj4 = { {x = 1, y = 0}, {x = 0, y = 1}, {x = -1, y = 0}, {x = 0, y = -1} }

local function parse(input)
    local state = { direction = 1 }
    local grid = {}
    local actions = {}

    local i = 1
    while input[i] and input[i] ~= '' do
        grid[i] = {}
        for j = 1, #input[i] do
            grid[i][j] = input[i]:sub(j, j)
            if grid[i][j] == '.' and not (state.x and state.y) then
                state.x, state.y = j, i
            end
        end
        i = i + 1
    end

    local op = input[i + 1]

    repeat
        local move_start, move_end = op:find("(%d+)")
        local turn_start, turn_end = op:find("(%a)")
        if move_start == 1 then
            table.insert(actions, {move = op:sub(move_start, move_end)})
            op = op:sub(move_end + 1)
        elseif turn_start == 1 then
            table.insert(actions, {turn = op:sub(turn_start, turn_end)})
            op = op:sub(turn_end + 1)
        end
    until not move_start and not turn_start

    return grid, actions, state
end

local function get_front(grid, state)
    local adj = Adj4[state.direction]
    local x, y = state.x + adj.x, state.y + adj.y
    if grid[y] and grid[y][x] and grid[y][x] ~= ' ' then
        if grid[y][x] == '#' then
            return state.x, state.y
        else
            return x, y
        end
    end

    local lx, ly = state.x, state.y
    x, y = lx, ly
    while true do
        if not grid[y] then break end
        if not grid[y][x] then break end
        if grid[y][x] == ' ' then break end
        lx, ly = x, y
        x, y = x + -adj.x, y + -adj.y
    end

    if grid[ly][lx] == '#' then
        return state.x, state.y
    end

    return lx, ly
end

local function move(grid_input, action, state_input)
    local grid = {}
    for i = 1, #grid_input do
        grid[i] = {}
        for j = 1, #grid_input[i] do grid[i][j] = grid_input[i][j] end
    end
    local state = {x = state_input.x, y = state_input.y, direction = state_input.direction}

    for _ = 1, action.move do
        local nx, ny = get_front(grid, state)
        if state.x == nx and state.y == ny then
            return grid, state
        end
        grid[state.y][state.x] = (">v<^"):sub(state.direction, state.direction)
        state.x, state.y = nx, ny
    end
    return grid, state
end

local function turn(state_input, action)
    local state = {x = state_input.x, y = state_input.y, direction = state_input.direction}
    if action.turn == "R" then
        state.direction = (state.direction) % 4 + 1
    elseif action.turn == "L" then
        state.direction = (state.direction + 2) % 4 + 1
    end
    return state
end

local function do_action(grid_input, action, state_input)
    local grid = {}
    for i = 1, #grid_input do
        grid[i] = {}
        for j = 1, #grid_input[i] do grid[i][j] = grid_input[i][j] end
    end

    local state = {x = state_input.x, y = state_input.y, direction = state_input.direction}

    if action.move then
        grid, state = move(grid, action, state)
    elseif action.turn then
        state = turn(state, action)
    end

    return grid, state
end

local input = {}
for line in io.lines() do table.insert(input, line) end

local grid, actions, state = parse(input)

for _, action in ipairs(actions) do
    --[[
    print('\n\n\n')
    for i = 1, #grid do
        for j = 1, #grid[i] do
            io.write(grid[i][j])
        end
        io.write('\n')
    end
    print(state.x, state.y, state.direction - 1)
    print('Action', action.turn, action.move)
    --]]
    grid, state = do_action(grid, action, state)
end

print(state.y * 1000 + state.x * 4 + state.direction - 1)

