#include <iostream>
#include <sstream>
#include "GameManager.h"

void GameManager::run_moves(GameMoves &gameMoves) {
    // The `moves` variable is an array of Pointers, and not References,
    // because C++ forbids arrays of references
    std::vector<PlannedMove> *moves[] = {&gameMoves.p1_moves, &gameMoves.p2_moves};
    int line_num[] = {0, 0};
    bool &curr_p = game.currentPlayer;
    while (game.getGameWinner() == GAME_NOT_ENDED) {
        if (moves[0]->size() <= line_num[0] && moves[1]->size() <= line_num[1]) {
            game.endGame(TIE, "A tie - both Moves input files done without a winner");
            return;
        }
        if (line_num[curr_p] < moves[curr_p]->size()) {
            auto move_result = make_planned_move(game, (*moves[curr_p])[line_num[curr_p]]
            );
            switch (move_result) {
                case SuccessfulMove:
                    line_num[curr_p] += 1;
                    break;
                case TriedToMoveEmptySpace:
                case TriedToMoveUnmovablePiece:
                case TriedToMoveOutOfBorders:
                case TriedToMoveIntoAlly:
                case TriedIllegalJokerChange:
                    std::stringstream s;
                    s << "Bad Moves input file";
                    s << "for player " << curr_p + 1; // hope this works
                    s << " - line " << line_num[curr_p];
                    std::string reason = s.str();
                    game.endGame(curr_p ? PLAYER_1_VICTORY : PLAYER_2_VICTORY, reason);
                    return;
            }
        }
        curr_p = !curr_p; // Will change game.currentPlayer too!
    }
}
