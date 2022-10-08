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
		int numberOfPlayers = Menu({ "2P", "3P", "4P", "5P" }) + 2;

		for (int i = 0; i < numberOfPlayers; i++) 
			players[i] = new Fighter(i + 1);


		Clear();

		Game::Stats();

		std::cout << "\nStart game?\n";
		finishedSetup = !Menu({"Yes", "No"});
	}

	Game::started = true;

	int playerTurn = 0;
	SortFightersBySpeed(players);
	while (Game::PlayersLeft() > 1) {
		Fighter* currentPlayer = players[playerTurn];

		Clear();

		if (currentPlayer == nullptr)
			throw new Error("Player does not exist!");

		std::cout << "<" << currentPlayer->GetName() << ">s turn.\n";
		std::cout << "What will you do?\n";

		int actionChoice = Menu({ "Attack", "Defend", "Work up", "Rest" });

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

	Fighter* lastPlayer = players[0];

	if (lastPlayer == nullptr)
		throw new Error("No one is left alive");

	std::cout << "<" << lastPlayer->GetName() << "> won with " << lastPlayer->GetHp() << " HP left";

	return 0;
}