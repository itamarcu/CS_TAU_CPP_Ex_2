//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "FilePlayerAlgorithm.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {

}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {

}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move &move) {

}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {

}

unique_ptr<Move> FilePlayerAlgorithm::getMove() {
    return nullptr;
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange() {
    return nullptr;
}

FilePlayerAlgorithm::~FilePlayerAlgorithm() {

}
