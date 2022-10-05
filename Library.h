#pragma once

#include <vector>
#include <string>
#include <functional>

struct MenuItem {
public:

};

struct PointMatrixElement {
public:
	std::string label;
	double points;
};

void Clear();

void Logo();

void Row(std::vector<std::string> row);
void Row(std::vector<std::string> row, int maxChars);

int Menu(std::vector<std::string> labels);

void Stats();

std::string NameInput(int numberOfCharacters);
std::vector<PointMatrixElement> DistributePoints(int availablePoints, std::string playerName, int playerNumber);