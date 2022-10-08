#include <iostream>
#include <format>
#include <vector>

#include "Game.h"
#include "Library.h"

bool Game::started = false;
Fighter** Game::players = nullptr;

int Game::PlayersLeft() {
	int playersLeft = 0;

	for (size_t i = 0; i < 5; i++) {
		if (players[i] != nullptr)
			playersLeft += 1;
	}
	return playersLeft;
}

void Game::Stats() {
	std::vector<std::string> names = {};
	std::vector<std::string> hp = {};
	std::vector<std::string> defense = {};
	std::vector<std::string> strength = {};
	std::vector<std::string> speed = {};
	for (size_t i = 0; i < 5; i++) {
		if (Game::players[i] != nullptr) {
			Fighter* player = Game::players[i];

			names.push_back("    <" + Game::players[i]->GetName() + ">");
			hp.push_back(player->GenHpBar(13));
			defense.push_back("defense:   " + std::format("{:02}", player->GetDefense()));
			strength.push_back("strength:  " + std::format("{:02}", player->GetStrength()));
			speed.push_back("speed:     " + std::format("{:02}", player->GetSpeed()));
		}
		else {
			names.push_back("");
			hp.push_back("");
			defense.push_back("");
			strength.push_back("");
			speed.push_back("");
		}
	}

	Row(names);
	Row(hp);
	std::cout << "\n";
	Row(defense);
	Row(strength);
	Row(speed);
	std::cout << "\n";
}