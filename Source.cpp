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

		int actionChoice = Menu({ "Attack", "Defend", "Work up", "Rest" });

		switch (actionChoice) {
		case 0:
			players[playerTurn]->Attack();
			break;
		case 1:
			players[playerTurn]->Defend();
			break;
		case 2:
			players[playerTurn]->WorkUp();
			break;
		case 3:
			players[playerTurn]->Rest();
			break;
		default:
			throw new Error("Action does not exist!");
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

	std::cout << "<" << players[0]->name << "> won with " << players[0]->hp << " HP left";

	return 0;
}