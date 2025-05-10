#include "../../include/order/SellOrder.h"

Order::SellOrder::SellOrder(int user_id, std::string symbol, int quantity, double price)
    : IActiveOrder(user_id, std::move(symbol), quantity, price) {
}

Order::OrderType Order::SellOrder::getType() const {
    return SELL;
}

bool Order::SellOrder::operator<(const IActiveOrder &other) const {
    return price_ > other.getPrice();
}

