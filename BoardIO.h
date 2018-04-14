//
// Created by itamar on 2018-04-12.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H


#include <vector>
#include "Game.h"

#define R 2  // Rocks
#define P 5  // Papers
#define S 1  // Scissors
#define B 2  // Bombs
#define J 2  // Jokers
#define F 1  // Flags

class BoardIO {
public:
    static Game *setup_game();


private:
    static std::vector<std::string> *split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter);

    /// returns true if the load was legal
    static bool _add_load_into_board(Game &game, bool player);
};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
