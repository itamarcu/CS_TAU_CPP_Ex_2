//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "MyPlayerAlgorithm.h"

void MyPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {

}

void MyPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {

}

void MyPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {

}

void MyPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {

}

unique_ptr<Move> MyPlayerAlgorithm::getMove() {
    return nullptr;
}

unique_ptr<JokerChange> MyPlayerAlgorithm::getJokerChange() {
    return nullptr;
}

MyPlayerAlgorithm::~MyPlayerAlgorithm() = default;
