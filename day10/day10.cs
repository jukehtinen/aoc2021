var lines = File.ReadAllLines("input.txt");

int scorePart1 = 0;
var scorePart2 = new List<long>();

// Part 1
foreach (var line in lines)
{
    var stack = new Stack<char>();
    var corrupted = false;
    for (int i = 0; i < line.Length; i++)
    {
        if (line[i] == '(' || line[i] == '{' || line[i] == '<' || line[i] == '[')
        {
            stack.Push(line[i]);
        }
        else if (line[i] == ')' || line[i] == '}' || line[i] == '>' || line[i] == ']')
        {
            var chr = stack.Pop();
            if ((chr == '(' && line[i] != ')') || (chr == '{' && line[i] != '}') || (chr == '<' && line[i] != '>') || (chr == '[' && line[i] != ']'))
            {
                Console.WriteLine($"error at {i}, found {line[i]}");
                if (line[i] == ')') scorePart1 += 3;
                if (line[i] == ']') scorePart1 += 57;
                if (line[i] == '}') scorePart1 += 1197;
                if (line[i] == '>') scorePart1 += 25137;
                corrupted = true;
                break;
            }
        }
    }

    // Part 2
    if (!corrupted)
    {
        var completed = "";
        while (stack.Any())
        {
            var chr = stack.Pop();
            if (chr == '(') completed += ')';
            if (chr == '{') completed += '}';
            if (chr == '<') completed += '>';
            if (chr == '[') completed += ']';
        }
        long score = 0;
        for (int i = 0; i < completed.Length; i++)
        {
            score *= 5;
            if (completed[i] == ')') score += 1;
            if (completed[i] == ']') score += 2;
            if (completed[i] == '}') score += 3;
            if (completed[i] == '>') score += 4;
        }
        scorePart2.Add(score);
        scorePart2.Sort();
    }
}

Console.WriteLine($"Part 1: {scorePart1}");
Console.WriteLine($"Part 2: {scorePart2[scorePart2.Count / 2]}");
