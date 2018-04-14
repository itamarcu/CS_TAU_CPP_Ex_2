//
// Created by daniel meltzer on 13/04/2018.
//

#include <iostream>
#include "GamePiece.h"

GamePieceType GamePiece::type_from_char(char c) {
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
