#pragma once
#include <string>

#include "OrderType.h"

namespace Order {
    class ActiveOrder {
    public:
        ActiveOrder(int user_id, OrderType order_type, std::string symbol, double quantity);

        int getUserId() const;
        OrderType getType() const;
        std::string getSymbol() const;
        double getQuantity() const;

    private:
        int user_id_;
        OrderType type_;
        std::string symbol_;
        double quantity_;
    };
}
