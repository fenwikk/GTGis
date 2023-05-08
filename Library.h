#pragma once

#include <vector>
#include <string>

#include "Fighter.h"
#include <wtypes.h>

void Clear();

void ChangeConsoleColor(int colorId);

void Logo();

void Write(std::string s);

void WaitForEnterPress();

void Row(std::string row[], int numberOfColumns, int maxChars = 75);

int Menu(std::string labels[], int numberOfLabels, bool disabled[] = nullptr);

Fighter **SortFightersBySpeed(Fighter **fighters);