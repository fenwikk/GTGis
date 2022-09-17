#pragma once

#include <string>
#include <array>
#include "Fighter.h"

class Game
{
public:
	static std::string title;
	static std::string headerText;
	static Game* currentGame;

	static void Setup();
	static void Fight();
	static void DisplayStats();

	Game(std::array<Fighter*, 5> players);

	int numberOfPlayersLeft();
	std::array<Fighter*, 5> players;
	std::array<std::string, 5> playerNames;
private:
	static bool currentGameSet;
};
