#include "../../include/order/IActiveOrder.h"

Order::IActiveOrder::IActiveOrder(int user_id, std::string symbol, int quantity, double price)
    : user_id_(user_id), symbol_(std::move(symbol)), quantity_(quantity), price_(price) {}

int Order::IActiveOrder::getUserId() const {
    return user_id_;
}

std::string Order::IActiveOrder::getSymbol() const {
    return symbol_;
}

int Order::IActiveOrder::getQuantity() const {
    return quantity_;
}

double Order::IActiveOrder::getPrice() const {
    return price_;
}


