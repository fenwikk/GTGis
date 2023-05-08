#pragma once

#include <string>

class Fighter
{
public:
	const int maxHp = 100;

	std::string GenHpBar(int length);
	void Attack();
	void Defend();
	void WorkUp();
	void Rest();

	std::string name() { return _name; }
	int defense() { return _defense; }
	int strength() { return _strength; }
	int speed() { return _speed; }
	int hp() { return _hp; }
	int damageDealt() { return _damageDealt; }
	int kills() { return _kills; }

	std::string NameInput(int numberOfCharacters);
	void DistributePoints(int availablePoints, std::string playerName);

	Fighter(int playerNumber);
	~Fighter();

private:
	std::string _name;
	int _defense;
	int _strength;
	int _speed;
	int _hp;
	int _damageDealt;
	int _kills;
};
