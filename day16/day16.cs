using System.Text;

var input = File.ReadAllText("input.txt");
var builder = new StringBuilder();
foreach (var c in input)
{
    int intValue = int.Parse(c.ToString(), System.Globalization.NumberStyles.HexNumber);
    builder.Append(Convert.ToString(intValue, 2).PadLeft(4, '0'));
}

var binary = builder.ToString();
int versionSum = 0;
int index = 0;

string Next(int n)
{
    var chunk = binary[index..(index + n)];
    index += n;
    return chunk;
}

long Parse()
{
    while (true)
    {
        int version = Convert.ToInt32(Next(3), 2);
        versionSum += version;

        int type = Convert.ToInt32(Next(3), 2);
        if (type == 4)
        {
            var chunk = Next(5);
            string literal = chunk[1..5];
            while (chunk[0] == '1')
            {
                chunk = Next(5);
                literal += chunk[1..5];
            }
            return Convert.ToInt64(literal, 2);
        }
        else
        {
            int lengthType = Convert.ToInt32(Next(1), 2);
            var values = new List<long>();
            if (lengthType == 0)
            {
                int totalLength = Convert.ToInt32(Next(15), 2);
                int endIndex = index + totalLength;
                while (index < endIndex)
                    values.Add(Parse());
            }
            else
            {
                int subPackets = Convert.ToInt32(Next(11), 2);
                for (int i = 0; i < subPackets; i++)
                    values.Add(Parse());
            }

            if (type == 0)
                return values.Sum();
            else if (type == 1)
                return values.Aggregate((a, b) => a * b);
            else if (type == 2)
                return values.Min();
            else if (type == 3)
                return values.Max();
            else if (type == 5)
                return values[0] > values[1] ? 1 : 0;
            else if (type == 6)
                return values[0] < values[1] ? 1 : 0;
            else if (type == 7)
                return values[0] == values[1] ? 1 : 0;
        }
    }
}

Console.WriteLine($"Part 2: {Parse()}");
Console.WriteLine($"Part 1: {versionSum}");
