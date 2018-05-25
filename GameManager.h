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
    std::unique_ptr<PlayerAlgorithm> p1_algo;
    std::unique_ptr<PlayerAlgorithm> p2_algo;
public:
    explicit NewGameManager(Game &game, std::unique_ptr<PlayerAlgorithm> p1_algo,
                            std::unique_ptr<PlayerAlgorithm> p2_algo) :
            game(game), p1_algo(std::move(p1_algo)), p2_algo(std::move(p2_algo)) {}

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
