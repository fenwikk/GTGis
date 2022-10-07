#include <iostream>

#include "Game.h"
#include "Library.h"
#include "Fighter.h"
#include <Windows.h>
#include <algorithm>

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool finishedSetup = false;

	Fighter* players[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	while (finishedSetup == false) {
		Clear();
		std::cout << "How many will play?\n";
		int numberOfPlayers = Menu({ "2P", "3P", "4P", "5P" }) + 2;

		for (size_t i = 0; i < numberOfPlayers; i++) 
			players[i] = new Fighter(i + 1);

		Game::players = players;

		Clear();

		Stats();

		std::cout << "\nStart game?\n";
		finishedSetup = !Menu({"Yes", "No"});
	}

	Game::started = true;

	int playerTurn = 0;
	SortFightersBySpeed(players);
	while (Game::PlayersLeft() > 1) {
		int playersleft = Game::PlayersLeft();

		Clear();

		std::cout << "<" << players[playerTurn]->name << ">s turn.\n";
		std::cout << "What will you do?\n";

		int actionChoice = Menu({ "Attack", "Defend", "Rest" });

		switch (actionChoice) {
		case 0:
			players[playerTurn]->Attack();
		default:
			break;
		}

		SortFightersBySpeed(players);

		playerTurn++;
		while (playerTurn < 5 && players[playerTurn] == nullptr) {
			playerTurn++;
		}
		if (playerTurn >= 5)
			playerTurn = 0;
	}

	std::cout << "<" << players[0]->name << "> won with " << players[0]->hp / .2 << "% HP left";

	return 0;
}