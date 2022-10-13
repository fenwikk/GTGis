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
	void TakeDamage(Fighter* attacker);

	std::string GetName();
	int GetDefense();
	int GetStrength();
	int GetSpeed();
	int GetHp();
	int GetDamageDealt();
	int GetKills();

	std::string NameInput(int numberOfCharacters);
	void DistributePoints(int availablePoints, std::string playerName, int playerNumber);

	Fighter(int playerNumber);
	~Fighter();
private:
	std::string name;
	int defense;
	int strength;
	int speed;
	int hp;
	int damageDealt;
	int kills;
};
