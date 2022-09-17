#include "Game.h"
#include "Error.h"
#include <iostream>
#include "Library.h"
#include <format>


std::string Game::title = "Fighter 3000";
std::string Game::headerText;
bool Game::currentGameSet = false;
Game* Game::currentGame;

Game::Game(std::array<Fighter*, 5> players) {
	if (Game::currentGameSet)
		throw new Error("Can't have more than one instance of class 'Game'");
	
	currentGameSet = true;
	this->players = players;

	this->playerNames = { "", "", "", "", "" };
	for (size_t i = 0; i < 5; i++)
	{
		if (players[i] != nullptr)
			this->playerNames[i] = players[i]->name;
	}
}

void Game::Setup() {
	Game::headerText = "\n\nChoose Mode:";

	int numberOfPlayers = Menu({ "P2", "P3", "P4", "P5" }) + 2;

	std::array<Fighter*, 5> players = { nullptr, nullptr, nullptr, nullptr, nullptr };
	for (int i = 0; i < numberOfPlayers; i++) {
		Game::headerText = "Mode: P" + std::to_string(numberOfPlayers) + ".\n\nP" + std::to_string(i + 1) + " enter name:";
		Clear();

		std::string playerName = NameInput(3);

		Game::headerText = "Mode: P" + std::to_string(numberOfPlayers) + ".\nP" + std::to_string(i + 1) + ": [" + playerName + "]";

		std::vector<PointMatrixElement> points = DistributePoints();

		players[i] = new Fighter(playerName, points[0].points, points[1].points, points[2].points);

	}

	currentGame = new Game(players);
}

void Game::Fight() {
	Game::headerText = "Mode: P" + std::to_string(currentGame->numberOfPlayersLeft());

	while (currentGame->numberOfPlayersLeft() > 1) {

		for (size_t i = 0; i < 5; i++) {
			if (currentGame->players[i] != nullptr) {
				Clear();

				int actionChoice = Menu({ "Attack", "Defend", "Rest" }, 
					[&]() {
						DisplayStats();
						std::cout << std::format("\nP{}s [{}] turn. What will you do?\n\n", i + 1, currentGame->playerNames[i]);
					});

				if (actionChoice == 0) {
					std::vector<std::string> names(currentGame->playerNames.begin(), currentGame->playerNames.end());
					int enemyToAttack = Menu(names,
						[]() {
							DisplayStats();
						});

					currentGame->players[i]->Attack(currentGame->players[enemyToAttack]);
				}
				else if (actionChoice == 1) {
					currentGame->players[i]->Defend();
				}
				else if (actionChoice == 2) {
					currentGame->players[i]->Rest();
				}
			}

			for (size_t i = 0; i < 5; i++) {

				if (currentGame->players[i] != nullptr) {
					if (currentGame->players[i]->hp <= 0) {
						std::cout << std::format("P{} [{}] has fainted.", i + 1, currentGame->playerNames[i]);
						delete currentGame->players[i];
						currentGame->players[i] = nullptr;
					}
				}
			}
		}
	}
}

void Game::DisplayStats() {
	std::vector<std::string> names(currentGame->playerNames.begin(), currentGame->playerNames.end());
	std::vector<std::string> strengths{};
	std::vector<std::string> defenses{};
	std::vector<std::string> speeds{};
	std::vector<std::string> hps{};

	for (size_t i = 0; i < currentGame->players.size(); i++)
	{
		Fighter* player = currentGame->players[i];

		if (currentGame->players[i] != nullptr) {
			defenses.push_back(std::format("Defense:  {}", player->defense));
			strengths.push_back(std::format("Strength: {}",player->strength));
			speeds.push_back(std::format("Speed:    {}", player->speed));
			hps.push_back(std::format("HP:       {:.1f}", player->hp));
		}
		else {
			defenses.push_back("");
			strengths.push_back("");
			speeds.push_back("");
			hps.push_back("");
		}
	}

	Row(names);
	Row(defenses);
	Row(strengths);
	Row(speeds);
	Row(hps);
}

int Game::numberOfPlayersLeft() {
	int playersLeft = 0;

	for (size_t i = 0; i < 5; i++)
		if (players[i] != nullptr)
			playersLeft++;

	return playersLeft;
}