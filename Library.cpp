#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <format>
#include <windows.h>

#include "Error.h"
#include "Fighter.h"
#include "Library.h"
#include "Game.h"

void Clear() {
	system("CLS");

	Logo();

	if (Game::started)
		Game::Stats();
}

void Write(std::string s) {
	for (size_t i = 0; i < s.size(); i++) {
		std::cout << s[i];
		Sleep(25);
	}
}

void WaitForEnterPress() {
	std::cout << "\nPress enter to continue...\r";

	bool enterPressed = false;
	while (!enterPressed) {
		if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
			enterPressed = true;

			while (GetAsyncKeyState(VK_RETURN) & 0x8000);
		}
	}

	std::cout << "                          \r";
}

void Logo() {
	std::cout << ",-----------------------------------------------------------------------,\n";
	std::cout << "|            ___________.__       .__     __                            |\n";
	std::cout << "|            \\_   _____/|__| ____ |  |___/  |_  ___________             |\n";
	std::cout << "|             |    __)  |  |/ ___\\|  |  \\   __\\/ __ \\_  __ \\            |\n";
	std::cout << "|             |     \\   |  / /_/  >   Y  \\  | \\  ___/|  | \\/            |\n";
	std::cout << "|             \\___  /   |__\\___  /|___|  /__|  \\___  >__|               |\n";
	std::cout << "|                 \\/      /_____/      \\/          \\/                   |\n";
	std::cout << "|                                                                       |\n";
	std::cout << "'-----------------------------------------------------------------------'\n\n";
}

void Row(std::string row[], int numberOfColumns, int maxChars) {
	for (size_t i = 0; i < numberOfColumns; i++)
	{
		std::string cell = row[i];

		std::string space = "";
		for (size_t i = 0; i < (maxChars / numberOfColumns - cell.length()); i++) {
			space += " ";
		}
		std::cout << cell + space;
	}

	std::cout << std::endl;
}

int Menu(std::string labels[], int numberOfLabels, std::vector<bool> disabled) {
	if (disabled.size() < numberOfLabels)
		for (size_t i = disabled.size(); i < numberOfLabels; i++) {
			disabled.push_back(false);
		}

	bool submitted = false;
	int selectedIndex = 0;

	while (disabled[selectedIndex] && selectedIndex <= (numberOfLabels - 1)) {
		selectedIndex++;
	}
	if (selectedIndex > (numberOfLabels - 1))
		throw new Error("Menu only has disabled items.");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!submitted) {
		std::cout << "\r";

		for (size_t i = 0; i < numberOfLabels; i++) {
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << (selectedIndex == i ? ">" : " ");
			SetConsoleTextAttribute(hConsole, (disabled[i] ? 7 : 15));
			std::cout << labels[i];
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << (selectedIndex == i ? "<" : " ");
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}

		bool commandPressed = false;
		while (!commandPressed) {
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && selectedIndex > 0) {
				int originalIndex = selectedIndex;
				selectedIndex--;
				while (selectedIndex >= 0 && disabled[selectedIndex]) {
					selectedIndex--;
				}
				if (selectedIndex < 0)
					selectedIndex = originalIndex;

				commandPressed = true;

				while (GetAsyncKeyState(VK_LEFT) & 0x8000);
			}
			if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && selectedIndex < (numberOfLabels - 1)) {
				int originalIndex = selectedIndex;
				selectedIndex++;
				while (selectedIndex <= (numberOfLabels - 1) && disabled[selectedIndex]) {
					selectedIndex++;
				}
				if (selectedIndex > (numberOfLabels - 1))
					selectedIndex = originalIndex;

				commandPressed = true;

				while (GetAsyncKeyState(VK_RIGHT) & 0x8000);
			}
			if ((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
				submitted = true;
				commandPressed = true;

				while (GetAsyncKeyState(VK_RETURN) & 0x8000);
			}
		}
	}

	return selectedIndex;
}

Fighter** SortFightersBySpeed(Fighter** fighters) {
	bool fightersSorted = false;

	while (!fightersSorted) {
		fightersSorted = true;
		for (size_t i = 1; i < 5; i++) {
			if (fighters[i] != nullptr) {
				if (fighters[i - 1] == nullptr || fighters[i]->GetSpeed() > fighters[i - 1]->GetSpeed()) {
					Fighter* tempFighter = fighters[i];
					fighters[i] = fighters[i - 1];
					fighters[i - 1] = tempFighter;

					fightersSorted = false;
				}
			}
		}
	}

	return fighters;
}