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


inline const auto buyOrderComparator = [](const std::shared_ptr<Order::IActiveOrder> &a,
                                          const std::shared_ptr<Order::IActiveOrder> &b) -> bool {
    if (a == nullptr || b == nullptr)
        return (a == nullptr) && (b != nullptr);
    return a->getPrice() > b->getPrice();
};

inline const auto sellOrderComparator = [](const std::shared_ptr<Order::IActiveOrder> &a,
                                           const std::shared_ptr<Order::IActiveOrder> &b) -> bool {
    if (a == nullptr || b == nullptr)
        return (a == nullptr) && (b != nullptr);
    return a->getPrice() < b->getPrice();
};

class OrderBookAggregate : IAggregate {
public:
    OrderBookAggregate();

    void placeOrder(const std::shared_ptr<Order::IActiveOrder> &order);

    void cancelOrder(const std::shared_ptr<Order::IActiveOrder> &order);

    std::shared_ptr<Order::IActiveOrder> getTopBuyOrder(const std::string &symbol) const;

    std::shared_ptr<Order::IActiveOrder> getTopSellOrder(const std::string &symbol) const;

private:
    using buyOrderSet = std::set<std::shared_ptr<Order::IActiveOrder>, decltype(buyOrderComparator)>;
    using sellOrderSet = std::set<std::shared_ptr<Order::IActiveOrder>, decltype(sellOrderComparator)>;
    std::unordered_set<std::shared_ptr<Order::IActiveOrder> > all_orders_;
    std::unordered_map<std::string, buyOrderSet> buy_orders_by_symbol_;
    std::unordered_map<std::string, sellOrderSet> sell_orders_by_symbol_;
};
