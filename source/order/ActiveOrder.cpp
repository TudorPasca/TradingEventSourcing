#include "../../include/order/ActiveOrder.h"

Order::ActiveOrder::ActiveOrder(int user_id, OrderType order_type, std::string symbol, double quantity)
    : user_id_(user_id), type_(order_type), symbol_(std::move(symbol)), quantity_(quantity) {}

int Order::ActiveOrder::getUserId() const {
    return user_id_;
}

Order::OrderType Order::ActiveOrder::getType() const {
    return type_;
}

std::string Order::ActiveOrder::getSymbol() const {
    return symbol_;
}

double Order::ActiveOrder::getQuantity() const {
    return quantity_;
}


