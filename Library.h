#pragma once

#include <vector>
#include <string>

#include "Fighter.h"

void Clear();

void Logo();

void Write(std::string s);

void WaitForEnterPress();

void Row(std::vector<std::string> row, int maxChars = 75);

int Menu(std::vector<std::string> labels, std::vector<bool> disabled = {});

Fighter** SortFightersBySpeed(Fighter** fighters);