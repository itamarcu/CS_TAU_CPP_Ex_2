#ifndef CS_TAU_CPP_RPS_GAMEMANAGER_H
#define CS_TAU_CPP_RPS_GAMEMANAGER_H

#include <vector>
#include "GameManager.h"

#include "Game.h"
#include "BoardIO.h"
#include "PlayerAlgorithm.h"

class NewGameManager {
private:
    Game &game;
    PlayerAlgorithm *p1_algo;
    PlayerAlgorithm *p2_algo;
public:
    explicit NewGameManager(Game &g, PlayerAlgorithm *p1_algo, PlayerAlgorithm *p2_algo) : game(g), p1_algo(p1_algo),
                                                                                           p2_algo(p2_algo) {}

    /**
     * run moves of players, alternating, until game ends
     */
    void run_game();
};

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
