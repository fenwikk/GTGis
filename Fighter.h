#pragma once

#include <string>

class Fighter {
public:
	const int maxHp = 100;

	std::string GenHpBar(int length);
	void Attack();
	void Defend();
	void WorkUp();
	void Rest();

	std::string GetName();
	int GetDefense();
	int GetStrength();
	int GetSpeed();
	int GetHp();

	void TakeDamage(Fighter* attacker);

	Fighter(int playerNumber);
	~Fighter();
private:
	std::string name;
	int defense;
	int strength;
	int speed;
	int hp;
};

