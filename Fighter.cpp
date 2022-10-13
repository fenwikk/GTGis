#include <iostream>
#include <Windows.h>
#include "Library.h"

#include "Fighter.h"
#include "Game.h"

std::string Fighter::GenHpBar(int length) {
	std::string bar = "";

	int hpLeft;

	if (hp < (maxHp / 2))
		hpLeft = (int)ceil(((float)hp / (float)maxHp) * (length - 2));
	else
		hpLeft = (int)floor(((float)hp / (float)maxHp) * (length - 2));

	for (size_t i = 0; i < hpLeft; i++) {
		bar += "#";
	}
	for (size_t i = 0; i < length - 2 - hpLeft; i++) {
		bar += "-";
	}

	return "[" + bar + "]";
}

void Fighter::Attack() {
	Clear();

	std::cout << "Who do you want to attack?\n";

	std::vector<bool> disabledItems = {};
	std::string names[] = { "", "", "", "", "" };
	for (size_t i = 0; i < 5; i++) {
		
		if (Game::players[i] == nullptr) {
			names[i] = "";
			disabledItems.push_back(true);
		}
		else {
			names[i] = Game::players[i]->name;
			if (Game::players[i] == this)
				disabledItems.push_back(true);
			else
				disabledItems.push_back(false);
		}
	}
	int whoToAttack = Menu(names, 5, disabledItems);
	Game::players[whoToAttack]->TakeDamage(this);
}
void Fighter::Defend() {
	Clear();

	Write("<" + name + "> defended themselves\n");

	defense += 2;
	Write("Defense went up by 2 points\n");

	if (speed > 0) {
		speed--;
		Write("Dpeed went down by 1 point\n");
	}
	else {
		Write("Dpeed is already at minimum. Speed was not changed\n");
	}
	WaitForEnterPress();
}
void Fighter::WorkUp() {
	Clear();

	Write("<" + name + "> worked up!\n");

	strength += 2;
	Write("Strength went up by 2 points\n");

	if (speed > 0) {
		speed--;
		Write("Speed went down by 1 point\n");
	}
	else {
		Write("Speed is already at minimum. Speed was not changed\n");
	}

	WaitForEnterPress();
}
void Fighter::Rest() {
	Clear();

	int originalHp = hp;

	Write("<" + name + "> rested");

	hp += 20;
	if (hp > 100)
		hp = 100;
	Write("<" + name + "> healed " + std::to_string(hp - originalHp) + " HP");
	WaitForEnterPress();
}
void Fighter::TakeDamage(Fighter* attacker) {
	int damageDealt = (int)floor((float)attacker->strength / (float)this->defense * 20);

	if (damageDealt > hp)
		damageDealt = hp;

	attacker->damageDealt += damageDealt;
	hp -= damageDealt;

	Clear();

	Write("<" + attacker->name + "> attacked <" + name + ">!\n");

	Write("<" + name + "> took " + std::to_string(damageDealt) +" damage.");

	if (hp <= 0) {
		attacker->kills++;
		delete this;
	}

	WaitForEnterPress();
}

std::string Fighter::GetName() {
	return name;
}
int Fighter::GetDefense() {
	return defense;
}
int Fighter::GetStrength() {
	return strength;
}
int Fighter::GetSpeed() {
	return speed;
}
int Fighter::GetHp() {
	return hp;
}
int Fighter::GetDamageDealt() {
	return damageDealt;
}
int Fighter::GetKills() {
	return kills;
}

std::string Fighter::NameInput(int numberOfCharacters) {
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

			for (size_t i = 0; i < numberOfCharacters; i++) {
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

	for (size_t i = 0; i < numberOfCharacters; i++) {
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << input.at(i);
	}

	SetConsoleTextAttribute(hConsole, 12);
	std::cout << "]\n";
	SetConsoleTextAttribute(hConsole, 7);

	return input;
}
void Fighter::DistributePoints(int availablePoints, std::string playerName, int playerNumber) {
	std::string labels[]{
		"Defense:  ",
		"Strength: ",
		"Speed:    "
	};
	int points[] = { 5, 5, 5 };

	bool submitted;
	int selectedIndex;
	bool confirmedPoints = false;
	while (confirmedPoints == false) {
		submitted = false;
		selectedIndex = 0;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		while (availablePoints > 0) {
			Clear();

			std::cout << "Distribute skillpoints for <" << playerName << ">\n";
			std::cout << "Remaining points: " << availablePoints << "\n\n";

			for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++) {
				std::cout << labels[i];
				SetConsoleTextAttribute(hConsole, 12);
				std::cout << ((selectedIndex == i && points[i] != 5) ? "< " : "  ");
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << points[i];
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
				if (((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000)) && selectedIndex < (sizeof(points) / sizeof(points[0]) - 1)) {
					selectedIndex++;
					commandPressed = true;

					while ((GetAsyncKeyState(VK_DOWN) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000));
				}
				if ((GetAsyncKeyState(VK_LEFT) & 0x8000) && points[selectedIndex] > 5) {
					points[selectedIndex]--;
					availablePoints++;
					commandPressed = true;

					while (GetAsyncKeyState(VK_LEFT) & 0x8000);
				}
				if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
					points[selectedIndex]++;
					availablePoints--;
					commandPressed = true;

					while (GetAsyncKeyState(VK_RIGHT) & 0x8000);
				}
			}
		}

		Clear();

		std::cout << "<" << name << ">" << "\n";
		std::cout << "Defense:  ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[0] << "\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Strength: ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[1] << "\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Speed:    ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[2] << "\n\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Accept points distribution?\n";

		std::string confirmMenuItems[] = { "Yes", "No" };
		confirmedPoints = !Menu(confirmMenuItems, 2);
	}

	defense = points[0];
	strength = points[1];
	speed = points[2];
}

Fighter::Fighter(int playerNumber) : hp(maxHp), damageDealt(0), kills(0)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Clear();

	bool confirmedName = false;
	while (!confirmedName) {
		std::cout << "Input name for [P" << playerNumber << "]\n";
		std::cout << "[Up/Down] to change character\n";

		name = NameInput(3);

		Clear();

		bool isDuplicate = false;
		for (size_t i = 0; i < 5; i++) {
			Fighter* player = Game::players[i];
			if (Game::players[i] != nullptr) 
				if (Game::players[i]->name == name) {
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << "The name <" << name << "> has already been taken. Retry with another name.\n";
					SetConsoleTextAttribute(hConsole, 7);
					isDuplicate = true;
				}
		}

		if (!isDuplicate) {
			Clear();
			std::cout << "Accept name <" << name << ">\n";

			std::string confirmMenuItems[] = {"Yes", "No"};
			confirmedName = !Menu(confirmMenuItems, 2);

			if (!confirmedName)
				Clear();
		}

	}

	DistributePoints(10, name, playerNumber);
}
Fighter::~Fighter() {
	Write("\nPlayer <" + name + "> perished.");

	Game::leaderboard[Game::PlayersLeft() - 1] = new LeaderboardItem(name, damageDealt, kills);

	for (size_t i = 0; i < 5; i++) {
		if (Game::players[i] == this) {
			Game::players[i] = nullptr;
		}
	}
}