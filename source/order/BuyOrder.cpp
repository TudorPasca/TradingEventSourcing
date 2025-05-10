#include "../../include/order/BuyOrder.h"

Order::BuyOrder::BuyOrder(int user_id, std::string symbol, int quantity, double price)
    : IActiveOrder(user_id, std::move(symbol), quantity, price) {
}

Order::OrderType Order::BuyOrder::getType() const {
    return BUY;
}

bool Order::BuyOrder::operator<(const IActiveOrder &other) const {
    return price_ < other.getPrice();
}
