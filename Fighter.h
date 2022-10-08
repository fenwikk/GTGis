#pragma once

#include <string>
#include <vector>

struct PointMatrixElement {
public:
	std::string label;
	int points;
};

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

	std::string NameInput(int numberOfCharacters);
	std::vector<PointMatrixElement> DistributePoints(int availablePoints, std::string playerName, int playerNumber);

	Fighter(int playerNumber);
	~Fighter();
private:
	std::string name;
	int defense;
	int strength;
	int speed;
	int hp;
};
