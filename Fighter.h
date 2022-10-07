#pragma once

#include <string>

class Fighter {
public:
	const double maxHp = 100;
	std::string name;
	double defense;
	double strength;
	double speed;
	double hp;

	std::string GenHpBar(int length);
	void Attack();
	void Defend();
	void Rest();

	void TakeDamage(Fighter* attacker);

	Fighter(int playerNumber);
	~Fighter();
private:
};

