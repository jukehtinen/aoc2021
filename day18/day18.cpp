#include <algorithm>
#include <format>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

struct Node
{
	long xvalue{ 0 };
	long yvalue{ 0 };
	Node* xnode{ nullptr };
	Node* ynode{ nullptr };
	Node* parent{ nullptr };
};

void Parse(Node* p, const std::string& thing, int& index)
{
	char token{};
	bool left = true;
	do
	{
		token = thing[index++];
		if (token == '[')
		{
			auto n = new Node;
			n->parent = p;
			if (left)
				p->xnode = n;
			else
				p->ynode = n;
			Parse(n, thing, index);
		}
		else if (std::isdigit(token))
		{
			if (left)
				p->xvalue = token - '0';
			else
				p->yvalue = token - '0';
		}
		else if (token == ',')
		{
			left = false;
		}
	} while (token != ']' && token != '\0');
}

Node* ParseTree(const std::string& data)
{
	Node root;
	int index{ 0 };
	Parse(&root, data, index);
	return root.xnode;
}

void ToString(Node* n, std::stringstream& ss)
{
	ss << "[";
	if (n->xnode == nullptr)
		ss << n->xvalue;
	else
		ToString(n->xnode, ss);

	if (n->ynode == nullptr)
		ss << "," << n->yvalue;
	else
	{
		ss << ",";
		ToString(n->ynode, ss);
	}
	ss << "]";
}

void GetValues(Node* n, std::vector<Node*>& nodes)
{
	if (n->xnode == nullptr && n->ynode == nullptr)
		nodes.push_back(n);
	if (n->xnode == nullptr && n->ynode != nullptr)
		nodes.push_back(n);
	if (n->xnode != nullptr)
		GetValues(n->xnode, nodes);
	if (n->ynode != nullptr)
		GetValues(n->ynode, nodes);
	if (n->xnode != nullptr && n->ynode == nullptr)
		nodes.push_back(n);
}

bool Explode(Node* n, int level, const std::vector<Node*>& values)
{
	if (level >= 4 && n->xnode == nullptr && n->ynode == nullptr)
	{
		auto i = std::find(values.begin(), values.end(), n);
		size_t index = std::distance(values.begin(), i);
		if (index > 0)
			if (values[index - 1]->ynode == nullptr)
				values[index - 1]->yvalue += n->xvalue;
			else
				values[index - 1]->xvalue += n->xvalue;

		if (index < values.size() - 1)
			if (values[index + 1]->xnode == nullptr)
				values[index + 1]->xvalue += n->yvalue;
			else
				values[index + 1]->yvalue += n->yvalue;

		if (n->parent->xnode == n)
		{
			n->parent->xnode = nullptr;
			n->parent->xvalue = 0;
		}
		else
		{
			n->parent->ynode = nullptr;
			n->parent->yvalue = 0;
		}

		return true;
	}

	if (n->xnode != nullptr)
		if (Explode(n->xnode, level + 1, values)) return true;

	if (n->ynode != nullptr)
		if (Explode(n->ynode, level + 1, values)) return true;

	return false;
}

bool Split(const std::vector<Node*>& values)
{
	for (auto v : values)
	{
		if (v->xnode == nullptr && v->xvalue >= 10)
		{
			v->xnode = new Node;
			v->xnode->parent = v;
			v->xnode->xvalue = (long)floor((double)v->xvalue / 2.0);
			v->xnode->yvalue = (long)ceil((double)v->xvalue / 2.0);
			v->xvalue = 0;
			return true;
		}
		if (v->ynode == nullptr && v->yvalue >= 10)
		{
			v->ynode = new Node;
			v->ynode->parent = v;
			v->ynode->xvalue = (long)floor((double)v->yvalue / 2.0);
			v->ynode->yvalue = (long)ceil((double)v->yvalue / 2.0);
			v->yvalue = 0;
			return true;
		}

	}
	return false;
}

Node* Reduce(Node* tree)
{
	while (true)
	{
		std::vector<Node*> values;
		GetValues(tree, values);
		if (Explode(tree, 0, values))
			continue;

		if (Split(values))
			continue;

		break;
	}
	return tree;
}


long GetMagnitude(Node* n)
{
	long x = n->xnode != nullptr ? GetMagnitude(n->xnode) : n->xvalue;
	long y = n->ynode != nullptr ? GetMagnitude(n->ynode) : n->yvalue;
	return x * 3 + y * 2;
}

int main()
{
	std::ifstream inputFile("input.txt");

	// Part 1
	std::vector<std::string> lines;
	std::string prevLine;
	std::string line;
	int magnitude = 0;
	while (std::getline(inputFile, line))
	{
		lines.push_back(line);
		if (prevLine.length() != 0)
		{
			auto tree = Reduce(ParseTree(std::format("[{},{}]", prevLine, line)));
			magnitude = GetMagnitude(tree);
			std::stringstream ss;
			ToString(tree, ss);
			prevLine = ss.str();
		}
		else
		{
			prevLine = line;
		}
	}
	std::cout << std::format("Part 1: {}\n", magnitude);

	// Part 2
	int largest = 0;
	for (int i = 0; i < lines.size(); i++)
	{
		for (int j = 0; j < lines.size(); j++)
		{
			if (j == i) continue;

			int a = GetMagnitude(Reduce(ParseTree(std::format("[{},{}]", lines[i], lines[j]))));
			int b = GetMagnitude(Reduce(ParseTree(std::format("[{},{}]", lines[j], lines[i]))));
			if (a > largest) largest = a;
			if (b > largest) largest = b;

		}
	}
	std::cout << std::format("Part 2: {}\n", largest);


	return 0;
}
