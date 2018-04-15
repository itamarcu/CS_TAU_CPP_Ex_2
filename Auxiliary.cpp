//
// Created by itamar on 2018-04-12.
//
#include "Auxiliary.h"
#include <iostream>

void print_line(std::string str)
{
    std::cout << str << std::endl;
}
std::vector<std::string>* split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter) {
    auto splittedStrings = new std::vector<std::string>;
    size_t pos = stringToSplit.find(delimiter);
    size_t initialPos = 0;

    while (pos != std::string::npos) {
        splittedStrings->push_back(stringToSplit.substr(initialPos, pos - initialPos));
        initialPos = pos + delimiter.length();

        pos = stringToSplit.find(delimiter, initialPos);
    }

    // Add the last one
    splittedStrings->push_back(
            stringToSplit.substr(initialPos, std::min(pos, stringToSplit.length()) - initialPos + 1));

    return splittedStrings;

}

