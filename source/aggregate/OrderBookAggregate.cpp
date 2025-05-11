#include "../../include/aggregate/OrderBookAggregate.h"

void OrderBookAggregate::placeOrder(const Order::SellOrder& order) {
    sell_orders_by_symbol_.at(order.getSymbol()).insert(order);
}

void OrderBookAggregate::placeOrder(const Order::BuyOrder &order) {
    buy_orders_by_symbol_.at(order.getSymbol()).insert(order);
}

void OrderBookAggregate::cancelOrder(const Order::SellOrder &order) {
    sell_orders_by_symbol_.at(order.getSymbol()).erase(order);
}

void OrderBookAggregate::cancelOrder(const Order::BuyOrder &order) {
    buy_orders_by_symbol_.at(order.getSymbol()).erase(order);
}

Order::BuyOrder OrderBookAggregate::getTopBuyOrder(const std::string &symbol) const {
    return *buy_orders_by_symbol_.at(symbol).begin();
}

Order::SellOrder OrderBookAggregate::getTopSellOrder(const std::string& symbol) const {
    return *sell_orders_by_symbol_.at(symbol).begin();
}
