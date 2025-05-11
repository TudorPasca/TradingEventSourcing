#pragma once
#include "IActiveOrder.h"

namespace Order {
    class SellOrder: public IActiveOrder {
    public:
        SellOrder(int user_id, std::string symbol, int quantity, double price);
        OrderType getType() const override;
        bool operator<(const SellOrder &other) const;
    };
}
