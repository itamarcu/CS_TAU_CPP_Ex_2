#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H

#include "Classes.h"

enum MoveResult { // Can't be in GameLogic due to circular dependency
    SuccessfulMove,
    TriedToMoveEmptySpace,
    TriedToMoveUnmovablePiece,
    TriedToMoveOutOfBorders,
    TriedToMoveIntoAlly,
    TriedIllegalJokerChange
};

class Game {
    // Fields
public:
    /**
    * board of game
    */
    std::vector<std::vector<GamePiece *>> board;
    /**
     * true = Player 1, false = Player 2
     */
    bool currentPlayer;
private:
    GameWinner gameWinner;
    std::string gameEndReason;
    //MARK: Constructors
public:
    /**
     * initialize game with default parameters
     */
    explicit Game() : board(M, std::vector<GamePiece *>(N, nullptr)),
                      currentPlayer(true), gameWinner(GAME_NOT_ENDED),
                      gameEndReason("Game did not end yet") {}
    //MARK: Functions
public:
    /**
     * set a game result
     * @param gameWinner game winner to set
     * @param gameEndReason reason for ending
     */
    void endGame(GameWinner gameWinner, std::string gameEndReason);

    //MARK: Getters:
public:
    GameWinner getGameWinner() const;

    std::string getGameEndReason() const;
};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BGAME_H
