#include "Leaderboard.h"

LeaderboardItem::LeaderboardItem(std::string newName, int newDamageDealt, int newKills) : 
	name(newName), 
	damageDealt(newDamageDealt),
	kills(newKills) {}

std::string LeaderboardItem::GetName() {
	return name;
}
int LeaderboardItem::GetDamageDealt() {
	return damageDealt;
}
int LeaderboardItem::GetKills() {
	return kills;
}