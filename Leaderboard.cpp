#include "Leaderboard.h"

LeaderboardItem::LeaderboardItem(std::string newName, int newDamageDealt, int newKills) : 
	_name(newName), 
	_damageDealt(newDamageDealt),
	_kills(newKills) {}

std::string LeaderboardItem::name() {
	return _name;
}
int LeaderboardItem::damageDealt() {
	return _damageDealt;
}
int LeaderboardItem::kills() {
	return _kills;
}