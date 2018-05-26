#include <iostream>
#include "AutoPlayerAlgorithm.h"
#include "MyPiecePosition.h"
#include "MyJokerChange.h"
#include "MyMove.h"

#define SIZE_OF_BIASED_JOKER_ARRAY 6
#define BIASED_JOKER_ARRAY {SCISSORS_CHAR, ROCK_CHAR, PAPER_CHAR, ROCK_CHAR, SCISSORS_CHAR, ROCK_CHAR}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<std::unique_ptr<FightInfo>> &fights) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int res = b.getPlayer(MyPoint(i, j));
            if (res == 0) {
                myBoard[i][j] = NoPlayer;
            } else if (res != player) {
                myBoard[i][j] = EnemyPlayer;
            }
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    lastOpponentPiece = myBoard[move.getFrom().getX()][move.getFrom().getY()] | Movable;
    if (myBoard[move.getTo().getX()][move.getTo().getY()] == AutoPlayerAlgorithm::BoardCases::NoPlayer) {
        myBoard[move.getTo().getX()][move.getTo().getY()] = lastOpponentPiece; // if there is no player in destination just move
    }
    // empty the from of the player
    myBoard[move.getFrom().getX()][move.getFrom().getY()] = AutoPlayerAlgorithm::BoardCases::NoPlayer;
    lastMyPiece = 0;
    //assumes no error in move
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    if (fightInfo.getWinner() == 0) {
        myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = 0;
    } else if (fightInfo.getWinner() != player) {
        char newPlayerChar = fightInfo.getPiece(
                player == FIRST_PLAYER_CONST ? SECOND_PLAYER_CONST : FIRST_PLAYER_CONST);
        if ((lastOpponentPiece && get_piece_from_char(newPlayerChar)) ||
            (!(lastOpponentPiece && BoardCases::Suspected))) {
            //might be regular piece
            if (lastOpponentPiece != 0) {
                // he attacked me
                myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] =
                        lastOpponentPiece | Suspected |
                        get_piece_from_char(
                                newPlayerChar);
            } else {
                // I attacked him
                myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] =
                        myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()]
                        | Suspected | get_piece_from_char(newPlayerChar);
            }
        } else {

            // for sure a joker, changed it's repr
            unsigned int value =
                    AutoPlayerAlgorithm::BoardCases::EnemyPlayer | AutoPlayerAlgorithm::BoardCases::Joker |
                    get_piece_from_char(newPlayerChar);
            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = value;
        }
    } else if (fightInfo.getWinner() == player) {
        if (lastMyPiece != 0) {
            //we won and we attacked.
            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = lastMyPiece;
        }

    }
    lastMyPiece = 0;
    lastOpponentPiece = 0;
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
    lastOpponentPiece = 0;
    std::unique_ptr<std::vector<MyPoint>> couldBeEnemyFlagPointsVector = get_by_filter(EnemyPlayer,
                                                                                       Movable);
    std::unique_ptr<std::vector<MyPoint>> myScissors = get_by_filter(Scissors | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myRocks = get_by_filter(Rock | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myPapers = get_by_filter(Paper | OurPlayer);

    if (couldBeEnemyFlagPointsVector->size() <= F + B) {
        MyPoint &mustBeFlag = (*couldBeEnemyFlagPointsVector)[0];
        if (!myPapers->empty()) {
            MyPoint &paperPoint = (*myPapers)[0];
            return make_move(mustBeFlag, paperPoint);
        } else if (!myRocks->empty()) {
            MyPoint &rockPoint = (*myRocks)[0];
            return make_move(mustBeFlag, rockPoint);
        } else if (!myScissors->empty()) {
            MyPoint &scissorsPoint = (*myScissors)[0];
            return make_move(mustBeFlag, scissorsPoint);
        } else { // joker can't be bomb in our implementation(of the auto)
            std::cout << "Error SDKD-DSDS-SADD-DYSD-213SHD9403: shouldn't reach here  " << std::endl;
            return nullptr;
        }
    } else {
        std::unique_ptr<std::vector<MyPoint>> enemyScissors = get_by_filter(Scissors | EnemyPlayer);
        std::unique_ptr<std::vector<MyPoint>> enemyRocks = get_by_filter(Rock | EnemyPlayer);
        std::unique_ptr<std::vector<MyPoint>> enemyPapers = get_by_filter(Paper | EnemyPlayer);
        if (!enemyScissors->empty() && !myRocks->empty()) {
            MyPoint &rockPoint = (*myRocks)[0];
            MyPoint &attackPoint = (*enemyScissors)[0];
            return make_move(rockPoint, attackPoint);
        } else if (!enemyPapers->empty() && !myScissors->empty()) {
            MyPoint &scissorPoint = (*myScissors)[0];
            MyPoint &attackPoint = (*enemyPapers)[0];
            return make_move(scissorPoint, attackPoint);
        } else if (!enemyRocks->empty() && !myPapers->empty()) {
            MyPoint &paperPoint = (*myPapers)[0];
            MyPoint &attackPoint = (*enemyRocks)[0];
            return make_move(paperPoint, attackPoint);
        } else {
            unique_ptr<Move> moveToMake;
            std::unique_ptr<std::vector<MyPoint>> emptySpaces = get_by_filter(NoPlayer);
            if (!myPapers->empty()) {
                moveToMake = make_move((*myPapers)[0], (*emptySpaces)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;
            } else if (!myRocks->empty()) {
                moveToMake = make_move((*myRocks)[0], (*emptySpaces)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;
            } else if (!myScissors->empty()) {
                moveToMake = make_move((*myScissors)[0], (*emptySpaces)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;
            } else {
                std::cout << "ERROR [3213TVJ]: shouldn't reach here" << std::endl;
                return nullptr;
            }
            return moveToMake;

        }
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::make_move(const MyPoint &attacker_position,
                                                const MyPoint &defender_position) {
    this->lastMyPiece = this->myBoard[attacker_position.getX()][attacker_position.getY()];
    this->myBoard[attacker_position.getX()][attacker_position.getY()] = NoPlayer;
    return std::make_unique<MyMove>(attacker_position, defender_position);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
    int random = random_number_in_range_inclusive(1, 10);
    std::unique_ptr<std::vector<MyPoint>> jokerPositions = get_by_filter(Joker & OurPlayer);
    //in 70% probability
    if (random <= 7) {
        if (jokerPositions->size() == J) {
            return select_joker_change(jokerPositions, random / 4);
        } else if (jokerPositions->size() == 1) {
            return select_joker_change(jokerPositions, 0);
        }
    }
    //otherwise no change
    return nullptr;
}

unique_ptr<JokerChange>
AutoPlayerAlgorithm::select_joker_change(const unique_ptr<std::vector<MyPoint>> &jokerPositions, int pos) {
    char c;
    MyPoint &jokerPoint = (*jokerPositions)[pos];
    c = this->select_new_joker_repr(jokerPoint);

    unique_ptr<JokerChange> change = std::make_unique<MyJokerChange>(jokerPoint, c);
    return std::move(change);
}

char AutoPlayerAlgorithm::select_new_joker_repr(const MyPoint &jokerPoint) {
    char c = PAPER_CHAR;// default
    if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Scissors) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Scissors;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Paper;
        c = PAPER_CHAR;
    } else if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Rock) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Rock;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Scissors;
        c = SCISSORS_CHAR;
    } else if (myBoard[jokerPoint.getX()][jokerPoint.getY()] && Paper) {
        myBoard[jokerPoint.getX()][jokerPoint.getY()] &= ~Paper;
        myBoard[jokerPoint.getX()][jokerPoint.getY()] |= Rock;
        c = ROCK_CHAR;
    } else {
        std::cout << "ERROR: 32321 - should not reach here" << std::endl;
    }
    return c;
}

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player) : player((unsigned int) player),
                                                       lastOpponentPiece(AutoPlayerAlgorithm::BoardCases::NoPlayer) {}

AutoPlayerAlgorithm::~AutoPlayerAlgorithm() = default;

unsigned int AutoPlayerAlgorithm::get_piece_from_char(char c) const {
    switch (c) {
        case BOMB_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Bomb;
        case FLAG_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Flag;
        case JOKER_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Joker;
        case SCISSORS_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Scissors;
        case PAPER_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Paper;
        case ROCK_CHAR:
            return AutoPlayerAlgorithm::BoardCases::Rock;
        default:
            std::cout << "Error [ESFR-GPDR-MLSQ-NRTS-KLMR.743480193.PC]: AutoPlayer get piece default reached."
                      << std::endl;
            return 0;//shouldn't get here
    }

}

unique_ptr<std::vector<MyPoint>> AutoPlayerAlgorithm::get_by_filter(int filter_in, int filter_out) const {
    std::unique_ptr<std::vector<MyPoint>> vector = std::make_unique<std::vector<MyPoint>>();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if ((myBoard[i][j] & filter_in) == filter_in) {
                if ((myBoard[i][j] & filter_out) == 0) {
                    vector->emplace_back(i, j);
                }
            }
        }
    }
    return vector;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    std::vector<MyPoint> availableSpots;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            availableSpots.emplace_back(i, j);
        }
    }
    shuffle_vector(availableSpots);
    availableSpots.erase(availableSpots.begin() + MAX_POSSIBLE_PIECE_COUNT);
    //bias for joker
    char wantedJokerChars[SIZE_OF_BIASED_JOKER_ARRAY] = BIASED_JOKER_ARRAY;
    for (int i = 0; i < J; i++) {
        char chr = wantedJokerChars[random_number_in_range_inclusive(0, SIZE_OF_BIASED_JOKER_ARRAY - 1)];
        MyPiecePosition myPiecePosition(JOKER_CHAR, chr, availableSpots[i]);
        unsigned int value = Joker | OurPlayer |
                             get_piece_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + J);

    select_non_joker_piece_to_add(vectorToFill, availableSpots, B, BOMB_CHAR, false);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, S, SCISSORS_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, R, ROCK_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, P, PAPER_CHAR, true);
    select_non_joker_piece_to_add(vectorToFill, availableSpots, F, FLAG_CHAR, false);

}

#pragma clang diagnostic pop

void AutoPlayerAlgorithm::select_non_joker_piece_to_add(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                                        std::vector<MyPoint> &availableSpots, int count, char chr,
                                                        bool movable) {
    for (int i = 0; i < count; i++) {
        MyPiecePosition myPiecePosition(chr, NON_JOKER_REPR_DEFAULT, availableSpots[i]);
        unsigned int value =
                AutoPlayerAlgorithm::BoardCases::OurPlayer | get_piece_from_char(chr) | (movable ? Movable : 0);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + count);
}

