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

#include "../event/IDomainEvent.h"

class OrderBookAggregate : IAggregate {
public:
    OrderBookAggregate();

    std::vector<std::shared_ptr<IDomainEvent>> placeOrder(const Order::BuyOrder &order);
    std::vector<std::shared_ptr<IDomainEvent>> placeOrder(const Order::SellOrder &order);
    std::vector<std::shared_ptr<IDomainEvent>> cancelOrder(const Order::BuyOrder &order);
    std::vector<std::shared_ptr<IDomainEvent>> cancelOrder(const Order::SellOrder &order);
    Order::BuyOrder getTopBuyOrder(const std::string &symbol) const;
    Order::SellOrder getTopSellOrder(const std::string &symbol) const;
    std::vector<std::unique_ptr<Order::IActiveOrder>> getAllOrders() const;
private:
    using buyOrderSet = std::set<Order::BuyOrder>;
    using sellOrderSet = std::set<Order::SellOrder>;
    std::unordered_map<std::string, buyOrderSet> buy_orders_by_symbol_;
    std::unordered_map<std::string, sellOrderSet> sell_orders_by_symbol_;
};
