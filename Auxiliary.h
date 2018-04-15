#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_AUXILIARY_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_AUXILIARY_H

#include <string>
#include <vector>
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
std::vector<std::string>* split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter);
#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_AUXILIARY_H
