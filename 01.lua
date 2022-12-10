local cur = 0
local elves = {}

for line in io.lines()
do
    if line == ""
    then
        table.insert(elves, cur)
        cur = 0
    else
        cur = cur + tonumber(line)
    end
end

table.sort(elves, function(a, b) return a > b end)

print(elves[1], elves[1] + elves[2] + elves[3])

