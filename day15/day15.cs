using Map = System.Collections.Generic.Dictionary<(int x, int y), Node>;

var input = File.ReadAllLines("input.txt");
var mapSize = input[0].Length;
var mapData = string.Join("", input);

Map GetMap()
{
    var map = new Map();
    for (var i = 0; i < mapData.Length; i++)
    {
        var x = i % mapSize;
        var y = i / mapSize;
        map[(x, y)] = new Node
        {
            Risk = int.Parse(mapData[i].ToString()),
            X = x,
            Y = y,
        };
    }

    return map;
}

Map EnlargeMap(Map map)
{
    for (var l = 0; l < 5; l++)
        for (var i = 0; i < 5; i++)
            for (var y = 0; y < mapSize; y++)
                for (var x = 0; x < mapSize; x++)
                {
                    var node = map[(x, y)];
                    var newRisk = node.Risk + l + i;
                    map[(i * mapSize + x, l * mapSize + y)] = new Node
                    {
                        Risk = newRisk > 9 ? newRisk - 9 : newRisk,
                        X = i * mapSize + x,
                        Y = l * mapSize + y
                    };
                }


    return map;
}

static int FindPathCost(Map map, int targetX, int targetY)
{
    var frontier = new PriorityQueue<Node, int>();
    frontier.Enqueue(map[(0, 0)], 0);
    while (frontier.Count > 0)
    {
        var current = frontier.Dequeue();
        if (current.X == targetX && current.Y == targetY)
            return current.Cost;

        foreach (var next in GetAdjacent(current, map))
        {
            var newCost = current.Cost + next.Risk;
            if (next.Cost == 0 || newCost < next.Cost)
            {
                next.Cost = newCost;
                frontier.Enqueue(next, newCost + Math.Abs(next.X - targetX) + Math.Abs(next.Y - targetY));
            }
        }
    }

    return -1;
}

static IEnumerable<Node> GetAdjacent(Node current, Map map)
{
    var mapSize = Math.Sqrt(map.Count);
    var nodes = new List<Node>();
    if (current.Y > 0) nodes.Add(map[(current.X, current.Y - 1)]);
    if (current.Y < mapSize * 1 - 1) nodes.Add(map[(current.X, current.Y + 1)]);
    if (current.X > 0) nodes.Add(map[(current.X - 1, current.Y)]);
    if (current.X < mapSize * 1 - 1) nodes.Add(map[(current.X + 1, current.Y)]);
    return nodes;
}

Console.WriteLine($"Part 1: {FindPathCost(GetMap(), 99, 99)}");
Console.WriteLine($"Part 2: {FindPathCost(EnlargeMap(GetMap()), 100 * 5 - 1, 100 * 5 - 1)}");

class Node
{
    public int X { get; set; }
    public int Y { get; set; }
    public int Risk { get; set; }
    public int Cost { get; set; }
}
