#include <iostream>
#include "Game.h"

GameWinner Game::getGameWinner() const {
    return gameWinner;
}

std::string Game::getGameEndReason() const {
    return gameEndReason;
}

void Game::endGame(const GameWinner gameWinner, const std::string gameEndReason) {
    Game::gameWinner = gameWinner;
    Game::gameEndReason = gameEndReason;
}

bool Game::checkWin() {
    int non_flag_counts[] = {0, 0};
    int flag_counts[] = {0, 0};

    for (int row = 0; row < M; row++) {
        for (int col = 0; col < N; col++) {
            auto piece = board[row][col];
            if (piece != nullptr)
                if (piece->type == Flag) {
                    flag_counts[1 - piece->player] += 1;
                } else {
                    non_flag_counts[1 - piece->player] += 1;
                }
        }
    }

    if (non_flag_counts[0] == 0 && non_flag_counts[1] == 0) {
        gameWinner = TIE;
        gameEndReason = "A tie (this was not in the google doc)"
                " - moving PIECEs of the both players are eaten";
        return true;
    }
    if (non_flag_counts[0] == 0) {
        gameWinner = PLAYER_2_VICTORY;
        gameEndReason = "All moving PIECEs of the opponent are eaten";
        return true;
    }
    if (non_flag_counts[1] == 0) {
        gameWinner = PLAYER_1_VICTORY;
        gameEndReason = "All moving PIECEs of the opponent are eaten";
        return true;
    }
    if (flag_counts[0] == 0 && flag_counts[1] == 0) {
        gameWinner = TIE;
        gameEndReason = "A tie - all flags are eaten by both players"
                " in the position files";
        return true;
    }
    if (flag_counts[0] == 0) {
        gameWinner = PLAYER_2_VICTORY;
        gameEndReason = "All flags of the opponent are captured";
        return true;
    }
    if (flag_counts[1] == 0) {
        gameWinner = PLAYER_1_VICTORY;
        gameEndReason = "All flags of the opponent are captured";
        return true;
    }

    return false;
}

