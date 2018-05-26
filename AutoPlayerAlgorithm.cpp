#include <iostream>
#include "AutoPlayerAlgorithm.h"
#include "MyPiecePosition.h"
#include "MyJokerChange.h"
#include "MyMove.h"

#define SIZE_OF_BIASED_JOKER_ARRAY 6
#define BIASED_JOKER_ARRAY {SCISSORS_CHAR, ROCK_CHAR, PAPER_CHAR, ROCK_CHAR, SCISSORS_CHAR, ROCK_CHAR}

void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            int res = b.getPlayer(MyPoint(i, j));
            if (res == 0) {
                myBoard[i][j] = NoPlayer;
            } else if (res == FIRST_PLAYER_CONST) {
                //update if not our player
                if (player != FIRST_PLAYER_CONST) {
                    myBoard[i][j] = SecondPlayer;
                }
            } else if (res == SECOND_PLAYER_CONST) {
                if (player != SECOND_PLAYER_CONST) {
                    myBoard[i][j] = SecondPlayer;
                }
            }
        }
    }
}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
    lastOpponentPiece = myBoard[move.getFrom().getX()][move.getFrom().getY()] | Movable;
    if (myBoard[move.getTo().getX()][move.getTo().getY()] == AutoPlayerAlgorithm::BoardCases::NoPlayer) {
        myBoard[move.getTo().getX()][move.getTo().getY()] = lastOpponentPiece;
    }

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
                myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] =
                        lastOpponentPiece | Suspected |
                        get_piece_from_char(
                                newPlayerChar);
            } else {
                myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] =
                        myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()]
                        | Suspected | get_piece_from_char(newPlayerChar);
            }
        } else {

            // for sure a joker, changed it's repr
            unsigned int value =
                    AutoPlayerAlgorithm::BoardCases::SecondPlayer | AutoPlayerAlgorithm::BoardCases::Joker |
                    get_piece_from_char(newPlayerChar);
            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = value;
        }
    } else if (fightInfo.getWinner() == player) {
        if (lastMyPiece != 0) {
            //if last move is ours
            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = lastMyPiece;
        }
    }
    lastMyPiece = 0;
    lastOpponentPiece = 0;
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
    lastOpponentPiece = 0;
    std::unique_ptr<std::vector<MyPoint>> couldBeEnemyFlagPointsVector = get_vector_with_settings(SecondPlayer,
                                                                                                  Movable);
    std::unique_ptr<std::vector<MyPoint>> myScissors = get_vector_with_settings(Scissors | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myRocks = get_vector_with_settings(Rock | OurPlayer);
    std::unique_ptr<std::vector<MyPoint>> myPapers = get_vector_with_settings(Paper | OurPlayer);

    if (couldBeEnemyFlagPointsVector->size() <= F + B) {
        MyPoint &mustBeFlag = (*couldBeEnemyFlagPointsVector)[0];
        if (!myPapers->empty()) {
            MyPoint &paperPoint = (*myPapers)[0];
            lastMyPiece = myBoard[paperPoint.getX()][paperPoint.getY()];
            myBoard[paperPoint.getX()][paperPoint.getY()] = NoPlayer;
            return std::make_unique<MyMove>(paperPoint, mustBeFlag);// kill the flag
        } else if (!myRocks->empty()) {
            MyPoint &rockPoint = (*myRocks)[0];
            lastMyPiece = myBoard[rockPoint.getX()][rockPoint.getY()];
            myBoard[rockPoint.getX()][rockPoint.getY()] = NoPlayer;
            return std::make_unique<MyMove>(rockPoint, mustBeFlag);// kill the flag
        } else if (!myScissors->empty()) {
            MyPoint &scissorsPoint = (*myScissors)[0];
            lastMyPiece = myBoard[scissorsPoint.getX()][scissorsPoint.getY()];
            myBoard[scissorsPoint.getX()][scissorsPoint.getY()] = NoPlayer;
            return std::make_unique<MyMove>(scissorsPoint, mustBeFlag);//kill the flag
        } else { // joker can't be bomb in our implementation(of the auto)
            std::cout << "Error SDKD-DSDS-SADD-DYSD-213SHD9403: shouldn't reach here  " << std::endl;
            return nullptr;
        }
    } else {
        std::unique_ptr<std::vector<MyPoint>> enemyScissors = get_vector_with_settings(Scissors | SecondPlayer);
        std::unique_ptr<std::vector<MyPoint>> enemyRocks = get_vector_with_settings(Rock | SecondPlayer);
        std::unique_ptr<std::vector<MyPoint>> enemyPapers = get_vector_with_settings(Paper | SecondPlayer);
        if ((!enemyScissors->empty()) && (!myRocks->empty())) {
            MyPoint &rockPoint = (*myRocks)[0];
            MyPoint &attackPoint = (*enemyScissors)[0];
            return makeAttack(attackPoint, rockPoint);
        } else if ((!enemyPapers->empty()) && (!myScissors->empty())) {
            MyPoint &attackPoint = (*enemyPapers)[0];
            MyPoint &scissorPoint = (*myScissors)[0];
            return makeAttack(attackPoint, scissorPoint);
        } else if ((!enemyRocks->empty()) && (myPapers->empty())) {
            MyPoint &attackPoint = (*enemyPapers)[0];
            MyPoint &paperPoint = (*myPapers)[0];
            return makeAttack(attackPoint, paperPoint);
        } else {
            unique_ptr<Move> moveToMake;
            std::unique_ptr<std::vector<MyPoint>> emptySpaces = get_vector_with_settings(NoPlayer);
            if (!myPapers->empty()) {
                moveToMake = makeAttack((*emptySpaces)[0], (*myPapers)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;
            } else if (!myRocks->empty()) {
                moveToMake = makeAttack((*emptySpaces)[0], (*myRocks)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;

            } else if (!myScissors->empty()) {
                moveToMake = makeAttack((*emptySpaces)[0], (*myScissors)[0]);
                this->myBoard[moveToMake->getTo().getX()][moveToMake->getTo().getY()] = lastMyPiece;
            } else {
                std::cout << "ERROR [3213TVJ]: shouldn't reach here" << std::endl;
                return nullptr;
            }
            return moveToMake;

        }
    }
}

unique_ptr<Move> AutoPlayerAlgorithm::makeAttack(const MyPoint &attackPoint, const MyPoint &attackerPoint) {
    this->lastMyPiece = this->myBoard[attackerPoint.getX()][attackerPoint.getY()];
    this->myBoard[attackerPoint.getX()][attackerPoint.getY()] = NoPlayer;
    return std::make_unique<MyMove>(attackerPoint, attackPoint);
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
    int random = random_number_in_range_inclusive(1, 10);
    std::unique_ptr<std::vector<MyPoint>> jokerPositions = get_vector_with_settings(Joker & OurPlayer);
    //in 70% probability
    if (random <= 7) {
        if (jokerPositions->size() == J) {
            char c;
            MyPoint &jokerPoint = (*jokerPositions)[random / 4];
            c = getNewRepr(jokerPoint);

            std::unique_ptr<JokerChange> change = std::make_unique<MyJokerChange>(jokerPoint, c);
            return std::move(change);
        } else if (jokerPositions->size() == 1) {
            char c;
            MyPoint &jokerPoint = (*jokerPositions)[0];
            c = getNewRepr(jokerPoint);

            std::unique_ptr<JokerChange> change = std::make_unique<MyJokerChange>(jokerPoint, c);
            return std::move(change);
        }
        //unique_ptr<JokerChange> change = std::make_unique<MyJokerChange>();

    }
    //otherwise no change
    return nullptr;
}

char AutoPlayerAlgorithm::getNewRepr(const MyPoint &jokerPoint) {
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

unique_ptr<std::vector<MyPoint>> AutoPlayerAlgorithm::get_vector_with_settings(int settings, int non) const{
    std::unique_ptr<std::vector<MyPoint>> vector = std::make_unique<std::vector<MyPoint>>();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if ((myBoard[i][j] & settings) == settings) {
                if (((myBoard[i][j]) & (non)) == 0) {
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

    addNonJokerPiece(vectorToFill, availableSpots, B, BOMB_CHAR, false);
    addNonJokerPiece(vectorToFill, availableSpots, S, SCISSORS_CHAR, true);
    addNonJokerPiece(vectorToFill, availableSpots, R, ROCK_CHAR, true);
    addNonJokerPiece(vectorToFill, availableSpots, P, PAPER_CHAR, true);
    addNonJokerPiece(vectorToFill, availableSpots, F, FLAG_CHAR, false);

}

#pragma clang diagnostic pop

void AutoPlayerAlgorithm::addNonJokerPiece(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                           std::vector<MyPoint> &availableSpots, int count, char chr, bool movable) {
    for (int i = 0; i < count; i++) {
        MyPiecePosition myPiecePosition(chr, NON_JOKER_REPR_DEFAULT, availableSpots[i]);
        unsigned int value =
                AutoPlayerAlgorithm::BoardCases::OurPlayer | get_piece_from_char(chr) | movable ? 0 : Movable;
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + count);
}

