#pragma once

#include "Fighter.h"

class Game {
public:
	static bool started;
	static Fighter** players;

	static int PlayersLeft();
	static void Stats();
};
