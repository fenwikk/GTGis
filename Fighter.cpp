#include <iostream>
#include <Windows.h>
#include "Library.h"

#include "Fighter.h"
#include "Game.h"

std::string Fighter::GenHpBar(int length) {
	std::string bar = "";

	int hpLeft = (hp / maxHp) * (length - 2);
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
	std::vector<std::string> names = {};
	for (size_t i = 0; i < 5; i++) {
		
		if (Game::players[i] == nullptr) {
			names.push_back("");
			disabledItems.push_back(true);
		}
		else {
			names.push_back(Game::players[i]->name);
			if (Game::players[i] == this)
				disabledItems.push_back(true);
			else
				disabledItems.push_back(false);
		}
	}
	int whoToAttack = Menu(names, disabledItems);
	Game::players[whoToAttack]->TakeDamage(this);
}

void Fighter::TakeDamage(Fighter* attacker) {
	double damageDealt = 20;
	hp -= damageDealt;

	Clear();

	std::cout << attacker->name << " attacked " << this->name << "!\n";
	std::cout << this->name << " took damage.\n";

	WaitForEnterPress();

	if (hp <= 0) {
		std::cout << "Player <" << name << "> perished.\n";
		for (size_t i = 0; i < 5; i++) {
			if (Game::players[i] == this) {
				Game::players[i] = nullptr;
			}
		}
		WaitForEnterPress();
		delete this;
	}
}

Fighter::Fighter(int playerNumber) : hp(20)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Clear();

	std::cout << "Input name for [P" << playerNumber << "]\n";

	std::string newName = NameInput(3);

	std::vector<PointMatrixElement> points = {};
	bool acceptedPoints = false;
	while (acceptedPoints == false) {
		points = DistributePoints(10, newName, playerNumber);

		std::cout << "<" << newName << ">" << "\n";
		std::cout << "Defense:  ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[0].points << "\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Strength: ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[1].points << "\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Speed:    ";
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << points[2].points << "\n\n";
		SetConsoleTextAttribute(hConsole, 7);

		std::cout << "Accept points distribution?\n";

		acceptedPoints = !Menu({ "Yes", "No" });
	}

	name = newName;
	defense = points[0].points;
	strength = points[1].points;
	speed = points[2].points;
}

Fighter::~Fighter() {
	
}