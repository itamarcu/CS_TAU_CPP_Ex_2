//
// Created by itamar on 2018-04-12.
//

#include <iostream>
#include "Classes.h"


GamePieceType type_from_char(char c) {
    switch (c) {
        case ROCK_CHAR:
            return Rock;
        case PAPER_CHAR:
            return Paper;
        case SCISSORS_CHAR:
            return Scissors;
        case BOMB_CHAR:
            return Bomb;
        case JOKER_CHAR:
            return None;
        case FLAG_CHAR:
            return Flag;
        default:
            std::cout << "ERROR in GamePiece type_from_char oh no";
            return None;
    }
}

const Cell &PlannedMove::getOrigin() const {
    return origin;
}

const Cell &PlannedMove::getDestination() const {
    return destination;
}

bool PlannedMove::isHas_joker_changed() const {
    return has_joker_changed;
}

const Cell &PlannedMove::getJoker_position() const {
    return joker_position;
}

GamePieceType PlannedMove::getNew_joker_type() const {
    return new_joker_type;
}

void PlannedMove::setOrigin(const Cell &origin) {
    PlannedMove::origin = origin;
}

void PlannedMove::setDestination(const Cell &destination) {
    PlannedMove::destination = destination;
}

void PlannedMove::setHas_joker_changed(bool has_joker_changed) {
    PlannedMove::has_joker_changed = has_joker_changed;
}

void PlannedMove::setJoker_position(const Cell &joker_position) {
    PlannedMove::joker_position = joker_position;
}

void PlannedMove::setNew_joker_type(GamePieceType new_joker_type) {
    PlannedMove::new_joker_type = new_joker_type;
}

char GamePiece::to_char() {
    char ch;
    switch (type) {
        case Rock:
            ch = ROCK_CHAR;
            break;
        case Paper:
            ch = PAPER_CHAR;
            break;
        case Scissors:
            ch = SCISSORS_CHAR;
            break;
        case Bomb:
            ch = BOMB_CHAR;
            break;
        case None:
            ch = JOKER_CHAR;
            break; // Notice
        case Flag:
            ch = FLAG_CHAR;
            break;
        default:;
            std::cerr << "Unknown type in store_game... cmon guys" << std::endl;
            ch = '@';
            break;
    }
    if (!player) // player 2
        ch = std::tolower(ch, std::locale()); // to lowercase
    return ch;
}
