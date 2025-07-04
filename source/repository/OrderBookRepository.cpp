#include "../../include/repository/OrderBookRepository.h"
#include "../../include/event/OrderPlaced.h"
#include "../../include/event/OrderCancelled.h"
#include "../../include/event/TradeExecuted.h"
#include "../../include/order/BuyOrder.h"
#include "../../include/order/SellOrder.h"
#include "../../include/aggregate/OrderBookAggregate.h"

OrderBookRepository::OrderBookRepository()
    : orderBook(std::make_shared<OrderBookAggregate>()) {}

void OrderBookRepository::processEvent(const IDomainEvent &event) {
    event.acceptVisitor(*this);
}

void OrderBookRepository::visit(const OrderPlaced &event) {
    int userId = event.getUserId();
    std::string symbol = event.getSymbol();
    int quantity = event.getQuantity();
    double price = event.getPrice();
    Order::OrderType type = event.getType();
    if (type == Order::OrderType::BUY)
        orderBook->placeOrder(Order::BuyOrder(userId, symbol, quantity, price));
    else if (type == Order::OrderType::SELL)
        orderBook->placeOrder(Order::SellOrder(userId, symbol, quantity, price));
    else
        throw std::runtime_error("[OrderBookRepository] Invalid order type");
}

void OrderBookRepository::visit(const OrderCancelled &event) {
    int userId = event.getUserId();
    std::string symbol = event.getSymbol();
    int quantity = event.getQuantity();
    double price = event.getPrice();
    Order::OrderType type = event.getType();
    if (type == Order::OrderType::BUY)
        orderBook->cancelOrder(Order::BuyOrder(userId, symbol, quantity, price));
    else if (type == Order::OrderType::SELL)
        orderBook->cancelOrder(Order::SellOrder(userId, symbol, quantity, price));
    else
        throw std::runtime_error("[OrderBookRepository] Invalid order type");
}

void OrderBookRepository::visit(const TradeExecuted &event) {
    int buyerId = event.getBuyerId();
    int sellerId = event.getSellerId();
    std::string symbol = event.getSymbol();
    int quantity = event.getQuantity();
    double price = event.getPrice();
    Order::BuyOrder buyOrder(buyerId, symbol, quantity, price);
    Order::SellOrder sellOrder(sellerId, symbol, quantity, price);
    orderBook->cancelOrder(buyOrder);
    orderBook->cancelOrder(sellOrder);
}

void OrderBookRepository::visit(const FundsCredited &event) {}

void OrderBookRepository::visit(const FundsDebited &event) {}

std::shared_ptr<OrderBookAggregate> OrderBookRepository::getAggregate() {
    return orderBook;
}

void OrderBookRepository::displayState(std::ostream &stream) const {
    stream << "[OrderBookRepository] STATE:" << std::endl;
    std::vector<std::unique_ptr<Order::IActiveOrder>> orders = orderBook->getAllOrders();
    for (const auto &it: orders) {
        stream << "( " << it->getUserId() << ", " << it->getType() << ", " << it->getSymbol() << ", " << it->getQuantity() << ", " << it->getPrice() << " )" << std::endl;
    }
    stream << "-------------" << std::endl;
}


