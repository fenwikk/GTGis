#include <iostream>

#include "Game.h"

Game::Game() {}

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