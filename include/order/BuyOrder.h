#pragma once
#include "IActiveOrder.h"

namespace Order {
    class BuyOrder: public IActiveOrder {
    public:
        BuyOrder(int user_id, std::string symbol, int quantity, double price);
        OrderType getType() const override;
        bool operator<(const BuyOrder& other) const;
    };
}
