//
// Created by itamar on 2018-04-12.
//

#include <iostream>
#include "Classes.h"


void Game::make_move(GamePiece &movingPiece, Cell &destination) {

}

GamePieceType type_from_char(char c) {
    switch (c) {
        case 'R':
            return Rock;
        case 'P':
            return Paper;
        case 'S':
            return Scissors;
        case 'B':
            return Bomb;
        case 'J':
            return None;
        case 'F':
            return Flag;
        default:
            std::cout << "ERROR in GamePiece type_from_char oh no";
            return None;
    }
}
