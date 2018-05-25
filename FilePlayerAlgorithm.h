#ifndef CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
#define CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H


#include <list>
#include "PlayerAlgorithm.h"
#include "PlannedMove.h"
#include "MyBoard.h"


class FilePlayerAlgorithm: public PlayerAlgorithm {
private:
    bool alreadyGotJokerPartOfMove;
    bool alreadyGotMovementPartOfMove;
    int player; // 1 or 2
    std::shared_ptr<PlannedMove> getFromNextMove();

    std::list<std::shared_ptr<PlannedMove>> movesList;
    std::vector<unique_ptr<PiecePosition>> initialPositions;
public:
    FilePlayerAlgorithm(int player, std::list<std::shared_ptr<PlannedMove>>& movesList,
                        MyBoard &initialBoard);

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

    ~FilePlayerAlgorithm() override;
};


#endif //CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
