#include <iostream>
#include "GameLogic.h"

static FightResult simulate_fight(const GamePiece &attacker, const GamePiece &defender) {
    // TODO fight logic
    return attackerWon;
}

static void move_piece_from_to(Game &game, Cell from, Cell to) {
    int r1 = from.row, c1 = from.column, r2 = to.row, c2 = to.column;
    if (game.board[r1][c1] == nullptr) {
        //TODO player attempted to move piece from empty place
        return;
    }
    if (r1 == r2 && c1 == c2) {
        //TODO player attempted to move piece to same space
        return;
    }
    if (game.board[r2][c2] == nullptr) {
        game.board[r2][c2] = game.board[r1][c1];
        game.board[r1][c1] = nullptr;
        return;
    }

    actually_fight(game, game.board[r1][c1], game.board[r2][c2], Cell(r2, c2));
    game.board[r1][c1] = nullptr;
}

static void actually_fight(Game &game, GamePiece *attacker, GamePiece *defender, Cell position) {
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
            std::cout << "ERROR in actually_fight because of weird fight result" << std::endl;
            break;
    }
}
