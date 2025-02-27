//
//  CommandBook.cpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 5/1/22.
//
#include "CommandBook.hpp"
#include "AdvisorBot.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// tokenise function
std::vector<std::string> CommandBook::tokenise(std::string input, char seperator)
{
    std::vector<std::string> cmdWords;

    signed int start, end;
    std::string command;

    start = input.find_first_not_of(seperator, 0);

    do {
        end = input.find_first_of(seperator, start);
        if (start == input.length() || start == end) break;
        if (end >= 0) command = input.substr(start, end - start);
        else command = input.substr(start, input.length() - start);
        cmdWords.push_back(command);
        start = end + 1;

    } while (end > 0);
    
    return cmdWords;
};
