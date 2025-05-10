#pragma once

#include "IDomainEvent.h"

class OrderPlaced : public IDomainEvent {
public:
    static constexpr std::string EVENT_TYPE = "OrderPlaced";

    OrderPlaced(std::string event_id, int user_id, Order::OrderType type, std::string symbol, int quantity,
                double price);

    explicit OrderPlaced(const std::string &json_string);

    void acceptVisitor(IEventVisitor &visitor) override;

    std::string toJson() const override;

private:
    int user_id_;
    Order::OrderType type_;
    std::string symbol_;
    int quantity_;
    double price_;
};
