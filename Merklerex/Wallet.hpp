//
//  Wallet.hpp
//  Merklerex
//
//  Created by Rajasuvedha Vivekanandan on 6/12/21.
//

#ifndef Wallet_hpp
#define Wallet_hpp

#include <stdio.h>

#include <string>
#include <map>
#include "OrderBookEntry.hpp"

class Wallet
{
    public:
        Wallet();
        /** insert currency to the wallet */
        void insertCurrency(std::string type, double amount);
        /** remove currency from the wallet */
        bool removeCurrency(std::string type, double amount);
        
        /** check if the wallet contains this much currency or more */
        bool containsCurrency(std::string type, double amount);
        /** checks if the wallet can cope with this ask or bid.*/
        bool canFulfillOrder(OrderBookEntry order);
        /** update the contents of the wallet
         * assumes the order was made by the owner of the wallet
        */
        void processSale(OrderBookEntry& sale);

        /** generate a string representation of the wallet */
        std::string toString();
        friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    private:
        std::map<std::string,double> currencies;
};

#endif /* Wallet_hpp */
