#pragma once

#include <vector>
#include <string>

#include "Fighter.h"

void Clear();

void Logo();

void Write(std::string s);

void WaitForEnterPress();

void Row(std::string row[], int numberOfColumns, int maxChars = 75);

int Menu(std::string labels[], int numberOfLabels, std::vector<bool> disabled = {});

Fighter** SortFightersBySpeed(Fighter** fighters);