using Map = System.Collections.Generic.Dictionary<(int x, int y), bool>;

var lines = File.ReadAllLines("input.txt");
var iea = lines[0];

var map = new Map();
for (var i = 2; i < lines.Length; i++)
    for (var x = 0; x < lines[i].Length; x++)
        map[(x, i - 2)] = lines[i][x] == '#';

var minx = -1;
var miny = -1;
var maxx = lines[2].Length + 1;
var maxy = lines.Length - 1;

static bool IsLight(Map map, int px, int py, string iea, int iteration)
{
    var value = 0;
    int index = 0;
    for (var y = py - 1; y < py + 2; y++)
    {
        for (var x = px - 1; x < px + 2; x++)
        {
            index++;
            // Sample data case, infinity stays '.'
            if (iea[0] == '.')
            {
                if (map.ContainsKey((x, y)) && map[(x, y)])
                    value |= 1 << 9 - index;
            }
            else
            {
                if (map.ContainsKey((x, y)))
                {
                    // Inside the known area, use the map
                    if (map[(x, y)])
                        value |= 1 << 9 - index;
                }
                else
                {
                    // Outside the known area, it seems to flip-flip between iterations.
                    if (iteration % 2 == 1)
                        value |= 1 << 9 - index;
                }
            }
        }
    }

    return iea[value] == '#';
}

Map Enhance(Map inputMap, int iteration)
{
    var newMap = new Map();
    for (var y = miny; y < maxy; y++)
    {
        for (var x = minx; x < maxx; x++)
        {
            newMap[(x, y)] = IsLight(inputMap, x, y, iea, iteration);
        }
    }

    minx -= 1;
    miny -= 1;
    maxx += 1;
    maxy += 1;

    return newMap;
}

var map2 = Enhance(Enhance(map, 0), 1);
Console.WriteLine($"Part 1: {map2.Count(x => x.Value)}");

var m = map;
for (var i = 0; i < 50; i++)
    m = Enhance(m, i);
Console.WriteLine($"Part 2: {m.Count(x => x.Value)}");