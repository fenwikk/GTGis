#pragma once

#include <vector>
#include <string>
#include <functional>

struct PointMatrixElement {
public:
	std::string label;
	double points;
};

void Clear();

void Row(std::vector<std::string> row);
void Row(std::vector<std::string> row, int maxChars);

int Menu(std::vector<std::string> labels);
int Menu(std::vector<std::string> labels, std::function<void()> before);
int Menu(std::vector<std::string> labels, std::function<void()> before, bool inlineLabels);

std::string NameInput(int numberOfCharacters);
std::vector<PointMatrixElement> DistributePoints();