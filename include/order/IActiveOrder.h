#pragma once
#include <string>

#include "OrderType.h"

namespace Order {
    class IActiveOrder {
    public:
        IActiveOrder(int user_id, std::string symbol, int quantity, double price);

        int getUserId() const;
        std::string getSymbol() const;
        int getQuantity() const;
        double getPrice() const;

        virtual OrderType getType() const = 0;
        virtual bool operator<(const IActiveOrder &other) const = 0;
    protected:
        int user_id_;
        std::string symbol_;
        int quantity_;
        double price_;
    };
}
