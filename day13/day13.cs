using System.Text.RegularExpressions;

var map = new HashSet<(int x, int y)>();
var instructions = new List<(string dir, int index)>();

var rgPoint = new Regex(@"(\d+),(\d+)");
var rgInstruction = new Regex(@"fold along (\w)=(\d+)");

foreach (var line in File.ReadAllLines("input.txt"))
{
    var match = rgPoint.Match(line);
    if (match.Success)
        map.Add(new(int.Parse(match.Groups[1].Value), int.Parse(match.Groups[2].Value)));

    var matchInstruction = rgInstruction.Match(line);
    if (matchInstruction.Success)
        instructions.Add(new(matchInstruction.Groups[1].Value, int.Parse(matchInstruction.Groups[2].Value)));
}

static HashSet<(int x, int y)> Fold(HashSet<(int x, int y)> map, string dir, int index)
{
    var newmap = new HashSet<(int x, int y)>();
    foreach ((int x, int y) in map)
    {
        if (dir == "y")
        {
            if (y > index)
                newmap.Add(new(x, index - (y - index)));
            else
                newmap.Add(new(x, y));
        }
        else
        {
            if (x > index)
                newmap.Add(new(index - (x - index), y));
            else
                newmap.Add(new(x, y));
        }
    }
    return newmap;
}

// Part 1
var newmap = Fold(map, instructions[0].dir, instructions[0].index);
Console.WriteLine($"Part 1: {newmap.Count}");

// Part 2
var next = map;
foreach (var instr in instructions)
{
    next = Fold(next, instr.dir, instr.index);
}

Console.WriteLine($"Part 2:");
for (int y = 0; y < next.MaxBy(n => n.y).y + 1; y++)
{
    for (int x = 0; x < next.MaxBy(n => n.x).x + 1; x++)
        Console.Write(next.Any(p => p.x == x && p.y == y) ? "#" : ".");
    Console.WriteLine("");
}