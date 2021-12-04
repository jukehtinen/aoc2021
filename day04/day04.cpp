#include <algorithm>
#include <format>
#include <fstream>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>

std::vector<std::string> Split(std::string_view str, std::string_view delim);
std::vector<int> ToInts(const std::vector<std::string> strs);

bool IsBingo(const std::vector<bool>& marks)
{
	for (int y = 0; y < 5; y++)
		if (marks[y * 5 + 0] && marks[y * 5 + 1] && marks[y * 5 + 2] && marks[y * 5 + 3] && marks[y * 5 + 4])
			return true;

	for (int x = 0; x < 5; x++)
		if (marks[0 * 5 + x] && marks[1 * 5 + x] && marks[2 * 5 + x] && marks[3 * 5 + x] && marks[4 * 5 + x])
			return true;

	return false;
}

int GetScore(const std::vector<int>& board, const std::vector<bool>& marks, int lastNumber)
{
	int score{};
	for (int i = 0; i < marks.size(); i++)
		if (!marks[i]) score += board[i];
	return score * lastNumber;
}

int main()
{
	std::ifstream inputFile("D:/code/aoc2021/day04/input.txt");
	std::string line;
	std::getline(inputFile, line);

	auto numbers = ToInts(Split(line, ","));

	int bestScore{};
	int bestIndex = 9999;
	int worstScore{};
	int worstIndex = 0;

	std::vector<int> board;
	while (std::getline(inputFile, line))
	{
		auto row = ToInts(Split(line, " "));
		board.insert(board.end(), row.begin(), row.end());

		if (board.size() == 25)
		{
			std::vector<bool> marks(25, false);
			for (int i = 0; i < numbers.size(); i++)
			{
				auto iter = std::find(board.begin(), board.end(), numbers[i]);
				if (iter == board.end())
					continue;

				marks[std::distance(board.begin(), iter)] = true;
				if (IsBingo(marks))
				{
					auto score = GetScore(board, marks, numbers[i]);
					if (i < bestIndex)
					{
						bestIndex = i;
						bestScore = score;
					}
					if (i > worstIndex)
					{
						worstIndex = i;
						worstScore = score;
					}
					break;
				}
			}
			board.clear();
		}
	}

	std::cout << std::format("Part 1: {}\n", bestScore);
	std::cout << std::format("Part 2: {}\n", worstScore);

	return 0;
}

std::vector<std::string> Split(std::string_view str, std::string_view delim)
{
	std::vector<std::string> result;
	size_t last = 0;
	size_t next = 0;
	while ((next = str.find(delim, last)) != std::string::npos)
	{
		result.push_back(std::string{ str.substr(last, next - last) });
		last = next + 1;
	}
	result.push_back(std::string{ str.substr(last) });
	result.erase(std::remove_if(result.begin(), result.end(), [](const std::string& s) { return s.length() == 0; }), result.end());

	return result;
}

std::vector<int> ToInts(const std::vector<std::string> strs)
{
	std::vector<int> numbers;
	std::transform(strs.begin(), strs.end(), std::back_inserter(numbers), [](const std::string& s) -> int { return std::stoi(s); });
	return numbers;
}
