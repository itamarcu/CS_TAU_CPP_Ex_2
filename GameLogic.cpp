#include <iostream>
#include "GameLogic.h"

/**
 * simulate a fight between two pieces and return the result
 * @param attacker attacker of fight
 * @param defender piece attacked
 * @return FightResult case matching the simulation
 */
FightResult simulate_fight(const GamePiece &attacker,
                           const GamePiece &defender){
    // TODO fight logic
    return attackerWon;
}

MoveResult move_piece_from_to(Game &game, Cell from, Cell to) {
    int sourceRow = from.row, sourceColumn = from.column, destinationRow = to.row, destinationColumn = to.column;
    if (game.board[sourceRow][sourceColumn] == nullptr) {
        //TODO player attempted to move piece from empty place
        return TriedToMoveEmptySpace;
    }
    if (sourceRow == destinationRow && sourceColumn == destinationColumn) {
        //TODO player attempted to move piece to same space
        return RegularMove;
    }
    if (game.board[destinationRow][destinationColumn] == nullptr) {
        game.board[destinationRow][destinationColumn] = game.board[sourceRow][sourceColumn];
        game.board[sourceRow][sourceColumn] = nullptr;
        return RegularMove;
    }
    game.board[sourceRow][sourceColumn] = nullptr;
    return  actually_fight(game, game.board[sourceRow][sourceColumn], game.board[destinationRow][destinationColumn], Cell(destinationRow, destinationColumn));

}

MoveResult actually_fight(Game &game, GamePiece *attacker, GamePiece *defender, Cell position) {
    int r = position.row;
    int c = position.column;
    auto fightResult = simulate_fight(*attacker, *defender);
    switch (fightResult) {
        case attackerWon:
            delete defender;
            game.board[r][c] = attacker;
            break;
        case defenderWon:
            delete attacker;
            game.board[r][c] = defender;
            break;
        case bothPiecesLost:
            delete attacker;
            delete defender;
            game.board[r][c] = nullptr;
            break;
        default:
            print_line("ERROR in actually_fight because of weird fight result");
            break;
    }
}
