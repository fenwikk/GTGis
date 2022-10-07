#include <iostream>
#include <Windows.h>
#include "Library.h"

#include "Fighter.h"
#include "Game.h"

std::string Fighter::GenHpBar(int length) {
	std::string bar = "";

	int hpLeft;

	if (hp < (maxHp / 2))
		hpLeft = (int)ceil((hp / maxHp) * (length - 2));
	else
		hpLeft = (int)floor((hp / maxHp) * (length - 2));

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
			names.push_back(Game::players[i]->GetName());
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

	Write("<" + GetName() + "> defended themselves");
	WaitForEnterPress();

	defense += 2;
	Write("<" + GetName() + ">s defense went up by 2 points");
	WaitForEnterPress();

	if (speed > 0) {
		speed--;
		Write("<" + GetName() + ">s speed went down by 1 point");
		WaitForEnterPress();
	}
	else {
		Write("<" + GetName() + ">s speed is already at minimum. Speed was not changed");
		WaitForEnterPress();
	}
}

void Fighter::WorkUp() {
	Clear();

	Write("<" + GetName() + "> worked up!");
	WaitForEnterPress();

	strength += 2;
	Write("<" + GetName() + ">s strength went up by 2 points");
	WaitForEnterPress();

	if (speed > 0) {
		speed--;
		Write("<" + GetName() + ">s speed went down by 1 point");
		WaitForEnterPress();
	}
	else {
		Write("<" + GetName() + ">s speed is already at minimum. Speed was not changed");
		WaitForEnterPress();
	}

}

void Fighter::Rest() {
	Clear();

	int originalHp = hp;

	Write("<" + GetName() + "> rested");
	WaitForEnterPress();

	hp += 20;
	if (hp > 100)
		hp = 100;
	Write("<" + GetName() + "> healed " + std::to_string(hp - originalHp) + " HP");
	WaitForEnterPress();
}

void Fighter::TakeDamage(Fighter* attacker) {
	int damageDealt = floor(attacker->strength / this->defense * 20);
	hp -= damageDealt;

	Clear();

	Write("<" + attacker->GetName() + "> attacked <" + GetName() + ">!");
	WaitForEnterPress();

	Write("<" + GetName() + "> took " + std::to_string(damageDealt) +" damage.");
	WaitForEnterPress();

	if (hp <= 0) {
		Write("Player <" + GetName() + "> perished.\n");
		for (size_t i = 0; i < 5; i++) {
			if (Game::players[i] == this) {
				Game::players[i] = nullptr;
			}
		}
		WaitForEnterPress();
		delete this;
	}
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

Fighter::Fighter(int playerNumber) : hp(maxHp)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Clear();

	bool confirmedName = false;
	while (!confirmedName) {
		std::cout << "Input name for [P" << playerNumber << "]\n";

		GetName() = NameInput(3);

		Clear();

		bool isDuplicate = false;
		for (size_t i = 0; i < 5; i++) {
			Fighter* player = Game::players[i];
			if (Game::players[i] != nullptr) 
				if (Game::players[i]->GetName() == GetName()) {
					SetConsoleTextAttribute(hConsole, 12);
					std::cout << "The GetName() <" << GetName() << "> has already been taken. Retry with another GetName().\n";
					SetConsoleTextAttribute(hConsole, 7);
					isDuplicate = true;
				}
		}

		if (!isDuplicate) {
			Clear();
			std::cout << "Accept GetName() <" << GetName() << ">\n";

			confirmedName = !Menu({ "Yes", "No" });

			if (!confirmedName)
				Clear();
		}

	}

	std::vector<PointMatrixElement> points = {};
	bool confirmedPoints = false;
	while (confirmedPoints == false) {
		points = DistributePoints(10, GetName(), playerNumber);

		std::cout << "<" << GetName() << ">" << "\n";
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

		confirmedPoints = !Menu({ "Yes", "No" });
	}

	defense = points[0].points;
	strength = points[1].points;
	speed = points[2].points;
}

Fighter::~Fighter() {
	
}