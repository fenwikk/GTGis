#pragma once

#include <string>

class Fighter {
public:
	std::string name;
	double defense;
	double strength;
	double speed;
	double hp;

	std::string GenHpBar(int length);
	void Attack(Fighter* playerToAttack);
	void Defend();
	void Rest();

	void TakeDamage(Fighter* attacker);

	Fighter(std::string name, double defense, double strength, double speed);
	~Fighter();
private:
	double maxHp;
};

