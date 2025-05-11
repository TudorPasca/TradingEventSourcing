#include "../../include/order/BuyOrder.h"

Order::BuyOrder::BuyOrder(int user_id, std::string symbol, int quantity, double price)
    : IActiveOrder(user_id, std::move(symbol), quantity, price) {
}

Order::OrderType Order::BuyOrder::getType() const {
    return BUY;
}

bool Order::BuyOrder::operator<(const BuyOrder &other) const {
    if (this->getPrice() != other.getPrice()) {
        return this->getPrice() < other.getPrice();
    }
    if (this->getQuantity() != other.getQuantity()) {
        return this->getQuantity() < other.getQuantity();
    }
    if (this->getSymbol() != other.getSymbol()) {
        return this->getSymbol() < other.getSymbol();
    }
    return this->getUserId() < other.getUserId();
}
