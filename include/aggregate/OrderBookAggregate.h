#pragma once

#include <memory>

#include "IAggregate.h"
#include "../order/IActiveOrder.h"
#include "../order/BuyOrder.h"
#include "../order/SellOrder.h"
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>

class OrderBookAggregate : IAggregate {
public:
    OrderBookAggregate();

    void placeOrder(const Order::BuyOrder &order);
    void placeOrder(const Order::SellOrder &order);
    void cancelOrder(const Order::BuyOrder &order);
    void cancelOrder(const Order::SellOrder &order);
    Order::BuyOrder getTopBuyOrder(const std::string &symbol) const;
    Order::SellOrder getTopSellOrder(const std::string &symbol) const;

private:
    using buyOrderSet = std::set<Order::BuyOrder>;
    using sellOrderSet = std::set<Order::SellOrder>;
    std::unordered_map<std::string, buyOrderSet> buy_orders_by_symbol_;
    std::unordered_map<std::string, sellOrderSet> sell_orders_by_symbol_;
};
