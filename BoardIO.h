//
// Created by itamar on 2018-04-12.
//

#ifndef CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
#define CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H


#include "Board.h"
#include <vector>
class BoardIO {
    public:
        static Board *parse_file(std::string &path );

    private:
        static std::vector<std::string>* split_string_using_delimiter(std::string& stringToSplit,std::string& delimiter);
};


#endif //CS_TAU_C_PLUS_PLUS_FIRST_EXERCISE_BOARDIO_H
