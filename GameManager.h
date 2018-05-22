#ifndef CS_TAU_CPP_RPS_GAMEMANAGER_H
#define CS_TAU_CPP_RPS_GAMEMANAGER_H

#include <vector>
#include "GameManager.h"

#include "Game.h"
#include "BoardIO.h"


class GameManager {
private:
    Game &game;
public:
    explicit GameManager(Game &g) : game(g) {}

    /**
     * run moves of players, alternating, until game ends
     */
    void run_moves(GameMoves &moves);
};


#endif //CS_TAU_CPP_RPS_GAMEMANAGER_H
