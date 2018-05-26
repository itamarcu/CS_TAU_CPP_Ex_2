#ifndef CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H
#define CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H


#include "PlayerAlgorithm.h"
#include "PlannedMove.h"
#include "MyBoard.h"

/**
 * @authors: Daniel Meltzer and Itamar Curiel
 */
class AutoPlayerAlgorithm : public PlayerAlgorithm {
private:
    unsigned int player; // 1 or 2
    unsigned int lastOpponentPiece;

    std::shared_ptr<PlannedMove> getFromNextMove();

    bool alreadyGotJokerPartOfMove;
    bool alreadyGotMovementPartOfMove;

    /**
     * board cases, don't use directly! so you can use or operator and save as int
     */
    enum BoardCases {
        NoPlayer = 0,
        OurPlayer = 1,
        SecondPlayer = 2,

        /**
         * could be with suspected on, when you think that a piece is some of the follows(we've seen it win in a fight) but might be a joker
         */
        Rock = 4,
        Scissors = 8,
        Paper = 16,

        /**
         * if we've seen a piece change it's type it must be a joker, not suspected
         */
        Joker = 32,

        /**
         * will be used only on our pieces
         */
        Bomb = 64,

        Flag = 128,

        /**
         * to use when you don't know for sure it's a piece or joker
         */
        Suspected = 256
    };

    //2d board of ints Representing Knowledge on Board, see enum
    unsigned int myBoard[N][M];

    void addNonJokerPiece(std::vector<unique_ptr<PiecePosition>> &vectorToFill, std::vector<MyPoint> &availableSpots,
                          int count, char chr);

    unsigned int get_piece_from_char(char c) const;

public:

    explicit AutoPlayerAlgorithm(int player);

    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) override;

    /**
     * notify on initial board
     * @param b the board to notify on
     * @param fights fights that were held on board
     */
    void notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) override;

    /**
     * notify function on opponent move, assumes no error in move
     * @param move the move of the opponent
     */
    void notifyOnOpponentMove(const Move &move) override;

    /**
     * notify fight result
     * @param fightInfo fight info
     */
    void notifyFightResult(const FightInfo &fightInfo) override;

    /**
     * get next move
     * @return next move
     */
    unique_ptr<Move> getMove() override;

    /**
     * get joker change
     * @return joker change, nullptr if no change;
     */
    unique_ptr<JokerChange> getJokerChange() override;

    ~AutoPlayerAlgorithm() override;

};


#endif //CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H
