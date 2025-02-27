//
//  AdvisorBot.cpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 5/1/22.
//

#include "AdvisorBot.hpp"
#include "CommandBook.hpp"
#include "OrderBook.hpp"
#include "OrderBookEntry.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

// Calling the AdvisorBot constructor.
AdvisorBot::AdvisorBot()
{
    
}

// Function that initialises values and executes
// the Advisorbot constructor.
void AdvisorBot::init()
{
    std::string input;
    while(true)
    {
        printMenu();
        input = getUserInput();
        processUserInput(input);
    }
}

// Function to print out starting instruction.
void AdvisorBot::printMenu()
{
    std::cout << "Please enter a command, or 'help' for a list of commands."
    << std::endl;
}

// Function to print out guides for each command.
void AdvisorBot::printHelp(std::vector<std::string> cmdWords)
{
    if(cmdWords.size() == 1)
    {
        std::cout << "The available commands are help, help <cmd>, prod, min, max, avg, predict, time, step and trend."
        << std::endl;
    }
    else if(cmdWords[1] == "prod")
    {
        std::cout << "Prod - list available products" << std::endl;
    }
    else if(cmdWords[1] == "min")
    {
        std::cout << "Min - find minimum bid or ask for product in current time step."
        << std::endl;
        std::cout << "Example: min ETH/BTC ask " << std::endl;
    }
    else if(cmdWords[1] == "max")
    {
        std::cout << "Max - find maximum bid or ask for product in current time step."
        << std::endl;
        std::cout << "Example: max ETH/BTC ask " << std::endl;
    }
    else if(cmdWords[1] == "avg")
    {
        std::cout << "Avg - compute average ask or bid for the sent product over the sent number of time steps."
        << std::endl;
        std::cout << "Example: avg ETH/BTC ask 10" << std::endl;
    }
    else if(cmdWords[1] == "predict")
    {
        std::cout << "Predict - predict ask or bid price for the sent product in the next time."
        << std::endl;
        std::cout << "Example: predict ETH/BTC bid" << std::endl;
    }
    else if(cmdWords[1] == "time")
    {
        std::cout << "Time - state current time in dataset/which timeframe we are looking at."
        << std::endl;
    }
    else if(cmdWords[1] == "step")
    {
        std::cout << "Step - move to next time step." << std::endl;
    }
    else if(cmdWords[1] == "trend")
    {
        std::cout << "Trend - list all trends over the sent number of time steps." << std::endl;
        std::cout << "Example: trend ETH/BTC bid 30" << std::endl;
    }
    else
    {
        std::cout << "Invalid command. Please enter available inputs. " << std::endl;
    }
}

// Function to
std::string AdvisorBot::getUserInput()
{
    std::string userInput;
    std::string line;
    std::getline(std::cin, line);
    try
    {
        userInput = line;//std::stoi(line);
    }
    catch (const std::exception& e)
    {
        //
    }
    std::cout << "Your command: " << userInput << std::endl;
    return userInput;
}

// Function to respond to users' commands.
void AdvisorBot::processUserInput(std::string input)
{
    std::vector<std::string> cmdWords = CommandBook::tokenise(input, ' ');
    std::cout << cmdWords[0] <<  std::endl;
    
    if(cmdWords[0] == "help")
    {
        printHelp(cmdWords);
    }
    else if(cmdWords[0] == "prod")
    {
        prod();
    }
    else if(cmdWords[0] == "min")
    {
        std::string product = cmdWords[1];
        std::string type = cmdWords[2];
        min(product, type);
    }
    else if(cmdWords[0] == "max")
    {
        std::string product = cmdWords[1];
        std::string type = cmdWords[2];
        max(product, type);
    }
    else if(cmdWords[0] == "avg")
    {
        std::string product = cmdWords[1];
        std::string type = cmdWords[2];
        int timesteps = std::stoi(cmdWords[3]);
        avg(product, type, timesteps);
    }
    else if(cmdWords[0] == "predict")
    {
        std::string product = cmdWords[1];
        std::string type = cmdWords[2];
        predict(product, type);
    }
    else if(cmdWords[0] == "time")
    {
        time();
    }
    else if(cmdWords[0] == "step")
    {
        step();
    }
    else if(cmdWords[0] == "trend")
    {
        std::string product = cmdWords[1];
        std::string type = cmdWords[2];
        int timesteps = std::stoi(cmdWords[3]);
        trend(product, type, timesteps);
    }
    else
    {
        std::cout << "Invalid input. Please enter available inputs. " << std::endl;
    }

}

