#include <iostream>
#include "GameLogic.h"

/**
 * simulate a fight between two pieces and return the result
 * @param attacker attacker of fight
 * @param defender piece attacked
 * @return FightResult case matching the simulation
 */
FightResult simulate_fight(const GamePiece &attacker,
                           const GamePiece &defender) {
    //Bombs kill everyone
    if (attacker.type == Bomb || defender.type == Bomb)
        return BOTH_PIECES_LOST;
    //Ties are a lose-lose scenario
    if (attacker.type == defender.type)
        return BOTH_PIECES_LOST;
    //Flags are useless in combat
    if (attacker.type == Flag)
        return DEFENDER_WON;
    if (defender.type == Flag)
        return ATTACKER_WON;
    // Rock > Scissors > Paper > Rock
    if (attacker.type == Rock && defender.type == Scissors)
        return ATTACKER_WON;
    if (attacker.type == Paper && defender.type == Rock)
        return ATTACKER_WON;
    if (attacker.type == Scissors && defender.type == Paper)
        return ATTACKER_WON;
    if (attacker.type == Rock && defender.type == Paper)
        return ATTACKER_WON;
    if (attacker.type == Paper && defender.type == Scissors)
        return ATTACKER_WON;
    if (attacker.type == Scissors && defender.type == Rock)
        return ATTACKER_WON;
    
    std::cout << "BUG in simulate_fight !!!";
    return FightResult::BOTH_PIECES_LOST;
}


MoveResult _make_move_part_of_planned_move(Game &game, PlannedMove &plannedMove) {
    MyPoint source(plannedMove.getOrigin());
    MyPoint destination(plannedMove.getDestination());
    int sourceRow = source.getX(), sourceColumn = source.getY(),
            destinationRow = destination.getX(), destinationColumn = destination.getY();
//    std::cout << "attempting to move " << sourceRow << sourceColumn << " to "
//              << destinationRow << destinationColumn << std::endl;
    if (game.board.grid[sourceRow][sourceColumn] == nullptr) {
        return TriedToMoveEmptySpace;
    }
    if (!game.board.grid[sourceRow][sourceColumn]->canMove()) {
        return TriedToMoveUnmovablePiece;
    }
    if (game.board.grid[sourceRow][sourceColumn]->player != game.currentPlayer) {
        return TriedToMoveEnemy;
    }
    if (sourceRow == destinationRow && sourceColumn == destinationColumn) {
        return TriedToMoveIntoAlly;
    }
    if (game.board.grid[destinationRow][destinationColumn] == nullptr) {
        game.board.grid[destinationRow][destinationColumn] =
                game.board.grid[sourceRow][sourceColumn];
    } else {
        actually_fight(
                game,
                game.board.grid[sourceRow][sourceColumn],
                game.board.grid[destinationRow][destinationColumn],
                MyPoint(destinationRow, destinationColumn));
    }

    game.board.grid[sourceRow][sourceColumn] = nullptr;

    return SuccessfulMove;
}


MoveResult make_planned_move(Game &game, PlannedMove &plannedMove) {
    MoveResult firstResult = _make_move_part_of_planned_move(game, plannedMove);
    if (firstResult != SuccessfulMove || !plannedMove.getHasJokerChanged())
        return firstResult;

    MyPoint jokerPosition(plannedMove.getJokerPosition());
    int jx = jokerPosition.getX();
    int jy = jokerPosition.getY();
    auto joker = game.board.grid[jx][jy];
    if (joker == nullptr || !joker->isJoker || joker->player != game.currentPlayer)
        return TriedIllegalJokerChange;
    switch (plannedMove.getNewJokerType()) {
        // Only R P S B are allowed
        case Rock:
        case Paper:
        case Scissors:
        case Bomb:
            return SuccessfulMove;
        case None:
        case Flag:
            return TriedIllegalJokerChange;
        default:
            std::cerr << "BUG 7984132547" << std::endl;
            break;
    }
    return SuccessfulMove;
}

MoveResult actually_fight(Game &game, std::shared_ptr<GamePiece> attacker,
                          std::shared_ptr<GamePiece> defender, Point &&position) {
    int r = position.getX();
    int c = position.getY();
    auto fightResult = simulate_fight(*attacker, *defender);
    switch (fightResult) {
        case ATTACKER_WON:

            game.board.grid[r][c] = attacker;
            return MoveResult::SuccessfulMove;
        case DEFENDER_WON:

            game.board.grid[r][c] = defender;
            return MoveResult::SuccessfulMove;
        case BOTH_PIECES_LOST:

            game.board.grid[r][c] = nullptr;
            return MoveResult::SuccessfulMove;
        default:
            print_line("ERROR in actually_fight because of weird fight result");
            return MoveResult::SuccessfulMove;
    }
}
