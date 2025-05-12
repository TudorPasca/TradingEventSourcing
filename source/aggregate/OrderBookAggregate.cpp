#include "../../include/aggregate/OrderBookAggregate.h"

#include "../../include/event/OrderCancelled.h"
#include "../../include/event/OrderPlaced.h"
#include "../../include/event/TradeExecuted.h"

OrderBookAggregate::OrderBookAggregate() {
}

std::vector<std::shared_ptr<IDomainEvent> > OrderBookAggregate::placeOrder(const Order::SellOrder &order) {
    sell_orders_by_symbol_[order.getSymbol()].insert(order);
    std::vector<std::shared_ptr<IDomainEvent> > result;
    auto orderPlaced = std::make_shared<OrderPlaced>("test", order.getUserId(), order.getType(), order.getSymbol(),
                                                     order.getQuantity(), order.getPrice());
    result.push_back(orderPlaced);
    if (buy_orders_by_symbol_.contains(order.getSymbol()) && buy_orders_by_symbol_[order.getSymbol()].size() > 0) {
        Order::BuyOrder topBuyOrder = getTopBuyOrder(order.getSymbol());
        if (topBuyOrder.getQuantity() == order.getQuantity() && topBuyOrder.getPrice() == order.getPrice()) {
            sell_orders_by_symbol_.at(order.getSymbol()).erase(order);
            buy_orders_by_symbol_.at(order.getSymbol()).erase(topBuyOrder);
            auto tradeExecuted = std::make_shared<TradeExecuted>("test", topBuyOrder.getUserId(), order.getUserId(),
                                                                 order.getSymbol(), order.getQuantity(),
                                                                 order.getPrice());
            result.push_back(tradeExecuted);
        }
    }
    return result;
}

std::vector<std::shared_ptr<IDomainEvent> > OrderBookAggregate::placeOrder(const Order::BuyOrder &order) {
    buy_orders_by_symbol_[order.getSymbol()].insert(order);
    std::vector<std::shared_ptr<IDomainEvent> > result;
    auto orderPlaced = std::make_shared<OrderPlaced>("test", order.getUserId(), order.getType(), order.getSymbol(),
                                                     order.getQuantity(), order.getPrice());
    result.push_back(orderPlaced);
    if (sell_orders_by_symbol_.contains(order.getSymbol()) && sell_orders_by_symbol_.at(order.getSymbol()).size() > 0) {
        Order::SellOrder topSellOrder = getTopSellOrder(order.getSymbol());
        if (topSellOrder.getQuantity() == order.getQuantity() && topSellOrder.getPrice() == order.getPrice()) {
            buy_orders_by_symbol_.at(order.getSymbol()).erase(order);
            sell_orders_by_symbol_.at(order.getSymbol()).erase(topSellOrder);
            auto tradeExecuted = std::make_shared<TradeExecuted>("test", topSellOrder.getUserId(), order.getUserId(),
                                                                 order.getSymbol(), order.getQuantity(),
                                                                 order.getPrice());
            result.push_back(tradeExecuted);
        }
    }
    return result;
}

std::vector<std::shared_ptr<IDomainEvent> > OrderBookAggregate::cancelOrder(const Order::SellOrder &order) {
    if (!sell_orders_by_symbol_.contains(order.getSymbol())) {
        throw std::runtime_error("[OrderBookAggregate] Order symbol doesn't exist");
    }
    sell_orders_by_symbol_[order.getSymbol()].erase(order);
    auto orderCancelled = std::make_shared<OrderCancelled>("test", order.getUserId(), order.getType(),
                                                           order.getSymbol(), order.getQuantity(), order.getPrice());
    return {orderCancelled};
}

std::vector<std::shared_ptr<IDomainEvent> > OrderBookAggregate::cancelOrder(const Order::BuyOrder &order) {
    if (!buy_orders_by_symbol_.contains(order.getSymbol())) {
        throw std::runtime_error("[OrderBookAggregate] Order symbol doesn't exist");
    }
    buy_orders_by_symbol_[order.getSymbol()].erase(order);
    auto orderCancelled = std::make_shared<OrderCancelled>("test", order.getUserId(), order.getType(),
                                                           order.getSymbol(), order.getQuantity(), order.getPrice());
    return {orderCancelled};
}

Order::BuyOrder OrderBookAggregate::getTopBuyOrder(const std::string &symbol) const {
    return *buy_orders_by_symbol_.at(symbol).begin();
}

Order::SellOrder OrderBookAggregate::getTopSellOrder(const std::string &symbol) const {
    return *sell_orders_by_symbol_.at(symbol).begin();
}

std::vector<std::unique_ptr<Order::IActiveOrder> > OrderBookAggregate::getAllOrders() const {
    std::vector<std::unique_ptr<Order::IActiveOrder> > orders;
    for (const auto &orders_at_symbol: sell_orders_by_symbol_) {
        const std::string symbol = orders_at_symbol.first;
        for (const auto &it: orders_at_symbol.second) {
            auto order = std::make_unique<Order::SellOrder>(it.getUserId(), symbol, it.getQuantity(), it.getPrice());
            orders.push_back(std::move(order));
        }
    }
    for (const auto &orders_at_symbol: buy_orders_by_symbol_) {
        const std::string symbol = orders_at_symbol.first;
        for (const auto &it: orders_at_symbol.second) {
            auto order = std::make_unique<Order::SellOrder>(it.getUserId(), symbol, it.getQuantity(), it.getPrice());
            orders.push_back(std::move(order));
        }
    }
    return orders;
}

