#include "../../include/order/SellOrder.h"

Order::SellOrder::SellOrder(int user_id, std::string symbol, int quantity, double price)
    : IActiveOrder(user_id, std::move(symbol), quantity, price) {
}

Order::OrderType Order::SellOrder::getType() const {
    return SELL;
}

bool Order::SellOrder::operator<(const SellOrder &other) const {
    if (this->getPrice() != other.getPrice()) {
        return this->getPrice() > other.getPrice();
    }
    if (this->getQuantity() != other.getQuantity()) {
        return this->getQuantity() < other.getQuantity();
    }
    if (this->getSymbol() != other.getSymbol()) {
        return this->getSymbol() < other.getSymbol();
    }
    return this->getUserId() < other.getUserId();
}

