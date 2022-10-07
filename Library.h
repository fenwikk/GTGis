#pragma once

#include <vector>
#include <string>
#include <functional>

#include "Fighter.h"

struct PointMatrixElement {
public:
	std::string label;
	double points;
};

void Clear();

void Logo();

void WaitForEnterPress();

void Row(std::vector<std::string> row, int maxChars = 75);

int Menu(std::vector<std::string> labels, std::vector<bool> disabled = {});

void Stats();

std::string NameInput(int numberOfCharacters);
std::vector<PointMatrixElement> DistributePoints(int availablePoints, std::string playerName, int playerNumber);

Fighter** SortFightersBySpeed(Fighter** fighters);