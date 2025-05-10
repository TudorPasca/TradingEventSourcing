#pragma once

#include <memory>

#include "IAggregate.h"
#include "../order/IActiveOrder.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>

class OrderBookAggregate: IAggregate {
public:
    OrderBookAggregate();
    void placeOrder(const std::shared_ptr<Order::IActiveOrder>& order);
    std::shared_ptr<Order::IActiveOrder> getTopBuyOrder(const std::string& symbol) const;
    std::shared_ptr<Order::IActiveOrder> getTopSellOrder(const std::string& symbol) const;
private:
    std::unordered_set<std::shared_ptr<Order::IActiveOrder>> all_orders_;
    std::unordered_map<std::string, std::priority_queue<std::shared_ptr<Order::IActiveOrder>>> buy_orders_by_symbol_, sell_orders_by_symbol_;
};
