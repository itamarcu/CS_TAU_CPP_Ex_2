//
// Created by daniel meltzer on 14/04/2018.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H

#include "Classes.h"
#include "GameLogic.h"


class Game {
    //MARK:public ivars
public:
    /**
    * board of game
    */
    std::vector<std::vector<GamePiece *>> board;
    //MARK:Constructors
public:
    /**
     * initialize game with default parameters
     */
    explicit Game() : board(M, std::vector<GamePiece *>(N, nullptr)), currentPlayer(true), gameResult(NONE) {}
//MARK:Functions
public:
    /**
     * make a move on the board of the game
     * @param plannedMove the move to make on the board
     * @return the function returns the move result, with one of the cases in the MoveResultEnum
     */
    MoveResult make_move(const PlannedMove& plannedMove);


    //MARK: Getters:

public:
    bool isCurrentPlayerfirstPlayer() const;
    GameResult getGameResult() const;

    //MARK: Setters:
public:
    /**
     * set a game result
     * @param gameResult game result to set
     */
    void setGameResult(GameResult gameResult);

    //MARK:private ivars
private:

    bool currentPlayer;
    GameResult gameResult;


};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H
