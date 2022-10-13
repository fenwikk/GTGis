#include <iostream>

#include "Game.h"
#include "Error.h"
#include "Library.h"
#include "Fighter.h"
#include <Windows.h>
#include <algorithm>

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool finishedSetup = false;

	Fighter* players[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	Game::players = players;
	while (finishedSetup == false) {
		Clear();
		std::cout << "How many will play?\n";

		std::string playerNumberItems[] = {"2P", "3P", "4P", "5P"};
		int numberOfPlayers = Menu(playerNumberItems, 4) + 2;

		for (int i = 0; i < numberOfPlayers; i++) 
			players[i] = new Fighter(i + 1);


		Clear();

		Game::Stats();

		std::cout << "\nStart game?\n";
		std::string finishedSetupMenuItems[] = {"Yes", "No"};
		finishedSetup = !Menu(finishedSetupMenuItems, 2);
	}

	Game::started = true;

	int playerTurn = 0;
	SortFightersBySpeed(players);
	while (Game::PlayersLeft() > 1) {
		Fighter* currentPlayer = players[playerTurn];

		Clear();

		if (currentPlayer == nullptr)
			throw new Error("Player does not exist!");

		Write("<" + currentPlayer->GetName() + ">s turn.\n");
		std::cout << "What will you do?\n";

		std::string actionChoiceItems[] = {"Attack", "Defend", "Work up", "Rest"};
		int actionChoice = Menu(actionChoiceItems, 4);

		switch (actionChoice) {
		case 0:
			currentPlayer->Attack();
			break;
		case 1:
			currentPlayer->Defend();
			break;
		case 2:
			currentPlayer->WorkUp();
			break;
		case 3:
			currentPlayer->Rest();
			break;
		default:
			throw new Error("Action does not exist!");
			break;
		}

		playerTurn++;
		while (playerTurn < 5 && players[playerTurn] == nullptr) {
			playerTurn++;
		}
		if (playerTurn >= 5)
			playerTurn = 0;

		if (playerTurn == 0)
			SortFightersBySpeed(players);
	}

	Clear();

	Fighter* lastPlayer = players[0];

	if (lastPlayer == nullptr)
		throw new Error("No one is left alive");

	Game::leaderboard[0] = new LeaderboardItem(lastPlayer->GetName(), lastPlayer->GetDamageDealt(), lastPlayer->GetKills());
	std::cout << "<" << lastPlayer->GetName() << "> won with " << lastPlayer->GetHp() << " HP left";
	WaitForEnterPress();

	Game::started = false;
	Clear();

	std::cout << "Leaderboard:\n";
	std::string leaderBoardHeader[] = {"Place", "Name", "Damage Dealt", "Kills"};
	Row(leaderBoardHeader, 4);
	for (size_t i = 0; i < 5; i++) {
		if (Game::leaderboard[i] != nullptr) {
			LeaderboardItem* currentPlayer = Game::leaderboard[i];

			std::string entry[] = {
				std::to_string(i + 1),
				"<" + currentPlayer->GetName() + ">",
				std::to_string(currentPlayer->GetDamageDealt()),
				std::to_string(currentPlayer->GetKills()),
			};

			Row(entry, 4);
		}
	}

	return 0;
}