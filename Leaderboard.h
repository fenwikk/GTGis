#pragma once
#include <string>

class LeaderboardItem
{
public:
	LeaderboardItem(std::string newName, int newDamageDealt, int newKills);

	std::string name();
	int damageDealt();
	int kills();

private:
	std::string _name;
	int _damageDealt;
	int _kills;
};