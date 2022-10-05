#include <iostream>

#include "Game.h"
#include "Library.h"
#include "Fighter.h"
#include <Windows.h>

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	bool finishedSetup = false;

	Fighter* players[] = {nullptr, nullptr, nullptr, nullptr, nullptr};
	while (finishedSetup == false) {
		Clear();
		std::cout << "How many will play?\n";
		int numberOfPlayers = Menu({ "2P", "3P", "4P", "5P" }) + 2;

		for (size_t i = 0; i < numberOfPlayers; i++) 
			players[i] = new Fighter(i);

		Game::players = players;

		Clear();

		Stats();

		std::cout << "\nStart game?\n";
		finishedSetup = !Menu({ "Yes", "No, restart setup" });
	}

	Game::started = true;

	while (Game::PlayersLeft() > 0) {
		Clear();

		players[0]->Attack(players[1]);

		while (true);
	}

	return 0;
}