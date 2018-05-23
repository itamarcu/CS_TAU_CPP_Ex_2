//
// Created by Daniel Meltzer on 23/05/2018.
//

#ifndef CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
#define CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H


#include "PlayerAlgorithm.h"

class FilePlayerAlgorithm: public PlayerAlgorithm {
public:
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) override;

    void notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) override;

    void notifyOnOpponentMove(const Move &move) override;

    void notifyFightResult(const FightInfo &fightInfo) override;

    unique_ptr<Move> getMove() override;

    unique_ptr<JokerChange> getJokerChange() override;

    ~FilePlayerAlgorithm() override;

};


#endif //CS_TAU_CPP_EX_2_FILEPLAYERALGORITHM_H
