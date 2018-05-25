#include <iostream>
#include <sstream>
#include "GameManager.h"

void NewGameManager::run_game() {
    auto p1_positions = std::vector<std::unique_ptr<PiecePosition>>(17);
    p1_algo->getInitialPositions(1, p1_positions);

}

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

//            for (int y = 0; y < N; y++) {
//                for (int x = 0; x < M; x++) {
//                    char ch = ' ';
//                    if (game.board.grid[x][y] != nullptr) {
//                        ch = game.board.grid[x][y]->to_char();
//                    }
//                    std::cout << ch;
//                }
//                std::cout << std::endl;
//            }
//            std::cout.flush();
            std::stringstream s;
            std::string reason;
            switch (move_result) {
                case SuccessfulMove:
                    line_num[curr_p_index] += 1;
                    break;
                case TriedToMoveEmptySpace: // 1
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedToMoveEmptySpace\n";
                    goto case_error;
                case TriedToMoveUnmovablePiece: // 2
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedToMoveUnmovablePiece\n";
                    goto case_error;
                case TriedToMoveOutOfBorders: // 3
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedToMoveOutOfBorders\n";
                    goto case_error;
                case TriedToMoveIntoAlly: // 4
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedToMoveIntoAlly\n";
                    goto case_error;
                case TriedToMoveEnemy: // 5
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedToMoveEnemy\n";
                    goto case_error;
                case TriedIllegalJokerChange: // 6
                    std::cout << "Bad input for player " << (curr_p_index ? 2 : 1) << ": TriedIllegalJokerChange\n";
                    goto case_error;
                default:
                    std::cerr << "BUG 58689217038" << std::endl;
                    break;
                case_error:
                    s << "Bad Moves input file";
                    s << " for player " << (curr_p_index ? 2 : 1);
                    s << " - line " << (line_num[curr_p_index] + 1);
                    reason = s.str();
                    game.endGame(curr_p_index ? PLAYER_1_VICTORY : PLAYER_2_VICTORY, reason);
                    return;
            }
        }
        // Check winner
        if (game.checkWin()) {
            return;
        }
        curr_p_index = !curr_p_index;
        game.currentPlayer = !game.currentPlayer;
    }
}
