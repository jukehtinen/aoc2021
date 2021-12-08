var input = File.ReadAllLines("input.txt");

// Part 1
var sum = input.Sum(line => line.Split('|')[1]
    .Split(' ', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
    .Where(i => i.Length == 2 || i.Length == 3 || i.Length == 4 || i.Length == 7).Count());

Console.WriteLine($"Part 1: {sum}");

// Part 2
var sum2 = 0;
foreach (var line in input)
{
    var signals = line.Split('|')[0]
        .Split(' ', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
        .Select(l => string.Concat(l.OrderBy(c => c))).ToList();

    var digits = line.Split('|')[1]
        .Split(' ', StringSplitOptions.RemoveEmptyEntries | StringSplitOptions.TrimEntries)
        .Select(l => string.Concat(l.OrderBy(c => c))).ToList();

    string Has(int len, string n)
    {
        var signal = signals.First(s => s.Length == len && n.All(c => s.Contains(c)));
        signals.Remove(signal);
        return signal;
    }

    var numbers = new string[10];
    numbers[1] = signals.First(s => s.Length == 2);
    numbers[4] = signals.First(s => s.Length == 4);
    numbers[7] = signals.First(s => s.Length == 3);
    numbers[8] = signals.First(s => s.Length == 7);
    numbers[3] = Has(5, numbers[1]);
    numbers[9] = Has(6, numbers[4]);
    numbers[0] = Has(6, numbers[1]);
    numbers[6] = Has(6, "");
    numbers[5] = signals.First(s => s.Length == 5 && s.All(c => numbers[6].Contains(c)));
    numbers[2] = signals.First(s => s.Length == 5 && !s.All(c => numbers[6].Contains(c)));

    var number = "";
    foreach (var digit in digits)
        number += numbers.ToList().IndexOf(digit);
    sum2 += int.Parse(number);
}

Console.WriteLine($"Part 2: {sum2}");