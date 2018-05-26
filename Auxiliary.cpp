#include "Auxiliary.h"
#include <iostream>
#include <algorithm>

void print_line(std::string str) {
    std::cout << str << std::endl;
}

std::unique_ptr<std::vector<std::string>> split_string_using_delimiter(std::string &stringToSplit, std::string &delimiter) {
    std::unique_ptr<std::vector<std::string>> splittedStrings = std::make_unique<std::vector<std::string>>();
    size_t pos = stringToSplit.find(delimiter);
    size_t initialPos = 0;

    while (pos != std::string::npos) {
        auto subst = stringToSplit.substr(initialPos, pos - initialPos);
        if (!subst.empty()) {
            splittedStrings->push_back(subst);
        }
        initialPos = pos + delimiter.length();
        pos = stringToSplit.find(delimiter, initialPos);
    }

    // Add the last one
    splittedStrings->push_back(
            stringToSplit.substr(initialPos, std::min(pos, stringToSplit.length()) - initialPos + 1));

    return splittedStrings;

}

int bool_to_player(bool player) {
    return (1 - player) + 1; // 0->2, 1->1
}


int random_number_in_range(int from, int to) {

    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(from, to);
    return distr(generator);
}




