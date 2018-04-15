#include <iostream>
#include <sstream>
#include "GameManager.h"

void GameManager::run_moves(GameMoves &gameMoves) {
    // The `moves` variable is an array of Pointers, and not References,
    // because C++ forbids arrays of references
    std::vector<PlannedMove> *moves[] = {&gameMoves.p1_moves, &gameMoves.p2_moves};
    int line_num[] = {0, 0};
    bool curr_p_index = !game.currentPlayer;
    while (game.getGameWinner() == GAME_NOT_ENDED) {
        if (moves[0]->size() <= line_num[0] && moves[1]->size() <= line_num[1]) {
            game.endGame(TIE, "A tie - both Moves input files done without a winner");
            return;
        }
        if (line_num[curr_p_index] < moves[curr_p_index]->size()) {
            auto move_result = make_planned_move(
                    game, (*moves[curr_p_index])[line_num[curr_p_index]]
            );

//            for (int col = 0; col < N; col++) {
//                for (int row = 0; row < M; row++) {
//                    char ch = ' ';
//                    if (game.board[row][col] != nullptr) {
//                        ch = game.board[row][col]->to_char();
//                    }
//                    std::cout << ch;
//                }
//                std::cout << std::endl;
//            }
            switch (move_result) {
                case SuccessfulMove:
                    line_num[curr_p_index] += 1;
                    break;
                case TriedToMoveEmptySpace:
                case TriedToMoveEnemy:
                case TriedToMoveUnmovablePiece:
                case TriedToMoveOutOfBorders:
                case TriedToMoveIntoAlly:
                case TriedIllegalJokerChange:
                    std::stringstream s;
                    s << "Bad Moves input file";
                    s << " for player " << (curr_p_index ? 1 : 2);
                    s << " - line " << line_num[curr_p_index];
                    std::string reason = s.str();
                    game.endGame(curr_p_index ? PLAYER_1_VICTORY : PLAYER_2_VICTORY, reason);

//                    auto x = (*moves[curr_p_index])[line_num[curr_p_index]];
//                    std::cout << "debug: " << move_result << x.getOrigin().row << x.getDestination().row << std::endl;
                    return;
            }
        }
        // Check winner
        if (game.checkWin())
            return;
        curr_p_index = !curr_p_index;
        game.currentPlayer = !game.currentPlayer;
    }
}
