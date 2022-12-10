Type = { Directory = 1, File = 2 }

local function make_directory(name, parent)
    return {
        type = Type.Directory,
        name = name,
        children = {},
        childmap = {},
        size = 0,
        parent = parent
    }
end

local function make_file(name, size, parent)
    return {
        type = Type.File,
        name = name,
        size = size,
        parent = parent
    }
end

local function update_size(node, delta)
    local stack = { node }

    while #stack > 0 do
        local entity = table.remove(stack)
        entity.size = entity.size + delta
        if entity.parent then
            table.insert(stack, entity.parent)
        end
    end
end

local function add_to_directory(parent, child)
    table.insert(parent.children, child)
    update_size(parent, child.size)
    if child.type == Type.Directory then
        parent.childmap[child.name] = child
    end
end

local function dfs_directory(root)
    local stack = { root }
    local result = {}

    while #stack > 0 do
        local entity = table.remove(stack)
        table.insert(result, entity)
        if entity.type == Type.Directory then
            for _, child in ipairs(entity.children) do
                table.insert(stack, child)
            end
        end
    end

    return result
end

local root = make_directory('/', nil)
local cwd = root

for line in io.lines() do
    if line:sub(3, 4) == 'cd' then
        local path = line:match("$%scd%s+(.+)")
        if path == '..' then
            cwd = cwd.parent
        elseif path == '/' then
            cwd = root
        else
            if root.childmap[path] == nil then
                add_to_directory(cwd, make_directory(path, cwd))
            end
            cwd = cwd.childmap[path]
        end
    elseif line:sub(3, 4) == 'ls' then
    elseif line:sub(1, 3) == 'dir' then
        local name = line:match("dir%s+(.+)%s*")
        add_to_directory(cwd, make_directory(name, cwd))
    elseif line ~= '' then
        local size, name = line:match("(%d+)%s(.+)%s*")
        size = tonumber(size)
        add_to_directory(cwd, make_file(name, size, cwd))
    end
end

local all_entity = dfs_directory(root)

-- part 1
local sub_1e5 = 0
for _, ent in ipairs(all_entity) do
    if ent.size <= 100000 and ent.type == Type.Directory then
        sub_1e5 = sub_1e5 + ent.size
    end
end

-- part 2
local total_disk = 70000000
local need_available = 30000000
local min_delete = need_available - (total_disk - root.size)
local to_delete = total_disk

for _, ent in ipairs(all_entity) do
    if ent.type == Type.Directory and ent.size >= min_delete and ent.size < to_delete then
        to_delete = ent.size
    end
end

print(string.format("%d %d", sub_1e5, to_delete))


