input = open('input.txt', 'r')
values = [int(i) for i in input.readlines()]
# Part 1
prev = values[0]
increases = 0
for value in values:
    if value > prev:
        increases += 1
    prev = value

print(f'Increases: {increases}')

# Part 2
prev = values[0] + values[1] + values[2]
increases = 0
for i in range(0, len(values)):
    if i + 2 >= len(values):
        break
    sum = values[i + 0] + values[i + 1] + values[i + 2]
    if sum > prev:
        increases += 1
    prev = sum

print(f'Increases 2: {increases}')
