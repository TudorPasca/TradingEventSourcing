#include "../../include/aggregate/OrderBookAggregate.h"

OrderBookAggregate::OrderBookAggregate()
    : all_orders_(), buy_orders_by_symbol_(), sell_orders_by_symbol_() {}

void OrderBookAggregate::placeOrder(const std::shared_ptr<Order::IActiveOrder>& order) {
    if (order == nullptr) {
        return;
    }
    all_orders_.insert(order);
    if (order->getType() == Order::OrderType::BUY) {
        buy_orders_by_symbol_.at(order->getSymbol()).push(order);
    } else {
        sell_orders_by_symbol_.at(order->getSymbol()).push(order);
    }
}


std::shared_ptr<Order::IActiveOrder> OrderBookAggregate::getTopBuyOrder(const std::string &symbol) const {
    return buy_orders_by_symbol_.at(symbol).top();
}

std::shared_ptr<Order::IActiveOrder> OrderBookAggregate::getTopSellOrder(const std::string& symbol) const {
    return sell_orders_by_symbol_.at(symbol).top();
}
