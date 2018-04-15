//
// Created by daniel meltzer on 14/04/2018.
//

#include "Game.h"

MoveResult Game::make_move(const PlannedMove& plannedMove){
    return RegularMove;
}



bool Game::isCurrentPlayerfirstPlayer() const {
    return currentPlayer;
}

GameResult Game::getGameResult() const {
    return gameResult;
}

void Game::setGameResult(GameResult gameResult) {
    Game::gameResult = gameResult;
}
