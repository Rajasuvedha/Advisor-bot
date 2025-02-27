//
//  CommandBook.hpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 5/1/22.
//

#ifndef CommandBook_hpp
#define CommandBook_hpp

#include <stdio.h>

#pragma once

#include "AdvisorBot.hpp"
#include "OrderBookEntry.hpp"

class CommandBook
{
    public:
        static std::vector<std::string> tokenise(std::string input, char separator);
    
    private:
    
};

#endif /* CommandBook_hpp */
