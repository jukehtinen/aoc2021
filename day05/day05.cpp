#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <iostream>
#include <regex>
#include <map>

void DrawLines(std::map<std::string, int>& coords, int x1, int y1, int x2, int y2, bool part2)
{
	if ((x1 == x2 || y1 == y2) || part2)
	{
		coords[std::format("{},{}", x1, y1)]++;
		while (x1 != x2 || y1 != y2)
		{
			if (x1 != x2) x1 = x1 > x2 ? x1 - 1 : x1 + 1;
			if (y1 != y2) y1 = y1 > y2 ? y1 - 1 : y1 + 1;
			coords[std::format("{},{}", x1, y1)]++;
		}
	}
}

int main()
{
	std::ifstream inputFile("input.txt");

	std::map<std::string, int> coordsPart1;
	std::map<std::string, int> coordsPart2;

	std::string line;
	while (std::getline(inputFile, line))
	{
		std::smatch matches;
		if (std::regex_search(line, matches, std::regex{ "(\\d+),(\\d+) -> (\\d+),(\\d+)" }))
		{
			int x1 = std::stoi(matches[1]);
			int y1 = std::stoi(matches[2]);
			int x2 = std::stoi(matches[3]);
			int y2 = std::stoi(matches[4]);
			DrawLines(coordsPart1, x1, y1, x2, y2, false);
			DrawLines(coordsPart2, x1, y1, x2, y2, true);
		}
	}

	int twoOrLarger{};
	for (auto& c : coordsPart1)
		if (c.second > 1) twoOrLarger++;
	std::cout << std::format("Part 1: {}\n", twoOrLarger);

	twoOrLarger = 0;
	for (auto& c : coordsPart2)
		if (c.second > 1) twoOrLarger++;
	std::cout << std::format("Part 2: {}", twoOrLarger);

	return 0;
}