#pragma once

#include "Fighter.h"
#include "Leaderboard.h"

class Game {
public:
	static bool started;
	static Fighter** players;
	static LeaderboardItem* leaderboard[];

	static int PlayersLeft();
	static void Stats();
};