// Function to list all available product pair in the market.
void AdvisorBot::prod()
{
    for(std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
    }
};

// Function to convert lowercase to uppercase if user types product in lowercase.
std::string AdvisorBot::upperCase(std::string str)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] >= 97 && str[i] <= 122)
        {
            str[i] = str[i] - 32;
        }
    }
    return str;
}

// Function to execute min() function.
// Find the minimum ask or bid for specified product.
void AdvisorBot::min(std::string product, std::string type)
{
    std::vector<OrderBookEntry> entries;
    currentTime = orderBook.getEarliestTime();
    
    // for minimum ask
    if(type == "ask")
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
            }
        }
        if(entries.size() > 0)
        {
            double minPrice = OrderBook::getLowPrice(entries);
            std::cout << "The minimum ask for " << upperCase(product) <<
                        " is " << std::to_string(minPrice) << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no asks for " << upperCase(product) << std::endl;
        }
    }
    
    // for minimum bid
    else if(type == "bid")
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
            }
        }
        if(entries.size() > 0)
        {
            double minPrice = OrderBook::getLowPrice(entries);
            std::cout << "The minimum bid for " << upperCase(product) <<
                        " is " << std::to_string(minPrice) << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no bids for " << upperCase(product) << std::endl;
        }
    }
    else
    {
        std::cout << "Please specify type: ask or bid " << std::endl;
    }
};

// Function to execute max() function.
// Find the maximum ask or bid for specified product.
void AdvisorBot::max(std::string product, std::string type)
{
    std::vector<OrderBookEntry> entries;
    currentTime = orderBook.getEarliestTime();
    
    // for maximum ask
    if(type == "ask")
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
            }
        }
        if(entries.size() > 0)
        {
            double maxPrice = OrderBook::getHighPrice(entries);
            
            std::cout << "The maximum ask for " << upperCase(product) <<
                        " is " << std::to_string(maxPrice) << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no asks for " << upperCase(product) << std::endl;
        }
    }
    
    // for maximum bid
    else if(type == "bid")
    {
        for(std::string const& p : orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
            }
        }
        if(entries.size() > 0)
        {
            double maxPrice = OrderBook::getHighPrice(entries);
            
            std::cout << "The maximum bid for " << upperCase(product) <<
                        " is " << std::to_string(maxPrice) << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no bids for " << upperCase(product) << std::endl;
        }
    }
    else
    {
        std::cout << "Please specify type: ask or bid " << std::endl;
    }
    
};

// Function to compute average ask or bid for sent product
// over stated number of timesteps.
void AdvisorBot::avg(std::string product, std::string type, int timesteps)
{
    std::vector<OrderBookEntry> entries;
    currentTime = orderBook.getEarliestTime();
    
    double pricesSum = 0;
    double avgPrice = 0;

    // for average ask
    if(type=="ask")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::ask, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //iterate through entries, starting from the last timestep in the current time.
            for(int i = entries.size(); i >= (entries.size() - timesteps); i--)
            {
                pricesSum = entries[i].price + pricesSum;
            }
            avgPrice = pricesSum / timesteps;
            std::cout << "The average " << upperCase(product) << " ask price over the last " <<
                                    timesteps << " timesteps was " << avgPrice << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no bids for " << upperCase(product) << std::endl;
        }
    }
    
    // for average bid
    else if(type == "bid")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::bid, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //iterate through entries, starting from the last timestep in the current time.
            for(int i = entries.size(); i >= (entries.size() - timesteps); i--)
            {
                pricesSum = entries[i].price + pricesSum;
            }
            avgPrice = pricesSum / timesteps;
            std::cout << "The average " << upperCase(product) << " bid price over the last " <<
                                    timesteps << " timesteps was " << avgPrice << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no bids for " << upperCase(product) << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid input, please enter again. " << std::endl;
    }
};

