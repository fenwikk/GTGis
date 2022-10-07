#pragma once

#include <string>

class Fighter {
public:
	const double maxHp = 100;
	std::string name;
	int defense;
	int strength;
	int speed;
	int hp;

	std::string GenHpBar(int length);
	void Attack();
	void Defend();
	void WorkUp();
	void Rest();

	void TakeDamage(Fighter* attacker);

	Fighter(int playerNumber);
	~Fighter();
private:
};

