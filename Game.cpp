#include <iostream>
#include <format>

#include "Game.h"
#include "Library.h"

bool Game::started = false;
Fighter** Game::players = nullptr;
LeaderboardItem* Game::leaderboard[] = { nullptr, nullptr, nullptr, nullptr, nullptr };

int Game::PlayersLeft() {
	int playersLeft = 0;

	for (size_t i = 0; i < 5; i++) {
		if (players[i] != nullptr)
			playersLeft += 1;
	}
	return playersLeft;
}

void Game::Stats() {
	std::string names[5] = { "", "", "", "", "" };
	std::string hp[5] = { "", "", "", "", "" };
	std::string defense[5] = { "", "", "", "", "" };
	std::string strength[5] = { "", "", "", "", "" };
	std::string speed[5] = { "", "", "", "", "" };
	for (size_t i = 0; i < 5; i++) {
		if (Game::players[i] != nullptr) {
			Fighter* player = Game::players[i];

			names[i] = "    <" + Game::players[i]->GetName() + ">";
			hp[i] = player->GenHpBar(13);
			defense[i] = "defense:   " + std::format("{:02}", player->GetDefense());
			strength[i] = "strength:  " + std::format("{:02}", player->GetStrength());
			speed[i] = "speed:     " + std::format("{:02}", player->GetSpeed());
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