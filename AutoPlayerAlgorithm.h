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
    bool alreadyGotJokerPartOfMove;
    bool alreadyGotMovementPartOfMove;
    int player; // 1 or 2
    std::shared_ptr<PlannedMove> getFromNextMove();
    /**
     * board cases, don't use directly! so you can use or operator and save as int
     */
    enum BoardCases{
        NoPlayer = 0,
        OurPlayer = 1,
        SecondPlayer = 2,
        /**
         * would be used when you think that a piece is some of the follows(we've seen it in a fight) but might be a joker
         */
        SuspctedRock = 4,
        SuspectedScissors = 8,
        SuspectedPaper = 16,
        /**
         * if we've seen a piece change it's type it must be a joker
         */
        Joker = 32
    };
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
     * notify function on opponent move
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

private:

    //2d board of ints Representing Knowledge on Board, see enum
    int myBoard[N][M];
};


#endif //CS_TAU_CPP_EX_2_AUTOPLAYERALOGRITHM_H
