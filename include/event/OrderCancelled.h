#pragma once

#include "IDomainEvent.h"

class OrderCancelled : public IDomainEvent {
public:
    static constexpr std::string EVENT_TYPE = "OrderCancelled";

    OrderCancelled(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity,
                   double price);

    explicit OrderCancelled(const std::string &json_string);

    void acceptVisitor(IEventVisitor &visitor) const override;

    std::string toJson() const override;

    int getUserId() const;

    int getQuantity() const;

    double getPrice() const;

    std::string getSymbol() const;

    Order::OrderType getType() const;

private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
    double price_;
};
