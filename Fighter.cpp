#include <iostream>
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

Fighter::Fighter(std::string newName, double newDefense, double newStrength, double newSpeed) {
	name = newName;
	defense = newDefense;
	strength = newStrength;
	speed = newSpeed;
	hp = 20;
	maxHp = 20;
}

Fighter::~Fighter() {

}