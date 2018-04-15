#include <iostream>
#include "Game.h"

GameWinner Game::getGameWinner() const {
    return gameWinner;
}

std::string Game::getGameEndReason() const {
    return gameEndReason;
}

void Game::endGame(const GameWinner gameWinner, const std::string gameEndReason) {
    Game::gameWinner = gameWinner;
    Game::gameEndReason = gameEndReason;
}

