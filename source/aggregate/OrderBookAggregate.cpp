#include "../../include/aggregate/OrderBookAggregate.h"

OrderBookAggregate::OrderBookAggregate()
    : all_orders_(), buy_orders_by_symbol_(), sell_orders_by_symbol_() {}

std::shared_ptr<Order::IActiveOrder> OrderBookAggregate::getTopBuyOrder(const std::string &symbol) const {
    return buy_orders_by_symbol_.at(symbol).top();
}

std::shared_ptr<Order::IActiveOrder> OrderBookAggregate::getTopSellOrder(const std::string& symbol) const {
    return sell_orders_by_symbol_.at(symbol).top();
}
