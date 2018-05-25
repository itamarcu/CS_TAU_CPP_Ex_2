#ifndef CS_TAU_CPP_RPS_AUXILIARY_H
#define CS_TAU_CPP_RPS_AUXILIARY_H


#include <vector>
#include <string>

#define M 10  // Rows
#define N 10  // Columns
#define R 2  // Rocks
#define P 5  // Papers
#define S 1  // Scissors
#define B 2  // Bombs
#define J 2  // Jokers
#define F 1  // Flags
#define ROCK_CHAR 'R'
#define PAPER_CHAR 'P'
#define SCISSORS_CHAR 'S'
#define BOMB_CHAR 'B'
#define JOKER_CHAR 'J'
#define FLAG_CHAR 'F'
#define FIRST_PLAYER_CONST 1
#define SECOND_PLAYER_CONST 2

/**
 * print line
 * @param str string to print in a seaperate line
 */
void print_line(std::string str);


/**
 * split a sting with delimiter
 * @param stringToSplit string to split
 * @param delimiter delimiter to use
 * @return vector of strings splited form the original one
 */
std::vector<std::string> *split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter);

/**
 *
 * @param player true for player 1, false for player 2
 * @return 1 or 2
 */
int bool_to_player(bool player);

#endif //CS_TAU_CPP_RPS_AUXILIARY_H
