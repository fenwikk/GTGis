#pragma once
#include <string>

class LeaderboardItem {
public:
	LeaderboardItem(std::string newName, int newDamageDealt, int newKills);

	std::string GetName();
	int GetDamageDealt();
	int GetKills();
private:
	std::string name;
	int damageDealt;
	int kills;
};