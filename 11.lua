local function gcd(a, b)
	if b ~= 0 then
		return gcd(b, a % b)
	else
		return math.abs(a)
	end
end

local function lcm(a, b)
    return a * b / gcd(a, b)
end

local input = {}
for line in io.lines() do table.insert(input, line) end

local function parse(lines)
    local monkey_list = { lcm =  1}
    local linei = 1
    while linei <= #lines do
        if lines[linei] ~= '' then
            local monkey = { items = {}, activity = 0, }
            monkey.id = lines[linei]:match("Monkey (%d+):") + 1
            for token in string.gmatch(lines[linei + 1], "[^%s]+") do
                local item = token:match("(%d+),?")
                if item then table.insert(monkey.items, item) end
            end
            monkey.leftoperand, monkey.operator, monkey.rightoperand = lines[linei + 2]:match("%s*Operation: new = (.+) (.) (.+)")
            monkey.modulo = lines[linei + 3]:match("%s*Test: divisible by (%d+)")
            monkey.ontrue = lines[linei + 4]:match("%s*If true: throw to monkey (%d+)") + 1
            monkey.onfalse = lines[linei + 5]:match("%s*If false: throw to monkey (%d+)") + 1
            table.insert(monkey_list, monkey)
            monkey_list.lcm = lcm(monkey_list.lcm, monkey.modulo)
            linei = linei + 6
        else
            linei = linei + 1
        end
    end
    return monkey_list
end

local function doround(monkey_list, do_divide)
    for _, monkey in ipairs(monkey_list) do
        monkey.activity = monkey.activity + #monkey.items
        for _, item in pairs(monkey.items) do
            local leftoperand = monkey.leftoperand == 'old' and item or tonumber(monkey.leftoperand)
            local rightoperand = monkey.rightoperand == 'old' and item or tonumber(monkey.rightoperand)
            if item then
                if     monkey.operator == '+' then item = leftoperand + rightoperand
                elseif monkey.operator == '-' then item = leftoperand - rightoperand
                elseif monkey.operator == '*' then item = leftoperand * rightoperand elseif monkey.operator == '/' then item = leftoperand / rightoperand
                end
                if do_divide then item = math.floor(item / 3) end
                item = item % monkey_list.lcm
                if item % monkey.modulo == 0 then table.insert(monkey_list[monkey.ontrue].items, item)
                else                              table.insert(monkey_list[monkey.onfalse].items, item)
                end
            end
        end
        monkey.items = {}
    end
end

local part1_monkeys = parse(input)
for _ = 1, 20 do doround(part1_monkeys, true) end
table.sort(part1_monkeys, function(a, b) return a.activity > b.activity end)
io.write(part1_monkeys[1].activity * part1_monkeys[2].activity..' ')

local part2_monkeys = parse(input)
for _ = 1, 10000 do doround(part2_monkeys, false) end
table.sort(part2_monkeys, function(a, b) return a.activity > b.activity end)
print(part2_monkeys[1].activity * part2_monkeys[2].activity)

