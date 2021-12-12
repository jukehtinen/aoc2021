#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <map>
#include <queue>
#include <ranges>
#include <set>

struct Edge
{
	std::string a;
	std::string b;
};

using Edges = std::vector<Edge>;
using NodeQueue = std::queue<std::string>;
using Paths = std::set<std::string>;
using Visited = std::map<std::string, int>;

void RecursePaths(const Edges& edges, const std::string& node, const std::string& target, Visited visited, NodeQueue path, Paths& pathsFound)
{
	if (std::islower(node[0]))
	{
		if (node == "start" || node == "end")
			visited[node] = 2;
		else if (visited.find(node) != visited.end())
			visited[node] = visited[node] + 1;
		else
			visited[node] = 1;
	}

	path.push(node);

	if (node == target)
	{
		std::string pathStr;
		while (!path.empty())
		{
			pathStr += path.front() + " ";
			path.pop();
		}
		pathsFound.insert(pathStr);
	}
	else
	{
		auto adjancent = edges | std::views::filter([&node](auto& a) {return a.a == node || a.b == node; });
		for (const auto& adj : adjancent)
		{
			const auto& n = adj.a == node ? adj.b : adj.a;
			auto visit = visited.find(n);
			if (visit == visited.end() || (*visit).second < 1)
				RecursePaths(edges, n, target, visited, path, pathsFound);
		}
	}
}

int main()
{
	std::ifstream inputFile("D:\\code\\aoc2021\\day12\\input.txt");

	Edges edges;

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::smatch matches;
		if (std::regex_search(line, matches, std::regex{ "(\\w+)-(\\w+)" }))
			edges.emplace_back(Edge{ matches[1] , matches[2] });
	}

	// Part 1
	Visited visited;
	NodeQueue path;
	Paths foundPaths;
	RecursePaths(edges, "start", "end", visited, path, foundPaths);

	for (auto& p : foundPaths)
		std::cout << std::format("{}\n", p);

	std::cout << std::format("Part 1: {}", foundPaths.size());

	// Part 2
	std::set<std::string> smallCaves;
	for (auto& e : edges)
	{
		if (std::islower(e.a[0]))
			smallCaves.insert(e.a);
		if (std::islower(e.b[0]))
			smallCaves.insert(e.b);
	}

	Paths foundPaths2;
	for (auto& sc : smallCaves)
	{
		Visited visited2;
		NodeQueue path2;
		visited2[sc] = -1;
		RecursePaths(edges, "start", "end", visited2, path2, foundPaths2);
	}

	for (auto& p : foundPaths2)
		std::cout << std::format("{}\n", p);

	std::cout << std::format("Part 2: {}", foundPaths2.size());

	return 0;
}
