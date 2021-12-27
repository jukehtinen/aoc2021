#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

std::string Step(const std::string& map, int width, int height)
{
	std::string newmap(map.length(), '.');
	for (int i = 0; i < map.length(); i++)
	{
		int x = i % width;
		int y = i / width;

		if (map[i] == '>')
		{
			x++;
			if (x >= width) x = 0;

			if (map[y * width + x] == '.')
				newmap[y * width + x] = '>';
			else
				newmap[i] = '>';
		}
	}

	for (int i = 0; i < map.length(); i++)
	{
		int x = i % width;
		int y = i / width;

		if (map[i] == 'v')
		{
			y++;
			if (y >= height) y = 0;

			if (newmap[y * width + x] == '.' && map[y * width + x] != 'v')
				newmap[y * width + x] = 'v';
			else
				newmap[i] = 'v';
		}
	}
	return newmap;
}

int main()
{
	std::ifstream inputFile("D:\\code\\aoc2021\\day25\\input.txt");

	std::string line;
	std::stringstream data;
	int width = 0;
	int height = 0;
	while (std::getline(inputFile, line))
	{
		width = (int)line.length();
		height++;
		data << line;
	}

	// Part 1	
	std::string map = data.str();
	int steps = 0;

	while (true)
	{
		steps++;
		auto newmap = Step(map, width, height);
		if (newmap == map)
			break;

		map = newmap;
	}
	std::cout << std::format("Part 1: {}\n", steps);

	// Part 2
	// Need more stars!

	return 0;
}
