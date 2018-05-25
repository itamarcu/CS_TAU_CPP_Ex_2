#include <iostream>
#include <sstream>
#include "GameManager.h"
#include "MyFightInfo.h"

LoadBoardResult NewGameManager::setup_positions(int player, std::vector<std::unique_ptr<PiecePosition>> &positions) {
    auto player_bool = (bool) (player - 1);
    std::map<GamePiece::Type, int> remainingCounts;
    int remainingJokerCount;
    BoardIO::settingCounts(remainingCounts, remainingJokerCount);
    int line_num = 0; // Line starts at 1!
    for (auto &placement : positions) {
        line_num += 1;

        if (placement == nullptr) {
            return LoadBoardResult(line_num, BadFormat);
        }

        std::shared_ptr<GamePiece> new_piece;
        if (placement->getPiece() == JOKER_CHAR) {
            new_piece = std::make_shared<GamePiece>(player_bool, type_from_char(placement->getJokerRep()), true);
        } else {
            new_piece = std::make_shared<GamePiece>(player_bool, type_from_char(placement->getPiece()), false);
        }
        if (new_piece->type == GamePiece::Type::None ||
            new_piece->type == GamePiece::Type::Flag) // Only allowed: R P S B
            return LoadBoardResult(line_num, InvalidJokerPieceType);
        if (new_piece->isJoker) {
            remainingJokerCount--;
            if (remainingJokerCount < 0)
                return LoadBoardResult(line_num, TooManyOfSamePiece);
        } else
            remainingCounts[new_piece->type]--;
        if (remainingCounts[new_piece->type] < 0)
            return LoadBoardResult(line_num, TooManyOfSamePiece);

        new_piece->player = player_bool;

        MyPoint position(placement->getPosition());
        auto &old_piece = game.board.grid[position.getX()][position.getY()];
        if (old_piece == nullptr)
            old_piece = new_piece;
        else if (old_piece->player == new_piece->player) {
            return LoadBoardResult(line_num, TwoPiecesSamePlayerSamePosition);
        } else {
            //fight fight fight
            auto result = actually_fight(game, new_piece, old_piece, MyPoint(position.getX(), position.getY()));
            int winner = 0;
            if (result == FightResult::ATTACKER_WON)
                winner = player;
            else winner = 2 - player;
            setup_fights.push_back(std::make_unique<MyFightInfo>(
                    player_bool ?
                    MyFightInfo(winner, position,
                                GamePiece::chrFromType(old_piece->type),
                                GamePiece::chrFromType(new_piece->type)) :
                    MyFightInfo(winner, position,
                                GamePiece::chrFromType(new_piece->type),
                                GamePiece::chrFromType(old_piece->type))));
        }
    }

    if (remainingCounts[GamePiece::Type::Flag] != 0)
        return LoadBoardResult(line_num, NotAllFlagsWerePlaced);

    return LoadBoardResult(line_num, BoardLoadingSuccess);
}

bool NewGameManager::setup_both_boards() {
    auto p1_positions = std::vector<std::unique_ptr<PiecePosition>>(0);
    auto p2_positions = std::vector<std::unique_ptr<PiecePosition>>(0);
    p1_algorithm->getInitialPositions(1, p1_positions);
    p2_algorithm->getInitialPositions(2, p2_positions);
    auto load_of_1 = this->setup_positions(1, p1_positions);
    auto load_of_2 = this->setup_positions(2, p1_positions);
    if (load_of_1.type != BoardLoadingSuccess && load_of_2.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for both players - ";
        s << "player 1: line " << load_of_1.line_num;
        s << ", ";
        s << "player 2: line " << load_of_2.line_num;
        game.endGame(TIE, s.str());
        return false;
    } else if (load_of_1.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for player 1 - ";
        s << "line " << load_of_1.line_num;
        game.endGame(PLAYER_2_VICTORY, s.str());
        std::cout << "error 1 is " << load_of_1.type << std::endl;
        return false;
    } else if (load_of_2.type != BoardLoadingSuccess) {
        std::stringstream s;
        s << "Bad Positioning input file for player 2 - ";
        s << "line " << load_of_2.line_num;
        std::cout << "error 2 is " << load_of_2.type << std::endl;
        game.endGame(PLAYER_1_VICTORY, s.str());
        return false;
    }

    return true;
}

void NewGameManager::run_game() {
    bool completed_setup = this->setup_both_boards();
    if (!completed_setup)
        return;

    p1_algorithm->notifyOnInitialBoard(game.board, setup_fights);
    p2_algorithm->notifyOnInitialBoard(game.board, setup_fights);

    while (game.getGameWinner() == GAME_NOT_ENDED) {
        auto move = game.currentPlayer ? p1_algorithm->getMove() : p2_algorithm->getMove();
        auto jokerChange = game.currentPlayer ? p1_algorithm->getJokerChange() : p2_algorithm->getJokerChange();
        if (move == nullptr) {
            game.endGame(game.currentPlayer ? PLAYER_2_VICTORY : PLAYER_1_VICTORY,
                         "Enemy player ran out of moves first!");
            return;
        }

        PlannedMove plannedMove(false);
        if (jokerChange == nullptr) // no joker swap
        {
            MyPoint from(move->getFrom());
            MyPoint to(move->getTo());
            plannedMove = PlannedMove(from.getX(), from.getY(), to.getX(), to.getY());
        } else {
            MyPoint from(move->getFrom());
            MyPoint to(move->getTo());
            MyPoint jokPos(jokerChange->getJokerChangePosition());
            char jokRep(jokerChange->getJokerNewRep());
            plannedMove = PlannedMove(from.getX(), from.getY(), to.getX(), to.getY(), jokPos.getX(), jokPos.getY(),
                                      type_from_char(jokRep));
        }

        auto move_result = make_planned_move(game, plannedMove);

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
                break;
            case TriedToMoveEmptySpace: // 1
                goto case_error;
            case TriedToMoveUnmovablePiece: // 2
                goto case_error;
            case TriedToMoveOutOfBorders: // 3
                goto case_error;
            case TriedToMoveIntoAlly: // 4
                goto case_error;
            case TriedToMoveEnemy: // 5
                goto case_error;
            case TriedIllegalJokerChange: // 6
                goto case_error;
            default:
                std::cerr << "BUG 58689217038" << std::endl;
                break;
            case_error:
                s << "Bad Moves input file";
                s << " for player " << (game.currentPlayer ? 1 : 2);
                reason = s.str();
                game.endGame(game.currentPlayer ? PLAYER_2_VICTORY : PLAYER_1_VICTORY, reason);
                return;
        }
        // Check winner
        if (game.checkWin()) {
            return;
        }
        game.currentPlayer = !game.currentPlayer;
    }
}
