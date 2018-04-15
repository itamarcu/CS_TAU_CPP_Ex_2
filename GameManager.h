//
// Created by daniel meltzer on 14/04/2018.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEMANAGER_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEMANAGER_H

#include <vector>
#include "GameManager.h"
#include "Classes.h"
#include "Game.h"
//singleton
class GameManager {
public:


    Game game;

    /**
     * get single instance of Game manager
     * @return single instance of GameManager
     */
    static GameManager& getInstance()
    {
        static GameManager instance;

        return instance;
    }
    /**
     * run moves of players at the same time
     * @param firstPlayerMoves moves of first player
     * @param secondPlayerMoves moves of the second player
     */
    void run_moves(std::vector<PlannedMove> &firstPlayerMoves,
                          std::vector<PlannedMove> &secondPlayerMoves);

};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_GAMEMANAGER_H
