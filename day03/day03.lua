lines = {}
for line in io.lines("input.txt") do table.insert(lines, line) end

-- Part 1
gamma = ""
for i = 1, #lines[1] do
    local ones = 0
    for _, v in ipairs(lines) do
        if string.sub(v, i, i) == "1" then ones = ones + 1 end
    end
    if ones > #lines / 2 then
        gamma = gamma .. "1"
    else
        gamma = gamma .. "0"
    end
end

print("Part 1", tonumber(gamma, 2) * (~tonumber(gamma, 2) & (2 ^ #lines[1] - 1)))

-- Part 2
function divide_groups(rows, index)
    local zeroes = {}
    local ones = {}
    for _, v in ipairs(rows) do
        if string.sub(v, index, index) == "1" then
            table.insert(ones, v)
        else
            table.insert(zeroes, v)
        end
    end
    return zeroes, ones
end

currentList = lines
for i = 1, #lines[1] do
    local zeroes, ones = divide_groups(currentList, i)
    if #ones >= #zeroes then
        currentList = ones
    else
        currentList = zeroes
    end
    if #currentList == 1 then oxygen = tonumber(currentList[1], 2) end
end

currentList = lines
for i = 1, #lines[1] do
    local zeroes, ones = divide_groups(currentList, i)
    if #ones >= #zeroes then
        currentList = zeroes
    else
        currentList = ones
    end
    if #currentList == 1 then co2 = tonumber(currentList[1], 2) end
end

print("Part 2", oxygen * co2)
