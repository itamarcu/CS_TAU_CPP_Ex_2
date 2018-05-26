#include <iostream>
#include "AutoPlayerAlgorithm.h"
#include "MyPiecePosition.h"
#include "MyFightInfo.h"
#include "MyJokerChange.h"

#define SIZE_OF_BAISED_JOKER_ARRAY 6
#define BAISED_JOKER_ARRAY {SCISSORS_CHAR, ROCK_CHAR, PAPER_CHAR, ROCK_CHAR, SCISSORS_CHAR, ROCK_CHAR}

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

    if (myBoard[move.getTo().getX()][move.getTo().getY()] == AutoPlayerAlgorithm::BoardCases::NoPlayer) {
        myBoard[move.getTo().getX()][move.getTo().getY()] = myBoard[move.getFrom().getX()][move.getFrom().getY()];
    }
    lastOpponentPiece = myBoard[move.getFrom().getX()][move.getFrom().getY()];
    myBoard[move.getFrom().getX()][move.getFrom().getY()] = AutoPlayerAlgorithm::BoardCases::NoPlayer;
    //assumes no error in move
}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    if (fightInfo.getWinner() != player) {
        char newPlayerChar = fightInfo.getPiece(
                player == FIRST_PLAYER_CONST ? SECOND_PLAYER_CONST : FIRST_PLAYER_CONST);
        if ((lastOpponentPiece && get_piece_from_char(newPlayerChar)) ||
            (!(lastOpponentPiece && BoardCases::Suspected))) {
            //might be regular piece

            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = lastOpponentPiece | Suspected |
                                                                                      get_piece_from_char(
                                                                                              newPlayerChar);
        } else {

            // for sure a joker, changed it's repr
            unsigned int value =
                    AutoPlayerAlgorithm::BoardCases::SecondPlayer | AutoPlayerAlgorithm::BoardCases::Joker |
                    get_piece_from_char(newPlayerChar);
            myBoard[fightInfo.getPosition().getX()][fightInfo.getPosition().getY()] = value;
        }
    }
}

std::shared_ptr<PlannedMove> AutoPlayerAlgorithm::getFromNextMove() {
    //TODO something
    return std::shared_ptr<PlannedMove>();
}

unique_ptr<Move> AutoPlayerAlgorithm::getMove() {
    //TODO something
    return unique_ptr<Move>();
}

unique_ptr<JokerChange> AutoPlayerAlgorithm::getJokerChange() {
    int random = random_number_in_range(1, 10);
    std::unique_ptr<std::vector<MyPoint>> jokerPositions = get_vector_joker_positions();
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
    }
    else{
        std::cout << "ERROR: 32321 - shoudln't reach here"<< std::endl;
    }
    return c;
}

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player) : player((unsigned int) player),
                                                       lastOpponentPiece(AutoPlayerAlgorithm::BoardCases::NoPlayer) {
}

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

unique_ptr<std::vector<MyPoint>> AutoPlayerAlgorithm::get_vector_joker_positions() {
    return nullptr;
}

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
    char wantedJokerChars[SIZE_OF_BAISED_JOKER_ARRAY] = BAISED_JOKER_ARRAY;
    for (int i = 0; i < J; i++) {
        char chr = wantedJokerChars[random_number_in_range(0, SIZE_OF_BAISED_JOKER_ARRAY - 1)];
        MyPiecePosition myPiecePosition(JOKER_CHAR, chr, availableSpots[i]);
        unsigned int value = AutoPlayerAlgorithm::BoardCases::Joker | AutoPlayerAlgorithm::BoardCases::OurPlayer |
                             get_piece_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + J);

    addNonJokerPiece(vectorToFill, availableSpots, B, BOMB_CHAR);
    addNonJokerPiece(vectorToFill, availableSpots, S, SCISSORS_CHAR);
    addNonJokerPiece(vectorToFill, availableSpots, R, ROCK_CHAR);
    addNonJokerPiece(vectorToFill, availableSpots, P, PAPER_CHAR);
    addNonJokerPiece(vectorToFill, availableSpots, F, FLAG_CHAR);

}

void AutoPlayerAlgorithm::addNonJokerPiece(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                           std::vector<MyPoint> &availableSpots, int count, char chr) {
    for (int i = 0; i < count; i++) {
        MyPiecePosition myPiecePosition(chr, NON_JOKER_REPR_DEFAULT, availableSpots[i]);
        unsigned int value = AutoPlayerAlgorithm::BoardCases::OurPlayer | get_piece_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.push_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin(), availableSpots.begin() + count);
}

