#include <iostream>
#include <Windows.h>
#include "Library.h"

#include "Fighter.h"
#include "Game.h"

std::string Fighter::GenHpBar(int length) {
	std::string bar = "";

	int hpLeft;

	if (hp < (maxHp / 2))
		hpLeft = ceil((hp / maxHp) * (length - 2));
	else
		hpLeft = floor((hp / maxHp) * (length - 2));

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

void Fighter::Defend() {
	Clear();

	std::cout << "<" << name << "> defended themselves\n";

	defense += 2;
	std::cout << "<" << name << ">s defense went up by " << 2 << " points\n";

	if (speed <= 0) {
		speed--;
		std::cout << "<" << name << ">s speed went down by " << 1 << " point\n";
	}
	else
		std::cout << "<" << name << ">s speed is already at minimum. Speed was not changed\n";

	WaitForEnterPress();
}

void Fighter::WorkUp() {
	Clear();

	std::cout << "<" << name << "> worked up!\n";

	strength += 2;
	std::cout << "<" << name << ">s strength went up by " << 2 << " points\n";

	if (speed <= 0) {
		speed--;
		std::cout << "<" << name << ">s speed went down by " << 1 << " point\n";
	}
	else
		std::cout << "<" << name << ">s speed is already at minimum. Speed was not changed\n";

	WaitForEnterPress();
}

void Fighter::Rest() {
	Clear();

	int originalHp = hp;

	std::cout << "<" << name << "> rested\n";

	hp += 20;
	if (hp > 100)
		hp = 100;
	std::cout << "<" << name << "> healed " << hp - originalHp << " HP\n";

	WaitForEnterPress();
}

void Fighter::TakeDamage(Fighter* attacker) {
	int damageDealt = floor(attacker->strength / this->defense * 20);
	hp -= damageDealt;

	Clear();

	std::cout << "<" << attacker->name << "> attacked " << this->name << "!\n";
	std::cout << "<" << name << "> took " << damageDealt << " damage.\n";

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

Fighter::Fighter(int playerNumber) : hp(maxHp)
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