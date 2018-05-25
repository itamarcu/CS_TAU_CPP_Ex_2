#include "FilePlayerAlgorithm.h"
#include "MyMove.h"
#include "MyJokerChange.h"

void FilePlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    //TODO move/change code from BoardIO into here. Notice that it should change from grid to vector of positions
}

void FilePlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    //Empty on purpose
}

void FilePlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    //Empty on purpose
}

void FilePlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    //Empty on purpose
}

unique_ptr<Move> FilePlayerAlgorithm::getMove() {
    if (alreadyGotMovementPartOfMove) {
        alreadyGotJokerPartOfMove = false;
        movesList.pop_front();
    }
    if (movesList.empty())
        return nullptr; // no more moves

    alreadyGotMovementPartOfMove = true;

    std::shared_ptr<PlannedMove> plannedMove = movesList.front();
    unique_ptr<Move> move = unique_ptr<Move>(
            new MyMove(plannedMove->getOrigin(), plannedMove->getDestination()));
    return move;
}

unique_ptr<JokerChange> FilePlayerAlgorithm::getJokerChange() {
    if (alreadyGotJokerPartOfMove) {
        alreadyGotMovementPartOfMove = false;
        movesList.pop_front();
    }
    if (movesList.empty())
        return nullptr; // no more moves

    alreadyGotJokerPartOfMove = true;

    std::shared_ptr<PlannedMove> plannedMove = movesList.front();
    if (plannedMove->getHasJokerChanged()) {
        unique_ptr<JokerChange> jokerChange = unique_ptr<JokerChange>(
                new MyJokerChange(plannedMove->getJokerPosition(), plannedMove->getNewJokerType()));
        return jokerChange;
    } else
        return nullptr; // no joker change
}

FilePlayerAlgorithm::~FilePlayerAlgorithm() = default;

FilePlayerAlgorithm::FilePlayerAlgorithm(int player) : player(player) {
    //TODO construct moves list
    alreadyGotJokerPartOfMove = false;
    alreadyGotMovementPartOfMove = false;
}
