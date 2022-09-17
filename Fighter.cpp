#include "Fighter.h"
#include <Windows.h>
#include "Game.h"
#include <iostream>

int Fighter::maxHp = 20;

Fighter::Fighter(std::string name, double defense, double strength, double speed) {
	this->name = name;
	this->defense = defense;
	this->strength = strength;
	this->speed = speed;

	this->hp = maxHp;
}

Fighter::~Fighter() {

}

void Fighter::Attack(Fighter* enemyToAttack) {
	enemyToAttack->Damage(this->strength);
}

void Fighter::Damage(double attackersStrength) {
	double damageDealt = (attackersStrength) / (this->defense);

	this->hp -= damageDealt;
}

void Fighter::Defend() {
	if (this->defense > 1)
		this->defense += 0.1;
}

void Fighter::Rest() {
	if (hp < maxHp)
		hp++;
}