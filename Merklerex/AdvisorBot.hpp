//
//  AdvisorBot.hpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 5/1/22.
//

#ifndef AdvisorBot_hpp
#define AdvisorBot_hpp

#include <stdio.h>

#pragma once

#include "CommandBook.hpp"
#include "OrderBook.hpp"
#include <iostream>
#include <vector>
#include <string>

class AdvisorBot
{
    public:
        AdvisorBot();
        void init();
        
    private:
        void printMenu();
        std::string getUserInput();
        void processUserInput(std::string input);
        void printHelp(std::vector<std::string> cmdWords);
    
        std::string upperCase(std::string str);
    
        void prod();
    
        void min(std::string product, std::string type);
        void max(std::string product, std::string type);
    
        void avg(std::string product, std::string type, int timesteps);
    
        void predict(std::string product, std::string type);
    
        void time();
        void step();
    
        void trend(std::string product, std::string type, int timesteps);
    
        std::string currentTime;

        OrderBook orderBook{"/Users/rajasuvedhavivekanandan/Desktop/Merklerex/Merklerex/20200601.csv"};
//        OrderBook orderBook{"/Users/rajasuvedhavivekanandan/Desktop/Merklerex/Merklerex/20200317.csv"};
};

#endif /* AdvisorBot_hpp */
