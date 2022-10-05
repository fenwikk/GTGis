#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <format>
#include <windows.h>

#include "Fighter.h"
#include "Library.h"
#include "Game.h"

void Clear() {
	system("CLS");

	Logo();

	if (Game::started)
		Stats();
}

void Logo() {
	std::cout << ",---------------------------------------------------------------------,\n";
	std::cout << "|                ___________________________.__                       |\n";
	std::cout << "|               /  _____/\\__    ___/  _____/|__| ______               |\n";
	std::cout << "|              /   \\  ___  |    | /   \\  ___|  |/  ___/               |\n";
	std::cout << "|              \\    \\_\\  \\ |    | \\    \\_\\  \\  |\\___ \\                |\n";
	std::cout << "|               \\______  / |____|  \\______  /__/____  >               |\n";
	std::cout << "|                      \\/                 \\/        \\/                |\n";
	std::cout << "'---------------------------------------------------------------------'\n\n";
}

void Row(std::vector<std::string> row) {
	Row(row, 75);
}
void Row(std::vector<std::string> row, int maxChars) {
	for (size_t i = 0; i < row.size(); i++)
	{
		std::string cell = row[i];

		std::string space = "";
		for (size_t i = 0; i < (maxChars / row.size() - cell.length()); i++) {
			space += " ";
		}
		std::cout << cell + space;
	}

	std::cout << std::endl;
}

int Menu(std::vector<std::string> labels) {
	bool submitted = false;
	int selectedIndex = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (!submitted) {
		std::cout << "\r";

		for (size_t i = 0; i < labels.size(); i++) {

			SetConsoleTextAttribute(hConsole, 12);
			std::cout << (selectedIndex == i ? ">" : " ");
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << labels[i];
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << (selectedIndex == i ? "<" : " ");
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "  ";
		}

		bool commandPressed = false;
		while (!commandPressed) {
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && selectedIndex > 0) {
				selectedIndex--;
				commandPressed = true;

				while (GetAsyncKeyState(VK_LEFT) & 0x8000);
			}
			if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) && selectedIndex < (labels.size() - 1)) {
				selectedIndex++;
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

void Stats() {
	std::vector<std::string> names = {};
	std::vector<std::string> hp = {};
	std::vector<std::string> defense = {};
	std::vector<std::string> strength = {};
	std::vector<std::string> speed = {};
	for (size_t i = 0; i < 5; i++) {
		if (Game::players[i] != nullptr) {
			Fighter* player = Game::players[i];

			names.push_back("   <" + Game::players[i]->name + ">");
			hp.push_back(player->GenHpBar(11));
			defense.push_back("def:  " + std::format("{:05.2f}", player->defense)); 
			strength.push_back("str:  " + std::format("{:05.2f}", player->strength));
			speed.push_back("spd:  " + std::format("{:05.2f}", player->speed));      
		}
		else {
			names.push_back("");
			hp.push_back("");
			defense.push_back("");
			strength.push_back("");
			speed.push_back("");
		}
	}

	Row(names);
	Row(hp);
	std::cout << "\n";
	Row(defense);
	Row(strength);
	Row(speed);
}

std::string NameInput(int numberOfCharacters) {
	std::string characterSet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string input = "";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t currentCharacterIndex = 0; currentCharacterIndex < numberOfCharacters; currentCharacterIndex++) {
		bool submitted = false;
		int selectedIndex = 0;

		while (!submitted) {
			std::cout << "\r";
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "[";

			for (size_t i = 0; i < numberOfCharacters; i++)
			{
				if (i < currentCharacterIndex) {
					SetConsoleTextAttribute(hConsole, 15);
					std::cout << input.at(i);
				}
				if (i == currentCharacterIndex) {
					SetConsoleTextAttribute(hConsole, 14);
					std::cout << characterSet.at(selectedIndex);
				}
				if (i > currentCharacterIndex) {
					SetConsoleTextAttribute(hConsole, 7);
					std::cout << "-";
				}
			}

			SetConsoleTextAttribute(hConsole, 12);
			std::cout << "]";
			SetConsoleTextAttribute(hConsole, 7);

			bool commandPressed = false;
			while (!commandPressed) {
				if ((GetAsyncKeyState(VK_UP) & 0x8000) && selectedIndex > 0) {
					selectedIndex--;
					commandPressed = true;

					while (GetAsyncKeyState(VK_UP) & 0x8000);
				}
				if ((GetAsyncKeyState(VK_DOWN) & 0x8000) && selectedIndex < (characterSet.length() - 1)) {
					selectedIndex++;
					commandPressed = true;

					while (GetAsyncKeyState(VK_DOWN) & 0x8000);
				}
				if ((GetAsyncKeyState(VK_DELETE) & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000) && currentCharacterIndex > 0) {
					commandPressed = true;

					input.erase(input.end() - 1);
					currentCharacterIndex--;
					selectedIndex = 0;

					while ((GetAsyncKeyState(VK_DELETE) & 0x8000) || (GetAsyncKeyState(VK_LEFT) & 0x8000));
				}
				if ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
					submitted = true;
					commandPressed = true;

					input += characterSet.at(selectedIndex);

					while ((GetAsyncKeyState(VK_RETURN) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000));
				}
			}
		}
	}

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "\r[";

	for (size_t i = 0; i < numberOfCharacters; i++)
	{
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << input.at(i);
	}

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "]\n";
	SetConsoleTextAttribute(hConsole, 7);

	return input;
}

std::vector<PointMatrixElement> DistributePoints(int availablePoints, std::string playerName, int playerNumber) {
	std::vector<PointMatrixElement> pointsMatrix {
		{"Defense:  ", 5},
		{"Strength: ", 5},
		{"Speed:    ", 5}
	};

	bool submitted = false;
	int selectedIndex = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	while (availablePoints > 0) {
		Clear();

		std::cout << "Distribute skillpoints for [P" << playerNumber << "] <" << playerName << ">\n";
		std::cout << "Remaining points: " << availablePoints << "\n\n";

		for (int i = 0; i < pointsMatrix.size(); i++) {
			std::cout << pointsMatrix[i].label;
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << ((selectedIndex == i && pointsMatrix[i].points != 5) ? "< " : "  ");
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << pointsMatrix[i].points;
			SetConsoleTextAttribute(hConsole, 12);
			std::cout << (selectedIndex == i ? " >" : "  ");
			SetConsoleTextAttribute(hConsole, 7);
			std::cout << "\n";
		}

		bool commandPressed = false;
		while (!commandPressed) {
			if ((GetAsyncKeyState(VK_UP) & 0x8000) && selectedIndex > 0) {
				selectedIndex--;
				commandPressed = true;

				while (GetAsyncKeyState(VK_UP) & 0x8000);
			}
			if (((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) && selectedIndex < (pointsMatrix.size() - 1)) {
				selectedIndex++;
				commandPressed = true;

				while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000));
			}
			if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && pointsMatrix[selectedIndex].points > 5) {
				pointsMatrix[selectedIndex].points--;
				availablePoints++;
				commandPressed = true;

				while (GetAsyncKeyState(VK_LEFT) & 0x8000);
			}
			if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
				pointsMatrix[selectedIndex].points++;
				availablePoints--;
				commandPressed = true;

				while (GetAsyncKeyState(VK_RIGHT) & 0x8000);
			}
		}
	}

	Clear();

	return pointsMatrix;
}