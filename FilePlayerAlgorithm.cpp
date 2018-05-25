//
// Created by Daniel Meltzer on 23/05/2018.
//

#include "FilePlayerAlgorithm.h"
#include "MyMove.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {

}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {

}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move &move) {

}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {

}

unique_ptr<Move> FilePlayerAlgorithm::getMove() {
    unique_ptr<Move> move = unique_ptr<Move>(new MyMove(movesList.front()->getOrigin(),movesList.front()->getDestination()));
    movesList.pop_front();
    return move;
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange() {
    return nullptr;
}

FilePlayerAlgorithm::~FilePlayerAlgorithm() = default;

FilePlayerAlgorithm::FilePlayerAlgorithm(int player, std::list<std::shared_ptr<PlannedMove>>& movesList,
                                         MyBoard &initialBoard) : player(player){
    movesList  = std::move(movesList);

}