// Function to execute predict() function.
// Predict ask/bid for sent product in the next time.
void AdvisorBot::predict(std::string product, std::string type)
{
    std::vector<OrderBookEntry> entries;
    currentTime = orderBook.getEarliestTime();
    
    double pricesSum1 = 0;
    double pricesSum2 = 0;
    double avgPrice1 = 0;
    double avgPrice2 = 0;
    double moveAvg = 0;

    std::vector<int> avgPrices;

    //for ask prediction
    if(type == "ask")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::ask, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //using moving average method
            //find the average price in the first half of entries.
            for(int i = 0; i < entries.size()/2; i++)
            {
                pricesSum1 = entries[i].price + pricesSum1;
                avgPrice1 = pricesSum1 / (entries.size() / 2);
            }
            
            //find the average price in the second half of entries.
            for(int i = entries.size()/2; i < entries.size(); i++)
            {
                pricesSum2 = entries[i].price + pricesSum2;
                avgPrice2 = pricesSum2 / (entries.size() / 2);
            }
            
            moveAvg = (avgPrice1 + avgPrice2) / 2;
            std::cout << "The ask price for " << upperCase(product) << " might be " << moveAvg << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There will be no asks for " << upperCase(product) << std::endl;
        }
    }

    //for bid prediction
    else if(type == "bid")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::bid, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //using moving average method
            //find the average price in the first half of entries.
            for(int i = 0; i < entries.size()/2; i++)
            {
                pricesSum1 = entries[i].price + pricesSum1;
                avgPrice1 = pricesSum1 / (entries.size() / 2);
            }
            
            //find the average price in the second half of entries.
            for(int i = entries.size()/2; i < entries.size(); i++)
            {
                pricesSum2 = entries[i].price + pricesSum2;
                avgPrice2 = pricesSum2 / (entries.size() / 2);
            }
            
            moveAvg = (avgPrice1 + avgPrice2) / 2;
            std::cout << "The bid price for " << upperCase(product) << " might be " << moveAvg << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There will be no bids for " << upperCase(product) << std::endl;
        }
    }
    else
    {
        std::cout << "Invalid input, please enter again. " << std::endl;
    }
};

// Function to execute time() function.
// Function to state current time.
void AdvisorBot::time()
{
    currentTime = orderBook.getEarliestTime();
    std::cout << "Current time is: " << currentTime << std::endl;
};

// Function to execute step() function.
// Function to move to next time.
void AdvisorBot::step()
{
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Now at: " << currentTime << std::endl;
};

// Function to execute trend() function.
// Function to display trend for sent product
void AdvisorBot::trend(std::string product, std::string type, int timesteps)
{
    std::vector<OrderBookEntry> entries;
    currentTime = orderBook.getEarliestTime();
    int uptrends = 0;
    int downtrends = 0;
    double pricesSum = 0;
    double avgPrice = 0;
    
    if(type == "ask")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::ask, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //find average price.
            for(int i = 0; i < entries.size(); i++)
            {
                pricesSum += entries[i].price;
            }
            avgPrice = pricesSum / entries.size();

            //iterate through entries, starting from the last timestep in the current time.
            for(int i = entries.size(); i > (entries.size() - timesteps); i--)
            {
                if(entries[i].price > avgPrice)
                {
                    uptrends++;
                }
                else if(entries[i].price < avgPrice)
                {
                    downtrends++;
                }
            }
            std::cout << "Number of uptrends: " << uptrends <<
                        " Number of downtrends: " << downtrends <<
                        " for ask prices over the last " << timesteps << " time steps. " << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no trends for " << upperCase(product) << std::endl;
        }
    }
    
    else if(type == "bid")
    {
        for(std::string const& p: orderBook.getKnownProducts())
        {
            if(upperCase(product) == upperCase(p))
            {
                entries = orderBook.getOrders(OrderBookType::bid, p , currentTime);
            }
        }
        if(entries.size() > 0)
        {
            //find the average price.
            for(int i = 0; i < entries.size(); i++)
            {
                pricesSum += entries[i].price;
            }
            avgPrice = pricesSum / entries.size();
            
            //iterate through entries, starting from the last timestep in the current time.
            for(int i = entries.size(); i > (entries.size() - timesteps); i--)
            {
                if(entries[i].price > avgPrice)
                {
                    uptrends++;
                }
                else if(entries[i].price < avgPrice)
                {
                    downtrends++;
                }
            }
            std::cout << "Number of uptrends: " << uptrends <<
                        " Number of downtrends: " << downtrends <<
                        " for bid prices over the last " << timesteps << " time steps. " << std::endl;
        }
        // if product was typed wrongly
        else
        {
            std::cout << "There are no trends for " << upperCase(product) << std::endl;
        }
    }
}
