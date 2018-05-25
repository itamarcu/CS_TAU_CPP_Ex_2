#ifndef CS_TAU_CPP_RPS_BOARDIO_H
#define CS_TAU_CPP_RPS_BOARDIO_H


#include "Auxiliary.h"

#include "GameLogic.h"
#include "Game.h"
#include "PlannedMove.h"
#include <map>

/**
 * result of loading board
 */
enum LoadBoardResultType {
    UnableToOpenPath,
    BadFormat,
    InvalidJokerPieceType,
    InvalidPieceType,
    TooManyOfSamePiece,
    CoordinatesOutOfBound,
    TwoPiecesSamePlayerSamePosition,
    NotAllFlagsWerePlaced,
    BoardLoadingSuccess
};

struct LoadBoardResult {
public:
    LoadBoardResultType type;
    int line_num;

    explicit LoadBoardResult(int line_number, LoadBoardResultType loadResultType) :
            type(loadResultType), line_num(line_number) {}
};

struct GameMoves {
public:
    std::vector<PlannedMove> p1_moves;
    std::vector<PlannedMove> p2_moves;

    explicit GameMoves() : p1_moves(), p2_moves() {}
};

/**
 * "static" class for handling file input and output regarding boards
 */
class BoardIO {
public:
    /**
     * setup a game
     * @param game game to setup
     */
    static void setup_game(Game &game);

    /**
     * load moves from files
     * @param moves moves to setup
     */
    static void load_moves(GameMoves &moves);

    /**
     * store the game
     * @param game game to store
     */
    static void store_game(Game &game);

    /**
     * load file of player to board
     * @param board board to load into
     * @param player true for player 1 , false for 2
     * @return one of LoadBoardResult cases according to the success of the function
     */
    static LoadBoardResult load_board(MyBoard &board, bool player);


    static void settingCounts(std::map<GamePieceType, int> &remainingCounts, int &remainingJokerCount);
};


#endif //CS_TAU_CPP_RPS_BOARDIO_H
