#include "AutoPlayerAlgorithm.h"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    //TODO something

}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    //TODO something

}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    //TODO something

}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    //TODO something

}

std::shared_ptr<PlannedMove> AutoPlayerAlgorithm::getFromNextMove() {
    //TODO something
    return std::shared_ptr<PlannedMove>();
}


unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
    //TODO something
    return unique_ptr<Move>();
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
    //TODO something
    return unique_ptr<JokerChange>();
}

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player, MyBoard &initialBoard) {
    //TODO something
}

AutoPlayerAlgorithm::~AutoPlayerAlgorithm() {
    //TODO something
}
