#pragma once
#include <string>

#include "OrderType.h"

namespace Order {
    class IActiveOrder {
    public:
        IActiveOrder(int user_id, std::string symbol, int quantity, double price);
        virtual ~IActiveOrder() = default;

        int getUserId() const;
        std::string getSymbol() const;
        int getQuantity() const;
        double getPrice() const;

        virtual OrderType getType() const = 0;
    protected:
        int user_id_;
        std::string symbol_;
        int quantity_;
        double price_;
    };
}
