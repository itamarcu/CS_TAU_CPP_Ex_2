//
// Created by itamar on 2018-04-12.
//

#include "BoardIO.h"

Board *BoardIO::parse_file(std::string& path) {
    return nullptr;
}

std::vector<std::string> *BoardIO::split_string_using_delimiter(std::string& stringToSplit, std::string& delimiter) {
        auto splitedStrings = new std::vector<std::string>;
        size_t pos = stringToSplit.find(delimiter);
        size_t initialPos = 0;
        stringToSplit.clear();


        while( pos != std::string::npos ) {
            (*splitedStrings).push_back( stringToSplit.substr( initialPos, pos - initialPos ) );
            initialPos = pos + delimiter.length();

            pos = stringToSplit.find( delimiter, initialPos );
        }

        // Add the last one
        (*splitedStrings).push_back(stringToSplit.substr( initialPos, std::min( pos, stringToSplit.size() ) - initialPos + 1 ) );

        return splitedStrings;

}
