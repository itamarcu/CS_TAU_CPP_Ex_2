#include "AutoPlayerAlgorithm.h"
#include "MyPiecePosition.h"

#define SIZE_OF_BAISED_JOKER_ARRAY 6
#define BAISED_JOKER_ARRAY {SCISSORS_CHAR,ROCK_CHAR,PAPER_CHAR,ROCK_CHAR,SCISSORS_CHAR, ROCK_CHAR}
void AutoPlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<unique_ptr<FightInfo>> &fights) {
    //TODO something

}

void AutoPlayerAlgorithm::notifyOnOpponentMove(const Move &move) {


}

void AutoPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
    //TODO something

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
    //TODO something
    return unique_ptr<JokerChange>();
}

AutoPlayerAlgorithm::AutoPlayerAlgorithm(int player):player(player) {
}

AutoPlayerAlgorithm::~AutoPlayerAlgorithm() = default;
int AutoPlayerAlgorithm::get_piece_from_char(char c) const{
    switch(c){
        case BOMB_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Bomb;
        case FLAG_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Flag;
        case JOKER_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Joker;
        case SCISSORS_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Scissors;
        case PAPER_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Paper;
        case ROCK_CHAR:
            return AutoPlayerAlgorithm::BoardCases ::Rock;
        default:
            return 0;//shouldn't get here
    }

}
void AutoPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
    std::vector<MyPoint> availableSpots;
    for (int i = 0; i <  N; ++i) {
        for (int j = 0; j < M; ++j) {
            availableSpots.emplace_back(MyPoint(i,j));
        }
    }
    availableSpots.erase(availableSpots.begin()+PLAYER_PICES_MAX_COUNT);
    //bias for joker
    char wantedJokerChars[SIZE_OF_BAISED_JOKER_ARRAY] = BAISED_JOKER_ARRAY;
    for(int i = 0 ;i<J;i++){
        char chr = wantedJokerChars[random_number_in_range(0,SIZE_OF_BAISED_JOKER_ARRAY-1)];
        MyPiecePosition myPiecePosition(JOKER_CHAR,chr,availableSpots[i]);
        int value = AutoPlayerAlgorithm::BoardCases ::Joker | AutoPlayerAlgorithm::BoardCases ::OurPlayer | get_piece_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.emplace_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin()+J);

    addNonJokerPiece(vectorToFill,availableSpots,B,BOMB_CHAR);
    addNonJokerPiece(vectorToFill,availableSpots,S,SCISSORS_CHAR);
    addNonJokerPiece(vectorToFill,availableSpots,R,ROCK_CHAR);
    addNonJokerPiece(vectorToFill,availableSpots,P,PAPER_CHAR);
    addNonJokerPiece(vectorToFill,availableSpots,F,FLAG_CHAR);

}

void AutoPlayerAlgorithm::addNonJokerPiece(std::vector<unique_ptr<PiecePosition>> &vectorToFill,
                                           std::vector<MyPoint> &availableSpots, int count, char chr) const {
    for(int i = 0; i < count; i++){
        MyPiecePosition myPiecePosition(chr,NON_JOKER_REPR_DEFAULT,availableSpots[i]);
        int value =  AutoPlayerAlgorithm::BoardCases ::OurPlayer | get_piece_from_char(chr);
        myBoard[availableSpots[i].getX()][availableSpots[i].getY()] = value;
        vectorToFill.emplace_back(std::make_unique<MyPiecePosition>(myPiecePosition));
    }
    availableSpots.erase(availableSpots.begin()+count);
}

