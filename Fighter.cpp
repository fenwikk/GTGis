#include <iostream>
#include <Windows.h>
#include "Library.h"

#include "Fighter.h"

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

void Fighter::Attack(Fighter* playerToAttack) {
	playerToAttack->TakeDamage(this);
}

void Fighter::TakeDamage(Fighter* attacker) {
	double damageDealt = attacker->strength / this->defense * 2;
	hp -= damageDealt;

	Clear();

	std::cout << attacker->name << " attacked " << this->name << "!\n";
	std::cout << this->name << " took " << damageDealt << " damage.\n";
}

Fighter::Fighter(int playerNumber) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	Clear();

	std::cout << "Input name for [P" << playerNumber << "]\n";

	std::string newName = NameInput(3);

	std::vector<PointMatrixElement> points = {};
	bool acceptedPoints = false;
	while (acceptedPoints == false) {
		points = DistributePoints(10, name, playerNumber);

		std::cout << "<" << name << ">" << "\n";
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
	hp = 20;
	maxHp = 20;
}

Fighter::~Fighter() {

}