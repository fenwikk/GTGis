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

		for (size_t i = 0; i < numberOfPlayers; i++) {
			Clear();
		
			std::cout << "Input name for [P" << i + 1 << "]\n";

			std::string name = NameInput(3);

			std::vector<PointMatrixElement> points = {};
			bool acceptedPoints = false;
			while (acceptedPoints == false) {
				points = DistributePoints(10);

				std::cout << "<" << name << ">" << "\n";
				std::cout << "Defense:  ";
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << points[0].points << "\n";
				SetConsoleTextAttribute(hConsole, 7);

				std::cout << "Strength: ";
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << points[1].points << "\n";
				SetConsoleTextAttribute(hConsole, 7);

				std::cout << "Speed:    ";
				SetConsoleTextAttribute(hConsole, 14);
				std::cout << points[2].points << "\n\n";
				SetConsoleTextAttribute(hConsole, 7);

				std::cout << "Accept points distribution?\n";

				acceptedPoints = !Menu({ "Yes", "No" });
			}

			players[i] = new Fighter(name, points[0].points, points[1].points, points[2].points);
		}

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