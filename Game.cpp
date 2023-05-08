#include <iostream>
#include <format>

#include "Game.h"
#include "Library.h"

bool Game::started = false;
Fighter **Game::players = nullptr;
LeaderboardItem *Game::leaderboard[] = {nullptr, nullptr, nullptr, nullptr, nullptr};

/**
 * @returns Antalet spelare som är kvar
 */
int Game::PlayersLeft()
{
	/**
	 * Går igenom alla spelare i spelar-fältet och kollar om det finns.
	 * Finns spelaren så lägger man till ett till "playersLeft"
	 */
	int playersLeft = 0;
	for (size_t i = 0; i < 5; i++)
	{
		if (players[i] != nullptr)
			playersLeft += 1;
	}

	return playersLeft;
}

/**
 * Skriver ut statistiken på ett fint sätt
 */
void Game::Stats()
{
	std::string names[5] = {"", "", "", "", ""};
	std::string hp[5] = {"", "", "", "", ""};
	std::string defense[5] = {"", "", "", "", ""};
	std::string strength[5] = {"", "", "", "", ""};
	std::string speed[5] = {"", "", "", "", ""};
	for (size_t i = 0; i < 5; i++)
	{
		if (Game::players[i] != nullptr)
		{
			Fighter *player = Game::players[i];

			names[i] = "    <" + Game::players[i]->name() + ">";
			hp[i] = player->GenHpBar(13);
			defense[i] = "defense:   " + std::format("{:02}", player->defense());
			strength[i] = "strength:  " + std::format("{:02}", player->strength());
			speed[i] = "speed:     " + std::format("{:02}", player->speed());
		}
	}

	Row(names, 5);
	Row(hp, 5);
	std::cout << "\n";
	Row(defense, 5);
	Row(strength, 5);
	Row(speed, 5);
	std::cout << "\n";
}