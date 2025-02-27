//
//  main.cpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 23/10/21.
//

#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.hpp"
#include "MerkleMain.hpp"
#include "CSVReader.hpp"
#include "Wallet.hpp"
#include "AdvisorBot.hpp"


int main()
{
    // Wallet wallet{};
    // MerkleMain app{};
    AdvisorBot app{};
    app.init();
}
