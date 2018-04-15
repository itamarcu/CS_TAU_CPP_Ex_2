#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H


#include "Auxiliary.h"
#include "Classes.h"
#include "GameLogic.h"
#include "Game.h"
/**
 * result of loading board
 */
enum LoadBoardResult{
    UnableToOpenPath,BadFormat,NoJokerPieceSpecified,NoPiece,ToManyOfSamePiece,CoordinatesOutOfBound,TwoPiecesOfPlayerInSameColumn,NoEnoughFlags,LoadingSuccses
};
class BoardIO {
public:

    /**
     * setup a game
     * @param game game to setup
     */
    static void setup_game(Game& game);

    /**
     * load moves from files
     * @param player player to load data for.true for player 1 , false for 2
     * @return  vector of PlannedMove
     */
    static std::vector<PlannedMove> load_moves(bool player);

    /**
     * store the game
     * @param game game to store
     */
    static void store_game(Game &game);

    /**
     * load file of player to board
     * @param game game to add file to
     * @param player true for player 1 , false for 2
     * @return one of LoadBoardResult cases according to the succes of the function
     */
    static LoadBoardResult _add_load_into_board(Game &game, bool player);




};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
